/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_call.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-carv <gde-carv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 19:26:56 by gde-carv          #+#    #+#             */
/*   Updated: 2023/03/17 19:32:08 by gde-carv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int check_permission_access2(char *folder_path, char *folder_name)
{
	struct stat sb;
	if (access(folder_name, F_OK) == 0)
	{
		stat(folder_name, &sb);
		if (!((sb.st_mode & S_IFMT) == S_IFDIR))
		{
			if ((!folder_path || (folder_path && access(folder_path, X_OK) == 0)) &&
				access(folder_name, X_OK) == 0)
				return (free(folder_path), 1);
			else
				ft_putstr_fd("Permission denied", 2);
		}
		else
			ft_putstr_fd("Permission denied", 2);

	}
	else
		ft_putstr_fd("Permission denied", 2);
	return (free(folder_path), 0);
}

char	*ft_get_parent(char *path)
{
	char	*parent_path;
	int		i;
	int		j;

	j = 0;
	i = ft_strlen(path);
	while (i > 0 && path[i] != '/')
		i--;
	if (i == 0)
		return (NULL);
	parent_path = malloc(sizeof(char) * (i + 1));
	while (path[j] && j < i)
	{
		parent_path[j] = path[j];
		j++;
	}
	parent_path[j] = 0;
	return (parent_path);
}

int	ft_terminal_command(t_command com, t_data *all)
{
	if (!com.command && !com.path)
		return (0);
	if (!com.path)
	{
		write(2, com.command[0], ft_strlen(com.command[0]));
		write(2, ": command not found\n", 20);
		return (127);
	}
	if (!check_permission_access2(ft_get_parent(com.path), com.path))
		return (1);
	execve(com.path, com.command, all->env);
	return (0);
}
