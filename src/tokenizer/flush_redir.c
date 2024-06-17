#include "../../includes/minishell_lib.h"

void handle_double_quotes_flush(char *str, char *buffer, int *i, int *j) {
    (*i)++;
    while (str[*i] != '\"') {
        buffer[(*j)++] = str[*i];
        (*i)++;
    }
    if (str[*i] == '\"') {
        (*i)++;
    }
}

void handle_single_quotes_flush(char *str, char *buffer, int *i, int *j, t_data *data) {
    (*i)++;
    while (str[*i] != '\'') {
        buffer[(*j)++] = str[*i];
        (*i)++;
    }
    if (str[*i] == '\'') {
        data->pansement = 1;
        (*i)++;
    }
}

int handle_signs(char *str, int *i) {
    int tmp;
    tmp = sign_cmp(&str[*i]);
    if (tmp) {
        *i += tmp;
        *i += get_word_size(&str[*i]);
    }
    return tmp;
}

char *flush_redir(char *str, t_data *data) {
    char buffer[2048];
    int i;
    int tmp;
    int j;

    i = 0;
    j = 0;
    data->pansement = 0;

    while (str[i]) {
        if (str[i] == '\"') {
            handle_double_quotes_flush(str, buffer, &i, &j);
        } else if (str[i] == '\'') {
            handle_single_quotes_flush(str, buffer, &i, &j, data);
        } else {
            tmp = handle_signs(str, &i);
            if (!tmp) {
                buffer[j++] = str[i];
                i++;
            }
        }
    }
    buffer[j] = 0;
    return ft_strdup(buffer);
}
