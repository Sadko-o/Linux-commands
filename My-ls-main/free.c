#include "my_ls.h"

void free_opt(t_opt* opt)
{
    free(opt->files);
    free(opt);
}

void free_file(file* files, int len)
{
    int index;
    for (index = 0; index < len; index += 1)
    {
        free(files[index].name);
    }
    free(files);
}