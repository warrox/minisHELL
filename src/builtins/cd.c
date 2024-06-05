#include "../../includes/minishell_lib.h"

int find_key_old_pwd(t_data *data)
{
	int i;
	i = 0;
	while(data->lst->key_and_val[i])
	{
		if(ft_strcmp(data->lst->key_and_val[i], "OLDPWD"))
			break;
		i++;
	}
	return(i);
} 

int find_key_pwd(t_data *data)
{
	int i;
	i = 0;
	while(data->lst->key_and_val[i])
	{
		if(ft_strcmp(data->lst->key_and_val[i], "PWD"))
			break;
		i++;
	}
	return(i);
} 

void cd_check_opt(char *path, t_data *data)
{
	int i;
	i = 0;
	while(path[i++])
	{
		if(path[i] == ' ' || path[i] == '\t')
		{
			while(path[i] == ' ' || path[i] == '\t')
				i++;
			if(path[i]== '-')
			{
				i++;
				while(path[i] == ' ' || path[i] == '\t')
					i++;
				if(path[i + 1] != '\0')
					break;
				else
				{
					i = find_key_old_pwd(data);
					chdir(data->lst->key_and_val[1]);
					// replace old by new & so on
				}
			}
		}
	}
}

void ft_current_directoryi(char *path,t_data *data)
{
	// 1 copier le path absolut via getcwd et remplacer old_pwd
	// 2 chdir et check si ok 
	// si ok remplacer old_pwd et pwd
	int buffer_size = 4096;
	char buffer[buffer_size];
	char buffer_old[buffer_size];
	int i; 
	i = 0;
	if(chdir(path)== -1)
	{
		ft_printf("no such file or directory: %s\n",path);
		return;
	}

	getcwd(buffer_old, buffer_size);
	if(chdir(path) == 0)
	{
		cd_check_opt(path,data);
		i = find_key_pwd(data);
		//use getcwd stock dans buffer et dup buffer dans keyandval
		free(data->lst->key_and_val[i]);
		getcwd(buffer, buffer_size);
		data->lst->key_and_val[i] = ft_strdup(buffer);
		i = 0;
		i = find_key_old_pwd(data);
		free(data->lst->key_and_val[i]);
		data->lst->key_and_val[i] = ft_strdup(buffer_old);
	}

}


