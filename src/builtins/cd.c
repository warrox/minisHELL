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
	//check if '-'is found if true replace pwd by old path and so on.
	int i;
	i = 0;
	t_list_arg *tmp;
	t_list_arg *save_current;
	int buffer_size = 4096;
	char buffer[buffer_size];
	save_current = data->lst;
	while(path[i] == ' ' || path[i] == '\t')
		i++;
	if(path[i]== '-')
	{
		while(path[i]== ' ' || path[i] == '\t')
			i++;
		if(path[i + 1] == '\0')
		{
			tmp = find_key_old_pwd(data);
			save_current = find_key_pwd(data);
			chdir(tmp->key_and_val[1]);
			free(tmp->key_and_val[1]);
			tmp->key_and_val[1] = ft_strdup(save_current->key_and_val[1]);
			free(save_current->key_and_val[1]);
			getcwd(buffer, buffer_size);
			save_current->key_and_val[1] = ft_strdup(buffer);	
			ft_printf("%s\n",save_current->key_and_val[0]);
			return(1);
			// replace old by new & so on
		}
		else
		{
			ft_printf("cd: string not in pwd: -\n");
			return(1);
		}
	}
	return (0);
}

void ft_current_directory(char *path,t_data *data)
{
	// 1 copier le path absolut via getcwd et remplacer old_pwd
	// 2 chdir et check si ok 
	// si ok remplacer old_pwd et pwd
	// if cd with no arg chdir goin to home root.
	// cd /home/$user
	int buffer_size = 4096;
	t_list_arg *tmp;
	char buffer[buffer_size];
	char buffer_old[buffer_size];
	int i; 
	char path_hu[4096];
	tmp = data->lst;
	i = 0;
	if (ft_strstr(data->tokenizer->final_cmd, "cd") || (ft_strstr(data->tokenizer->final_cmd, "cd") && (data->tokenizer->final_cmd[2] == ' ' && data->tokenizer->final_cmd[3] == '\0')))
	{	
		int j = 3;	
		while(data->tokenizer->final_cmd[j] == ' ')
			j++;
		if(data->tokenizer->final_cmd[i + 2] == '\0' || data->tokenizer->final_cmd[j] == '\0')
		{
			tmp = find_key_user(data);
			if(tmp == NULL)
				return;
			ft_strcpy(path_hu, "/home/");
			ft_strlcat(path_hu, tmp->key_and_val[1], (ft_strlen(path_hu) + ft_strlen(tmp->key_and_val[1])+ 1));
			chdir(path_hu);
			return;
		}
		if(cd_check_opt(path,data))
		{
			return;
		}
		if(chdir(path)== -1)
		{
			ft_printf("no such file or directory: %s\n",path);
			return;
		}

		getcwd(buffer_old, buffer_size);
		if(chdir(path) == 0)
		{
			tmp = find_key_pwd(data);
			free(data->lst->key_and_val[1]);
			getcwd(buffer, buffer_size);
			tmp->key_and_val[1] = ft_strdup(buffer);
			tmp = find_key_old_pwd(data);
			data->lst->key_and_val[1] = ft_strdup(buffer_old);
		}
	}


}


