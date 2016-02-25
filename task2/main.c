#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

#define INIT_NUM 32
#define MAX_NAME_SIZE 20000
#define MAX_NUMBER_SIZE 20000
#define MAX_COMMAND_SIZE 20000

#define CM_FIND "find"
#define CM_CREATE "create"
#define CM_DELETE "delete"
#define CM_CHANGE "change"
#define CM_EXIT "exit"
#define CM_CHANGE_NAME "name"
#define CM_CHANGE_NUM "number"

#define MSG_UNRECOGNIZED_INPUT "Unrecognized input.\n"
#define MSG_UNRECOGNIZED_NAME_NUMBER "Unrecognized name or number.\n"

typedef struct {
    int id;
    char *name;
    char *num;
} Record;

typedef struct {
    int n;
    int used;
    Record *v;
} Phone_Book;

void phone_book_init_from_file(Phone_Book *pb);
void phone_book_unload_to_file(Phone_Book *pb);
void phone_book_find_name(Phone_Book *pb, char *name);
void phone_book_find_num(Phone_Book *pb, char *num);
void phone_book_create(Phone_Book *pb, char *name, char *num);
void phone_book_delete(Phone_Book *pb, int id);
void phone_book_change_name(Phone_Book *pb, int id, char *name);
void phone_book_change_num(Phone_Book *pb, int id, char *num);
bool phone_book_is_id(Phone_Book *pb, int id);
void phone_book_expand(Phone_Book *pb);
void phone_book_free(Phone_Book *pb);
int phone_book_find_free_id(Phone_Book *pb);
void phone_book_find(Phone_Book *pb, char *key);

void record_print(Record *r, FILE *output);
void record_set_name(Record *r, char *name);
void record_set_num(Record *r, char *num);
void record_set(Record *r, int id, char *name, char *num);

bool is_name(char *key);
bool is_num(char *key);

int str_to_int(char *str);
void str_to_lower(char *_s, char *s);
void str_to_number(char *_num, char *num);

void print_wrong_input_msg();

char *file_name;

int main(int argc, char *argv[]) {
    Phone_Book pb;
    file_name = argv[1];
    fclose(fopen(file_name, "a"));
    for (; ;) {
        char command[MAX_COMMAND_SIZE];
        scanf("%s", command);

        if (!strcmp(command, CM_FIND)) {
            char key[MAX_NUMBER_SIZE | MAX_NAME_SIZE];
            scanf("%s", key);
            phone_book_find(&pb, key);
        } else
        if (!strcmp(command, CM_CREATE)) {
            char name[MAX_NAME_SIZE];
            char num[MAX_NUMBER_SIZE];
            scanf("%s%s", name, num);
            phone_book_create(&pb, name, num);
        } else
        if (!strcmp(command, CM_DELETE)) {
            char s_id[MAX_NUMBER_SIZE];
            scanf("%s", s_id);
            int id = str_to_int(s_id);
            phone_book_delete(&pb, id);
        } else
        if (!strcmp(command, CM_CHANGE)) {
            char s_id[MAX_NUMBER_SIZE];
            char ch_type[MAX_COMMAND_SIZE];
            char key[MAX_NAME_SIZE | MAX_NUMBER_SIZE];
            scanf("%s%s%s", s_id, ch_type, key);
            int id = str_to_int(s_id);

            if (!strcmp(ch_type, CM_CHANGE_NAME)) {
                if (!is_name(key)) {
                    print_wrong_input_msg();
                    continue;
                }

                phone_book_change_name(&pb, id, key);
            } else
            if (!strcmp(ch_type, CM_CHANGE_NUM)) {
                if (!is_num(key)) {
                    print_wrong_input_msg();
                    continue;
                }

                phone_book_change_num(&pb, id, key);
            }
            else {
                print_wrong_input_msg();
            }
        } else
        if (!strcmp(command, CM_EXIT)) {
            return 0;
        } else {
            print_wrong_input_msg();
        }
    }
}

