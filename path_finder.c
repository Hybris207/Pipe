/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etanguy <etanguy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 00:44:50 by gde-carv          #+#    #+#             */
/*   Updated: 2023/03/20 13:39:28 by etanguy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdlib.h>

char	*path_value(char **env)
{
	int		i;
	char	*path;

	i = 0;
	while (env && env[i] && ft_strncmp(env[i], "PATH", 4) != 0)
		i++;
	if (!env[i])
		path = NULL;
	else
		path = ft_strdup(env[i] + 5);
	return (path);
}

static int	creat_path_name(char *str, char **all_path, int i, char **cmd_path)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strjoin("/", str);
	if (!tmp)
		return (2);
	tmp2 = ft_strjoin(all_path[i], tmp);
	if (!tmp2)
		return (free(tmp), 2);
	*cmd_path = ft_strdup(tmp2);
	free(tmp2);
	free(tmp);
	if (!(*cmd_path))
		return (2);
	return (1);
}

static int	check_path_exist(t_data *all, char **path, char ***all_path)
{
	*path = path_value(all->env);
	if (!(*path))
		return (0);
	*all_path = ft_split(*path, ':');
	if (!(*all_path))
		return (free(*path), 0);
	free(*path);
	return (1);
}

static int	which_path(char	**command_path, int *i, char **all_path, char *str)
{
	while (all_path && all_path[*i])
	{
		if (creat_path_name(str, all_path, *i, command_path) == 2)
			return (2);
		if (access(*command_path, F_OK) == 0)
			return (ft_free_dbchar_tab(all_path, 0), 1);
		free(*command_path);
		(*i)++;
	}
	return (0);
}

int	find_command_in_path(char *str, t_data *all, char **path_to_command)
{
	int		i;
	char	*path;
	char	**all_path;
	char	*command_path;
	int		check;

	i = 0;
	all_path = NULL;
	if (!check_path_exist(all, &path, &all_path))
		return (0);
	check = which_path(&command_path, &i, all_path, str);
	if (check == 1)
	{
		*path_to_command = command_path;
		return (1);
	}
	else if (check == 2)
		return (0);
	if (all_path)
		ft_free_dbchar_tab(all_path, 0);
	*path_to_command = NULL;
	return (1);
}
