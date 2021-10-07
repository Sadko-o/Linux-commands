#include "my_ls.h"

file* init_files(int len)
{
    int index = 0;
    
    file* files = (file*)malloc(len * sizeof(file));
    while (index < len)
    {
        files[index].name = (char*)malloc(256 * sizeof(char));
        files[index].time = 0;
        files[index].type = 0;
        index += 1;
    }

    return files;
}

int* init_int_array(int len)
{
    int index;

    int* array = (int*)malloc(len * sizeof(int));
    for (index = 0; index < len; index += 1)
    {
        array[index] = 0;
    }

    return array;
}

t_opt* init_opt(int len)
{
    t_opt* opt = (t_opt*)malloc(sizeof(t_opt));

    opt->a = 0;
    opt->t = 0;
    opt->wrongOpt = 0;
    opt->files = init_int_array(len);
    opt->wrongFiles = 0;

    return opt;
}