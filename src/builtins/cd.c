#include "../../includes/minishell_lib.h"
#include <unistd.h>

t_list_arg *find_key_old_pwd(t_data *data)
{
	t_list_arg *tmp;
	tmp = data->lst;
	while(tmp)
	{
		if(ft_strcmp(data->lst->key_and_val[1], "OLDPWD"))
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
		if(ft_strcmp(data->lst->key_and_val[1], "PWD"))
			break;
		tmp = tmp->next;
	}
	return(tmp);
} 

void cd_check_opt(char *path, t_data *data)
{
	//check if '-'is found if true replace pwd by old path and so on.
	int i;
	i = 0;
	t_list_arg *tmp;
	t_list_arg *save_current;
	int buffer_size = 4096;
	char buffer[buffer_size];
	i = 2;
	ft_printf("XGOIN\n");
	ft_printf("ici : %s\n",path);
	while(path[i++])
	{
		ft_printf("YGOIN\n");
		if(path[i] == ' ' || path[i] == '\t')
		{
			while(path[i] == ' ' || path[i] == '\t')
				i++;
			if(path[i]== '-')
			{
				ft_printf("XGOIN\n");
				i++;
				while(path[i] == ' ' || path[i] == '\t')
					i++;
				if(path[i + 1] != '\0')
					break;
				else
				{
					tmp = find_key_old_pwd(data);
					save_current = find_key_pwd(data);
					chdir(tmp->key_and_val[1]);
					free(tmp->key_and_val[1]);
					tmp->key_and_val[1] = ft_strdup(save_current->key_and_val[1]);
					free(save_current->key_and_val[1]);
					getcwd(buffer, buffer_size);
					save_current->key_and_val[1] = ft_strdup(buffer);	
					// replace old by new & so on
				}
			}
		}
	}
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
	tmp = data->lst;
	i = 0;
	if (ft_strstr(data->tokenizer->final_cmd, "cd"))
	{
		
		cd_check_opt(path,data);
		if(chdir(path)== -1)
		{
			ft_printf("no such file or directory: %s\n",path);
			exit(1); //TO REMOOOOOVE
			return;
		}

		getcwd(buffer_old, buffer_size);
		if(chdir(path) == 0)
		{
			ft_printf("RETURN OF CHDIR : %d\n",chdir(path));
			tmp = find_key_pwd(data);
			ft_printf("TMP 1 : %s\n",tmp->key_and_val[1]);
			free(data->lst->key_and_val[i]);
			getcwd(buffer, buffer_size);
			tmp->key_and_val[i] = ft_strdup(buffer);
			tmp = find_key_old_pwd(data);
			ft_printf("TMP 2 : %s\n",tmp->key_and_val[1]);
			free(data->lst->key_and_val[i]);
			data->lst->key_and_val[i] = ft_strdup(buffer_old);
		}
	}


}


