#ifndef MINISHELL_LIB_H
#define MINISHELL_LIB_H
#include "../libft/libft.h"
#include "../Printf/ft_printf.h"

typedef struct s_data
{
	t_list *arg;
	char **args;
} t_data;


/*************************** INIT FUNC ***********************/

/*************************** PARSING FUNC ***************/

/*******************************************************************/
/*                        LIST CUSTOM FUNC                     		*/
/*******************************************************************/
void				ft_lstadd_front(t_list **lst, t_list *new);
int					ft_list_lenght(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
//void				ft_lstclear(t_list **lst);
void parser(char **arg, t_data *data);

#endif
