
#include "../../includes/minishell_lib.h"
#include <stdio.h>

bool isDoubleQuote(char c) 
{
	return (c == '"');
}

// int count_sign(char *input) 
// {
//     int count = 0;
//     int tmp;
//     int i = 0;
//     char *ptr = input;
//     if(!ptr)
// 		return(count);
// 	while (ptr[i]) 
// 	{
// 		if (isSingleQuote(ptr[i])) 
// 		{
// 			i++;
// 			while(ptr[i] && !isSingleQuote(ptr[i]))
// 				i++;
// 			i++;
// 		}
// 		if (isDoubleQuote(ptr[i])) 
// 		{
// 			i++;
// 			while(ptr[i] && !isDoubleQuote(ptr[i]))
// 				i++;
// 			i++;
// 		}
//         tmp = sign_cmp(&ptr[i]);
// 		if (tmp != 0) 
// 		{
// 			count++;
// 			i += tmp;
// 		} 
// 		else 
// 			i++;
//     }
//     return (count);
// }

//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
int handle_single_quote(char *ptr, int i) 
{
    i++;
    while(ptr[i] && !isSingleQuote(ptr[i]))
        i++;
    i++;
    return i;
}

int handle_double_quote(char *ptr, int i) 
{
    i++;
    while(ptr[i] && !isDoubleQuote(ptr[i]))
        i++;
    i++;
    return i;
}

int handle_sign(char *ptr, int i, int *count) 
{
    int tmp;
    tmp = sign_cmp(&ptr[i]);
    if (tmp != 0) 
    {
        (*count)++;
        i += tmp;
    } 
    else 
        i++;
    return i;
}

int count_sign(char *input) 
{
    int count;
    int i;
    char *ptr;
    
    count = 0;
    i = 0;
    ptr = input;
    if(!ptr)
        return(count);
    while (ptr[i]) 
    {
        if (isSingleQuote(ptr[i]))
            i = handle_single_quote(ptr, i);
        else if (isDoubleQuote(ptr[i]))
            i = handle_double_quote(ptr, i);
        else 
            i = handle_sign(ptr, i, &count);
    }
    
    return (count);
}
