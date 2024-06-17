
#include "../../includes/minishell_lib.h"
int handle_double_quote(char **ptr, int *i) {
    if ((*ptr)[*i] == '\"') {
        if ((*ptr)[*i + 1])
            (*i)++;
        *ptr = strchr(*ptr, '\"');
        if (!*ptr)
            return 1;
    }
    return 0;
}

int handle_single_quote(char **ptr, int *i) {
    if ((*ptr)[*i] == '\'') {
        if ((*ptr)[*i + 1])
            (*i)++;
        *ptr = strchr(*ptr, '\'');
        if (!*ptr)
            return 1;
    }
    return 0;
}

int count_sign(char *input) 
{
    int count = 0;
    int tmp;
    int i = 0;
    char *ptr = input;
    
    while (ptr[i]) {
        if (handle_double_quote(&ptr, &i))
            return count;
        if (handle_single_quote(&ptr, &i))
            return count;
        tmp = sign_cmp(&ptr[i]);
        if (tmp != 0) {
            count++;
            i += tmp;
        } else {
            i++;
        }
    }
    return count;
}
