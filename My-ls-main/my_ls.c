/*
**
*/

#include "my_ls.h"
/*
**
*/

int count_files(char* dir)
{
    DIR* folder;
    struct dirent* entry;
    int count = 0;
    folder = opendir(dir);
    if(folder == NULL){
            printf("Unable to read directory");
            return(1);
        }
    
    while((entry = readdir(folder))){
            count += 1;
        }

    closedir(folder);
    return count;
}

void save_data_of_file (file* file, char* dir)
{
    DIR* folder;
    struct dirent * entry;
    struct stat file_stat;
    folder = opendir(dir);
    int index = 0;

    while(( entry=readdir(folder) )) 
    {
        stat(entry->d_name, &file_stat);

        if(S_ISDIR(file_stat.st_mode))
            file[index].type = 1;
        else 
            file[index].type = 0;
        
        file[index].time = file_stat.st_mtime;
        my_strcpy(file[index].name, entry->d_name);
        index += 1;
    }

    closedir(folder);
}