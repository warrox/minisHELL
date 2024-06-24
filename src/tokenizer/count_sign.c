
#include "../../includes/minishell_lib.h"

bool isDoubleQuote(char c) 
{
	return (c == '"');
}

int count_sign(char *input) 
{
    int count = 0;
    int tmp;
    int i = 0;
    char *ptr = input;
    
	printf("%s\n", input);
    if(!ptr)
		return(count);
	while (ptr[i]) {
		if (isSingleQuote(ptr[i])) {
			i++;
			while(ptr[i] && !isSingleQuote(ptr[i]))
				i++;
			i++;
		}
		if (isDoubleQuote(ptr[i])) {
			i++;
			while(ptr[i] && !isDoubleQuote(ptr[i]))
				i++;
			i++;
		}
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
