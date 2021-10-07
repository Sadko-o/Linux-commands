/*
**
*/

#include "my_ls.h"

/*
**
*/

void sort(file* files, opt* opts, int num, int obj);
void swap(char* param_1, char* param_2);
int* has_file_obj(int* files, int num);
void output(opt* opts, file* files, int* objs, int num);
void print_dir(file* files, opt* opt, int num);
void print_opt(opt* opts, file* files, int num);



void swap(char* param_1, char* param_2)
{
    char temp[256];

    my_strcpy(temp, param_1);
    my_strcpy(param_1, param_2);
    my_strcpy(param_2, temp);
}

void print_dir(file* files, opt* opts, int num)
{
    int index = 0;
    while (index < num){
        if (opts->a == 0){
            if (files[index].name[0] == '.'){
                index += 1;
                continue;
            }
        }
        printf("%s  ", files[index].name);
        index += 1;
    }
    printf("\n");
}


void print_opt(opt* opts, file* files, int num)
{
    if (opts->wrong_opt == 0){
        sort(files, opts, num, 0);
        int* objs = has_file_obj(opts->files, num);
        output(opts, files, objs, num);
        free(objs);
    } else {
        printf("my_ls: invalid option -- '%c'\n", opts->wrong_opt);
    }
}


int* has_file_obj(int* files, int num)
{
    int index = 0;
    int* objs = array_alloc(2);

    while (index < num) {
        if (files[index] == 1) {
            objs[0] += 1;
        } else if (files[index] == 2) {
            objs[1] += 1;
        }

        index += 1;
    }

    return objs;
}

void sort(file* files, opt* opts, int num, int obj)
{
    int index, next;
    long int temp;

    for (index = 0; index < num; index ++) {
        for (next = index + 1; next < num; next ++) {
            if (opts->t != 0) {
                if (files[index].time < files[next].time) {
                   
                    temp = files[index].time;
                    files[index].time = files[next].time;
                    files[next].time = temp;

                    swap(files[index].name, files[next].name);
                    if (obj == 0) {
                        temp = opts->files[index];
                        opts->files[index] = opts->files[next];
                        opts->files[next] = temp;
                    }
                }
            } else {
                if (my_strcmp(files[index].name, files[next].name) > 0) {
                    swap(files[index].name, files[next].name);

                    if (obj == 0) {
                        temp = opts->files[index];
                        opts->files[index] = opts->files[next];
                        opts->files[next] = temp;
                    }
                }
            }
        }
    }
}


void output(opt* opts, file* files, int* objs, int num)
{
    int index = 0, dir_count = 1, count;

    if (objs[0] != 0) {
        while (index<num){ 
            if (opts->files[index] == 1 ){
                printf("%s  ", files[index].name);
            }

            index += 1;
        }

        printf("\n");
    }
    
    
    if (objs[1] != 0) {
        index = 0;

        if (objs[0] != 0) {
                printf("\n");
            }

        while (index < num) {
            if (opts->files[index] == 2)
                {
                    if((objs[0] != 0) || (objs[1] > 1)){
                        printf("%s:\n", files[index].name);
                    }

                    count = count_files(files[index].name);
                    file* this_dir = files_alloc(count);
                    save_data_of_file(this_dir, files[index].name);
                    sort(this_dir, opts, count, 2);
                    print_dir(this_dir, opts, count);
                    file_free(this_dir, count);

                    if (dir_count < objs[1]) {
                        printf("\n");
                        dir_count += 1;
                    }
                }

                index += 1;
            }
        }
    else if (opts->wrong_files == 0) {
        print_dir(files, opts, num);
    }
}
