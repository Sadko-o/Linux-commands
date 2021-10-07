/*
**
*/

#include "my_tar.h"

/*
**
*/


char* my_strncpy(char* dest, char* src, int num);
void my_memset(char* buff, char c, int size);
void my_bzero(char* buff, int size);
char* my_init(int size);
int my_strcmp(char* first, char* second);
int my_strlen(char* input);
char* my_strdup(char* input);
char* my_join(char* first_part, char* second_part, char* third_part);




char* my_strncpy(char* dest, char* src, int num)
{
    int index;
    index = 0;
    while (index < num && src[index] != '\0') {
        dest[index] = src[index];
        index++;
    }
    dest[index] = '\0';
    return dest;
}

void my_memset(char* buff, char c, int size)
{
    int index;
    index = 0;
    while (index < size)
    {
        buff[index] = c;
        index += 1;
    }
}

void my_bzero(char* buff, int size)
{
    my_memset(buff, 0, size);
}

char* my_init(int size)
{
    char* buffer = (char*)malloc(size);
    my_bzero(buffer, size);
    return buffer;
}

int my_strcmp(char* first, char* second)
{
    int count;

    count = 0;
    while (first[count] != '\0' && second[count] != '\0' && first[count] == second[count])
        count++;
    return (first[count] - second[count]);
}

int my_strlen(char* input)
{
    int index;
    index = 0;
    while (input[index] != '\0')
    {
        index += 1;
    }
    return index;
}

char* my_strdup(char* input)
{
    int index;
    int length;
    char* my_str;

    length = my_strlen(input);
    my_str = (char*)malloc(sizeof(char) * length + 1);
    if (!my_str)
    {
        return 0;
    }
    index = 0;
    while (input[index] != '\0')
    {
        my_str[index] = input[index];
        index += 1;
    }
    my_str[index] = '\0';
    return my_str;
}

char* my_join(char* first_part, char* second_part, char* third_part)
{
    int size = my_strlen(first_part) + my_strlen(second_part) + my_strlen(third_part) + 1;
    char* new_str = malloc(sizeof(char) * size);
    int index_1 = 0, index_2, index_3;
    
    while (first_part[index_1] != '\0')
    {
        new_str[index_1] = first_part[index_1];
        index_1++;
    }
    index_2 = 0;
    while (second_part[index_2] != '\0')
    {
        new_str[index_1] = second_part[index_2];
        index_1++;
        index_2++;
    }
    index_3 = 0;
    while (third_part[index_3] != '\0')
    {
        new_str[index_1] = third_part[index_3];
        index_1++;
        index_3++;
    }
    new_str[index_1] = '\0';
    return new_str;
}