/*
**
*/

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>

#define st_mtime st_mtim.tv_sec

/*
**
*/

typedef struct options
{
    int a;
    int t;
    int wrong_opt;
    int* files;
    _Bool wrong_files;
} opt;

typedef struct file
{
    char* name;
    _Bool type;
    long int time;
} file;

// my_func.c
void my_strcpy(char* param_1, char* param_2);
int my_strcmp(char* param_1, char* param_2);

// my_ls.c
int count_files(char* dir);
void save_data_of_file(file* files, char* dir);

//get_opt.c
opt* get_opt(int argc, char** argv, file* files, int num);
int check_option(char* str);
void add_option(opt* opts, char* str);
void add_files(opt* opts, char* str, file* files, int num);
void print_opt(opt* opt, file* files, int num);

// memory.c
opt* opt_alloc(int num);
int* array_alloc(int num);
file* files_alloc(int num);
void opt_free(opt* opt);
void file_free(file* files, int num);

//user_out.c
void sort(file* files, opt* opts, int num, int obj);
void swap(char* param_1, char* param_2);
int* has_file_obj(int* files, int num);
void output(opt* opts, file* files, int* objs, int num);
void print_dir(file* files, opt* opts, int num);
void print_opt(opt* opts, file* files, int num);