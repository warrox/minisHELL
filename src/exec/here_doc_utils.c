/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 17:34:00 by cyferrei          #+#    #+#             */
/*   Updated: 2024/06/18 17:34:58 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 09:19:02 by cyferrei          #+#    #+#             */
/*   Updated: 2024/04/16 15:31:43 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

int	exit_free_error(char *str)
{
	if (str)
		free(str);
	exit(1);
}

int	find_new_line(char *str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			if (str[i] == '\n')
				return (1);
			i++;
		}
	}
	return (0);
}

char	*obtain_line(char *str)
{
	int		i;
	int		j;
	char	*new_line;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	new_line = (char *)malloc(i + 1);
	if (!new_line)
		return (NULL);
	while (str[j] != '\n' && str[j] != '\0')
	{
		new_line[j] = str[j];
		j++;
	}
	new_line[j] = '\0';
	return (new_line);
}

int	gnl_hd(int fd, char **line)
{
	char	*buffer;
	int		read_line;

	if (fd < 0 || BUFFER_SIZE < 1 || !line)
		return (-1);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (exit_free_error(buffer));
	read_line = 1;
	while (read_line != 0 && (!*buffer || buffer[ft_strlen(buffer)
				- 1] != '\n'))
	{
		read_line = read(fd, buffer, BUFFER_SIZE);
		if (read_line == 0)
		{
			*line = buffer;
			return (0);
		}
		if (read_line < 0)
			exit_free_error(buffer);
	}
	buffer[ft_strlen(buffer) - 1] = 0;
	*line = buffer;
	return (1);
}