void phone_book_init_from_file(Phone_Book *pb) {
    FILE *input = fopen(file_name, "r");
    pb->n = INIT_NUM;
    pb->used = 0;
    pb->v = calloc(sizeof(Record), (size_t )pb->n);

    for (; ;) {
        int id;
        char name[MAX_NAME_SIZE];
        char num[MAX_NUMBER_SIZE];
        if (fscanf(input, "%d%s%s", &id, name, num) != 3) {
            break;
        }
        record_set(&pb->v[pb->used++], id, name, num);

        if (pb->used == pb->n) {
            phone_book_expand(pb);
        }
    }
    fclose(input);
}

void phone_book_unload_to_file(Phone_Book *pb) {
    FILE *output = fopen(file_name, "w");
    for (int i = 0; i < pb->used; i++) {
        if (pb->v[i].id != -1) {
            record_print(&pb->v[i], output);
            //fprintf(output, "%d %s %s\n", pb->v[i].id, pb->v[i].name, pb->v[i].num);
            fflush(output);
        }
    }
    fclose(output);
    phone_book_free(pb);
}

void phone_book_find(Phone_Book *pb, char *key) {
    if (!is_name(key) && !is_num(key)) {
        printf(MSG_UNRECOGNIZED_NAME_NUMBER);
        fflush(stdout);
        return;
    }
    phone_book_init_from_file(pb);
    phone_book_find_name(pb, key);
    phone_book_find_num(pb, key);
    phone_book_unload_to_file(pb);
}

void phone_book_find_name(Phone_Book *pb, char name[MAX_NAME_SIZE | MAX_NUMBER_SIZE]) {
    if (!is_name(name)) {
        return;
    }
    str_to_lower(name, name);
    for (int i = 0; i < pb->used; i++) {
        char cur_name[MAX_NAME_SIZE | MAX_NUMBER_SIZE];
        str_to_lower(cur_name, pb->v[i].name);
        //printf("!!!!!!%d\n", strstr(cur_name, name));
        if (strstr(cur_name, name)) {
            record_print(&pb->v[i], stdout);
        }
    }
}

void phone_book_find_num(Phone_Book *pb, char num[MAX_NAME_SIZE | MAX_NUMBER_SIZE]) {
    if (!is_num(num)) {
        return;
    }
    str_to_number(num, num);
    for (int i = 0; i < pb->used; i++) {
        char cur_num[MAX_NAME_SIZE | MAX_NUMBER_SIZE];
        str_to_number(cur_num, pb->v[i].num);
        if (!strcmp(cur_num, num)) {
            record_print(&pb->v[i], stdout);
        }
    }
}

void phone_book_create(Phone_Book *pb, char name[MAX_NAME_SIZE], char num[MAX_NUMBER_SIZE]) {
    if (!is_name(name) || !is_num(num)) {
        print_wrong_input_msg();
        return;
    }
    phone_book_init_from_file(pb);
    record_set(&pb->v[pb->used++], phone_book_find_free_id(pb), name, num);
    phone_book_unload_to_file(pb);
}

void phone_book_delete(Phone_Book *pb, int id) {
    phone_book_init_from_file(pb);
    if (!phone_book_is_id(pb, id)) {
        print_wrong_input_msg();
        phone_book_unload_to_file(pb);
        return;
    }

    for (int i = 0; i < pb->used; i++) {
        if (pb->v[i].id == id) {
            pb->v[i].id = -1;
            free(pb->v[i].name);
            pb->v[i].name = NULL;
            free(pb->v[i].num);
            pb->v[i].num = NULL;
        }
    }
    phone_book_unload_to_file(pb);
}

