/*
**
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>

#include <string.h>
#include <errno.h>
#include <stdbool.h>

#define READLINE_READ_SIZE 512
#define NL '\n'
#define TERM '\0'

/*
**
*/
//list of the functions 
void *my_memmove(void *destination, const void *source, size_t size);
void *my_memcpy(void *dest, const void *src, size_t size);
void *my_calloc(size_t nmemb, size_t size);
void my_memset(void *data, int c, size_t size);
size_t my_strlen(const char * string);
char* my_strcpy(char* param_1, char* param_2);
char* my_strchr(char* param_1, char param_2);
char* my_strncpy(char* param_1, char* param_2, int param_3);
char* my_readline(int fd);

/*
**
*/

void *my_memmove(void *destination, const void *source, size_t size)
{
    char str[size];

    my_memcpy(str, source, size);
    my_memcpy(destination, source, size);

    return destination;
}

void *my_memcpy(void *dest, const void *src, size_t size)
{
    char *destination = dest;
    const char *source = src;

    while (size--)
        *destination++ = *source++;
    return dest;
}

void my_memset(void *data, int c, size_t size)
{
    unsigned char *temp;
    temp = data;

    while (size > 0) {
        *temp++ = (unsigned char)c;
        size--;
    }
}

void *my_calloc(size_t nmemb, size_t size) {

   void *r = malloc(nmemb*size);
   my_memset(r, 0, (nmemb*size));

   return r;
}

char* my_strchr(char* param_1, char param_2)
{
    for (int i=0; i<strlen(param_1); i++) {
            if (param_1[i] == param_2) {
                return &param_1[i];
            }
        }
    return NULL;
}

size_t my_strlen( const char * string ){
    int len = 0;
    int i = 0;
    while(string[i]!='\0'){
        len += 1;
        i += 1;
    }
    return i;
}

char* my_strcpy(char* param_1, char* param_2)
{
    int i=0;//size
    while(param_2[i]!='\0'){i++;}
    for(int j=0;j<i;j++){
        param_1[j] = param_2[j];
    }
    return param_1;
}

char* my_strncpy(char* param_1, char* param_2, int param_3)
{
    for(int i=0;i<param_3; i++)
    {
        param_1[i]=param_2[i];
    }    
    return param_1;
}


char* my_readline(int fd)
{
    char* str=NULL;
    char *tmp=NULL;
    static char buffer[2048];
    int ret, len, buff_len;

    while(true)
    {
        buff_len = my_strlen(buffer);
        ret = read(fd, &buffer[buff_len], READLINE_READ_SIZE);

        if(ret == -1) {
            return NULL;
        }

        
        if(ret == 0 && my_strlen(buffer) == 0)
            return NULL;
            
        if(ret != 0)
            buffer[ret + buff_len] = '\0';


        tmp = my_strchr(buffer, '\n');

        if(tmp != NULL) {

            *tmp = TERM;
            len = tmp - buffer + 1;
            str = my_calloc(len, sizeof(char));
            my_strncpy(str, buffer, len);
           
            len = my_strlen(tmp+1) + 1;
            my_memmove(buffer, tmp+1, len);

            return str;

        } else if(ret == 0) {

            len = my_strlen(buffer) + 1;
            str = my_calloc(len, sizeof(char));
            my_strcpy(str, buffer);

            return str;
        }
    }
}



int main()
{
    char *str = NULL;
    int fd = open("./file.txt", O_RDONLY);
    while ((str = my_readline(fd)) != NULL)
    {
        printf("%s\n", str);
        free(str);
    }
    close(fd);
    return 0;
}