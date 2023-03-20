/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_line_helper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etanguy <etanguy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 13:31:16 by etanguy           #+#    #+#             */
/*   Updated: 2023/03/20 13:40:05 by etanguy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>
#include "libftt/libft.h"

int	how_many_child(char *path)
{
	int	i;
	int	nb_child;

	i = 0;
	nb_child = 0;
	while (path[i])
	{
		if (path[i] == '/')
			nb_child++;
		i++;
	}
	return (nb_child);
}

int	change_path_value(int *pathl, char **split, char ***new_split, char **pthtc)
{
	int	i;

	i = 0;
	(*pathl) = how_many_child(split[0]);
	if ((*pathl) > 0)
	{
		(*pthtc) = ft_strdup(split[0]);
		if (!(*pthtc))
			return (0);
		(*new_split) = ft_split(split[0], '/');
		if (!(*new_split))
			return (0);
		free(split[0]);
		while ((*new_split)[i + 1])
			i++;
		split[0] = ft_strdup((*new_split)[i]);
		if (!(split[0]))
			return (free(*pthtc), 0);
		ft_free_dbchar_tab((*new_split), 0);
	}
	return (1);
}

t_command	empty_command(void)
{
	t_command	res;

	res.command = malloc(sizeof(char *));
	res.command = NULL;
	res.path = NULL;
	return (res);
}

int	path_exist(t_data *data)
{
	int	i;

	i = 0;
	while (data->env && data->env[i])
	{
		if (ft_strncmp(data->env[i], "PATH", 5) == '=')
			return (i);
		i++;
	}
	return (-1);
}