void phone_book_change_name(Phone_Book *pb, int id, char name[MAX_NAME_SIZE]) {
    phone_book_init_from_file(pb);
    if (!phone_book_is_id(pb, id)) {
        print_wrong_input_msg();
    }

    for (int i = 0; i < pb->used; i++) {
        if (pb->v[i].id == id) {
            record_set_name(&pb->v[i], name);
            break;
        }
    }
    phone_book_unload_to_file(pb);
}

void phone_book_change_num(Phone_Book *pb, int id, char num[MAX_NUMBER_SIZE]) {
    phone_book_init_from_file(pb);
    for (int i = 0; i < pb->used; i++) {
        if (pb->v[i].id == id) {
            record_set_num(&pb->v[i], num);
            break;
        }
    }
    phone_book_unload_to_file(pb);
}

bool phone_book_is_id(Phone_Book *pb, int id) {
    for (int i = 0; i < pb->used; i++) {
        if (pb->v[i].id == id) {
            return true;
        }
    }

    return false;
}

void phone_book_expand(Phone_Book *pb) {
    Record *_v = malloc(2 * pb->n * sizeof(Record));
    for (int i = 0; i < pb->n; i++) {
        _v[i].id = pb->v[i].id;
        _v[i].name = pb->v[i].name;
        _v[i].num = pb->v[i].num;
    }
    free(pb->v);
    pb->n *= 2;
    pb->v = _v;
}

void phone_book_free(Phone_Book *pb) {
    for (int i = 0; i < pb->used; i++) {
        if (pb->v[i].name) {
            free(pb->v[i].name);
        }
        if (pb->v[i].num) {
            free(pb->v[i].num);
        }
    }
    free(pb->v);
    pb->used = pb->n = 0;
}

int phone_book_find_free_id(Phone_Book *pb) {
    bool *id_is_used = calloc(sizeof(bool), (size_t)pb->used + 1);
    for (int i = 0; i < pb->used; i++) {
        if (pb->v[i].id < pb->used) {
            id_is_used[i] = true;
        }
    }
    for (int i = 0; i <= pb->used; i++) {
        if (!id_is_used[i]) {
            free(id_is_used);
            return i;
        }
    }
    return pb->used;
}

bool is_name(char *key) {
    for (char *c = key; *c; c++) {
        if (!isalpha(*c)) {
            return false;
        }
    }
    return true;
}

//kkkkkkkkkkkkkkkkkkkkk
bool is_num(char *key) {
    for (char *c = key; *c; c++) {
        if (!isdigit(*c) && *c != '(' && *c != ')' && *c != '-' && *c != '+') {
            return false;
        }
    }
    return true;
}


int str_to_int(char *str) {
    int res = 0;
    for (char *c = str; *c; c++) {
        if (!isdigit(*c)) {
            return -1;
        }
        res = res * 10 + (*c - '0');
    }
    return res;
}


void print_wrong_input_msg() {
    printf("%s", MSG_UNRECOGNIZED_INPUT);
    fflush(stdout);
}

void str_to_lower(char *_s, char *s) {
    for (int i = 0; ; i++) {
        _s[i] = (char)tolower(s[i]);
        if (!s[i]) {
            break;
        }
    }
}

void record_print(Record *r, FILE *output) {
    fprintf(output, "%d %s %s\n", r->id, r->name, r->num);
    fflush(output);
}

void record_set_name(Record *r, char *name) {
    if (r->name) {
        free(r->name);
    }
    r->name = malloc(strlen(name));
    strcpy(r->name, name);
}

void record_set_num(Record *r, char *num) {
    if (r->num) {
        free(r->num);
    }
    r->num = malloc(strlen(num));
    strcpy(r->num, num);
}

void record_set(Record *r, int id, char *name, char *num) {
    r->id = id;
    record_set_name(r, name);
    record_set_num(r, num);
}

void str_to_number(char *_num, char *num) {
    int j = 0;
    for (int i = 0; num[i]; i++) {
        if (isdigit(num[i])) {
            _num[j++] = num[i];
        }
    }
    _num[j] = '\0';
}