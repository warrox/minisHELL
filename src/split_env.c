#include "../includes/libft.h"
#include "../includes/minishell_lib.h"

static char *strdup_until(const char *str, char delimiter) {
    size_t len = 0;
    while (str[len] && str[len] != delimiter)
        len++;
    char *dup = malloc((len + 1) * sizeof(char));
    if (!dup)
        return NULL;
    size_t i = 0;
    while (i < len) {
        dup[i] = str[i];
        i++;
    }
    dup[len] = '\0';
    return dup;
}

char **split_first_equal(const char *s) {
    char **result;
    char *first_part;
    char *second_part;
    char *equal_pos;

    if (!s)
        return NULL;

    equal_pos = ft_strchr(s, '=');
    if (!equal_pos) {
        result = malloc(2 * sizeof(char *));
        result[0] = strdup(s);
        result[1] = NULL;
        return result;
    }

    first_part = strdup_until(s, '=');
    second_part = ft_strdup(equal_pos + 1);

    result = malloc(3 * sizeof(char *));
    if (!result || !first_part || !second_part) {
        free(first_part);
        free(second_part);
        free(result);
        return NULL;
    }

    result[0] = first_part;
    result[1] = second_part;
    result[2] = NULL;

    return result;
}
