/*
**
*/

#include "my_ls.h"

/*
**
*/

int check_option(char* str);
void add_option(opt* opts, char* str);
void add_files(opt* opts, char* str, file* files, int num);



opt* get_opt(int argc, char** argv, file* files, int num)
{
    opt* opts = opt_alloc(num);
    int index = 1;

    while (index < argc)
    {
        if (check_option(argv[index])) {
            add_option(opts, argv[index] + 1);
        } else {
            add_files(opts, argv[index], files, num);
        }

        index += 1;
    }
    return opts;
}

int check_option(char* str)
{
    if (str[0] == '-'){
        return 1;
    }

    return 0;
}

void add_option(opt* opts, char* str)
{
    int index = 0;

    while (str[index] != '\0'){
        if (str[index] == 'a'){
            opts->a = 1;
        } else if (str[index] == 't'){
            opts->t = 1;
        } else {
            opts->wrong_opt = str[index];
        }

        index += 1;
    }
}

void add_files(opt* opts, char* str, file* files, int num)
{
    int index = 0;
    _Bool wrong = 1;

    while (index < num) {
        if ( my_strcmp(files[index].name, str) == 0 ) {
            if(files[index].type == 1){
                opts->files[index] = 2;
            } else{
                opts->files[index] = 1;
            }
            wrong = 0;
        }
        index += 1;
    }

    if (wrong == 1) {
        opts->wrong_files = 1;
        printf("my_ls: cannot access '%s': No such file or directory\n", str);
    }
}