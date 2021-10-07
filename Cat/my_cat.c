#include <stdio.h>
#include <stdlib.h>
int main(int ac, char* av[])
{
    FILE * fc;
    char l;
    for(int i=1;i<ac;i++)
    {
        fc = fopen(av[i], "r");
        if(fc == NULL)
            {
                printf("Error!");              
            }
        else
            {
                while((l = fgetc(fc)) != EOF)
                    {
                        printf("%c", l);
                    }
            }
        fclose(fc);
    }
    
}