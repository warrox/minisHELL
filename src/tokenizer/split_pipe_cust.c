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
    char *token_start = start;
    char *token_end = end;

    // Trim leading spaces
    while (token_start < token_end && (*token_start == ' ' || *token_start == '\t'))
        token_start++;

    // Trim trailing spaces
    while (token_end > token_start && (*(token_end - 1) == ' ' || *(token_end - 1) == '\t'))
        token_end--;

    // Remove double quotes
    char *temp = (char *)malloc((token_end - token_start + 1) * sizeof(char));
    char *temp_ptr = temp;
    while (token_start < token_end) {
        if (*token_start != '"') {
            *temp_ptr++ = *token_start;
        }
        token_start++;
    }
    *temp_ptr = '\0';

    length = temp_ptr - temp;
    result[*index] = (char *)malloc((length + 1) * sizeof(char));
    strncpy(result[*index], temp, length);
    result[*index][length] = '\0';

    free(temp);
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


