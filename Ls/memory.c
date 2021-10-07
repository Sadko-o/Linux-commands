/*
**
*/

#include "my_ls.h"
/*
**
*/
opt* opt_alloc(int num);
file* files_alloc(int num);
int* array_alloc(int num);
void opt_free(opt* opt);
void file_free(file* files, int num);


opt* opt_alloc(int num)
{
    opt* opts = (opt*)malloc(sizeof(opt));

    opts->a = 0;
    opts->t = 0;
    opts->wrong_opt = 0;
    opts->files = array_alloc(num);
    opts->wrong_files = 0;

    return opts;
}


file* files_alloc(int num)
{
    int index = 0;
    
    file* files = (file*)malloc(num * sizeof(file));
    while (index < num) {
        files[index].name = (char*)malloc(256 * sizeof(char));
        files[index].time = 0;
        files[index].type = 0;
        index += 1;
    }

    return files;
}

int* array_alloc(int num)
{
    int index;
    int* array = (int*)malloc(num * sizeof(int));

    for (index = 0; index < num; index += 1) {
        array[index] = 0;
    }

    return array;
}


void opt_free(opt* opts)
{
    free(opts->files);
    free(opts);
}

void file_free(file* files, int num)
{
    int index;
    for (index = 0; index < num; index += 1) {
        free(files[index].name);
    }

    free(files);
}