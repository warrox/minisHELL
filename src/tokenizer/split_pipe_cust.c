#include "../../includes/minishell_lib.h"
int count_splits(char *input, char c) 
{
    int count;
    int in_single_quote;
    int in_double_quote;

    count = 1;
    in_single_quote = 0;
    in_double_quote = 0;

    while (*input) {
        if (*input == '\'')
            in_single_quote = !in_single_quote;
        else if (*input == '"')
            in_double_quote = !in_double_quote;
        else if (*input == c && !in_single_quote && !in_double_quote) 
            count++;
        input++;
    }
    return count;
}

char **allocate_splits(char *input, char c, int *num_splits) 
{
    char **result;

    *num_splits = count_splits(input, c);
    result = (char **)malloc((*num_splits + 1) * sizeof(char *));
    return result;
}


void add_token(char **result, char *start, char *end, int *index) 
{
    int length; 
	length = end - start;
    result[*index] = (char *)malloc((length + 1) * sizeof(char));
    strncpy(result[*index], start, length);
    result[*index][length] = '\0';
    (*index)++;
}

void fill_splits(char **result, char *input, char c) 
{
    char *token_start;
    int in_single_quote;
    int in_double_quote;
    int index;

    token_start = input;
    in_single_quote = 0;
    in_double_quote = 0;
    index = 0;

    while (*input) {
        if (*input == '\'')
            in_single_quote = !in_single_quote;
        else if (*input == '"')
            in_double_quote = !in_double_quote;
        else if (*input == c && !in_single_quote && !in_double_quote) 
		{
            add_token(result, token_start, input, &index);
            token_start = input + 1;
        }
        input++;
    }
    add_token(result, token_start, input, &index);
    result[index] = NULL;
}
char **split_pipe_cust(char *input, char c) 
{
    char **result;
    int num_splits;

    result = allocate_splits(input, c, &num_splits);
    fill_splits(result, input, c);
    return result;
}


