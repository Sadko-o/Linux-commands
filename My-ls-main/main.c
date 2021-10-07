/*
**
*/

#include "my_ls.h"
/*
**
*/

int main(int argc, char** argv)
{
    int file_count = count_files(".");
    file* files = files_alloc(file_count);

    save_data_of_file(files, ".");
    opt* options = get_opt(argc, argv, files, file_count);
    print_opt(options, files, file_count);

    opt_free(options);
    file_free(files, file_count);

    return 0;
}
