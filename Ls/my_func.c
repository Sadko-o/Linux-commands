/*
**
*/

#include "my_ls.h"

/*
**
*/

int my_strcmp(char* param_1, char* param_2)
{
    int i = 0;

	while(param_1[i] != '\0')
    {
		if (param_1[i] != param_2[i])
            break;
        i += 1;
	}
    char return_value = param_1[i] - param_2[i];
	return return_value;
}

void my_strcpy(char* param_1, char* param_2)
{
    int i = 0;
    
    while (param_2[i] != '\0')
    {
        param_1[i] = param_2[i];
        i += 1;
    }
    param_1[i] = '\0';
}