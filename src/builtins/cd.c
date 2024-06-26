#include "../../includes/minishell_lib.h"
#include <unistd.h>


t_list_arg *find_key_user(t_data *data)
{
	t_list_arg *tmp;
	tmp = data->lst;
	while(tmp)
	{
		if(ft_strcmp(tmp->key_and_val[0], "USER") == 0)
			break;
		tmp = tmp->next;
	}
	if(tmp == NULL)
		ft_printf("USER is unset\n");
	return(tmp);
} 

t_list_arg *find_key_old_pwd(t_data *data)
{
	t_list_arg *tmp;
	tmp = data->lst;
	while(tmp)
	{
		if(ft_strcmp(tmp->key_and_val[0], "OLDPWD") == 0)
			break;
		tmp = tmp->next;
	}
	return(tmp);
} 

t_list_arg *find_key_pwd(t_data *data)
{
	t_list_arg *tmp;
	tmp = data->lst;
	while(tmp)
	{
		if(ft_strcmp(tmp->key_and_val[0], "PWD")== 0)
			break;
		tmp = tmp->next;
	}
	return(tmp);
} 
int cd_check_opt(char *path, t_data *data)
{
	t_list_arg *tmp;
	t_list_arg *save_current;
	t_cd toolbox;

	data->i = 0;
	save_current = data->lst;
	tmp = NULL;
	if(path == NULL)
		return(-1);
	while(path[data->i] == ' ' || path[data->i] == '\t')
		data->i++;
	if(path[data->i]== '-')
	{
		while(path[data->i]== ' ' || path[data->i] == '\t')
			data->i++;
		if(path[data->i + 1] == '\0')
		{
			exec_cd_with_opt(data, tmp, save_current, toolbox.buffer);	
			return(1);
		}
		else
		{
			ft_printf("cd: string not in pwd: -\n");
			return(1);
		}
	}
	return (0);
}

int ft_current_directory(char *path,t_data *data)
{
	t_cd tool_box;
	t_list_arg *tmp;
	
	tmp = data->lst;
	init_tool_box(&tool_box);	
	if (ft_strstr(data->tokenizer->final_cmd, "cd") || (ft_strstr(data->tokenizer->final_cmd, "cd") && (data->tokenizer->final_cmd[2] == ' ' && data->tokenizer->final_cmd[3] == '\0')))
	{		
		tool_box.j = iterate_in_str(data->tokenizer->final_cmd);
		if(data->tokenizer->final_cmd[tool_box.i + 2] == '\0' || data->tokenizer->final_cmd[tool_box.j] == '\0')
		{
			no_arg(data, tmp, tool_box.path_hu);
			return(1);
		}
		if(cd_check_opt(path,data))
			return (1);
		if(chdir(path)== -1)
		{
			ft_printf("no such file or directory: %s\n",path);
			return (1);
		}
		getcwd(tool_box.buffer_old, 4096);
		if(chdir(path) == 0)
			return(exec_cd(data,tmp, tool_box.buffer,tool_box.buffer_old,4096),1);
	}
	return (0);
}


