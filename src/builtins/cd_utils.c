#include "../../includes/minishell_lib.h"

void exec_cd_with_opt(t_data *data, t_list_arg *tmp, t_list_arg *save_current, char *buffer)
{
	tmp = find_key_old_pwd(data);
	save_current = find_key_pwd(data);
	if(tmp->key_and_val[1] == NULL)
		tmp->key_and_val[1] = ft_strdup(save_current->key_and_val[1]);
	chdir(tmp->key_and_val[1]);
	free(tmp->key_and_val[1]);
	tmp->key_and_val[1] = NULL;
	tmp->key_and_val[1] = ft_strdup(save_current->key_and_val[1]);
	free(save_current->key_and_val[1]);
	save_current->key_and_val[1] = NULL;
	getcwd(buffer, 4096);
	save_current->key_and_val[1] = NULL;
	save_current->key_and_val[1] = ft_strdup(buffer);	
	ft_printf("%s\n",save_current->key_and_val[1]);

}


void exec_cd(t_data *data, t_list_arg *tmp, char *buffer, char *buffer_old, int buffer_size)
{
	tmp = find_key_pwd(data);
	free(data->lst->key_and_val[1]);
	data->lst->key_and_val[1] = NULL;
	getcwd(buffer, buffer_size);
	free(tmp->key_and_val[1]);
	tmp->key_and_val[1] = NULL;
	tmp->key_and_val[1] = ft_strdup(buffer);
	tmp = find_key_old_pwd(data);
	data->lst->key_and_val[1] = ft_strdup(buffer_old);

}


int no_arg(t_data *data, t_list_arg *tmp, char *path_hu)
{
	tmp = find_key_user(data);
	if(tmp == NULL)
		return (1);
	ft_strcpy(path_hu, "/home/");
	ft_strlcat(path_hu, tmp->key_and_val[1], (ft_strlen(path_hu) + ft_strlen(tmp->key_and_val[1])+ 1));
	int res = chdir(path_hu);
	ft_printf("CODE : %d\n",res);
	return (1);

}


int iterate_in_str(char *str)
{
	int j;
	if(ft_strlen(str) == 2)
		return(j = 0);
	else
		return(j = 3);
	while(str[j] == ' ')
		j++;
	return(j);
}


void init_tool_box(t_cd *tool_box)
{
	tool_box->i = 0;
	tool_box->j = 0;

}

