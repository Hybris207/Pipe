/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-carv <gde-carv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 00:44:50 by gde-carv          #+#    #+#             */
/*   Updated: 2023/03/17 14:50:21 by gde-carv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int		path_exist(t_data *data)
{
	int i;

	i = 0;
	while (data->env && data->env[i])
	{
		if (ft_strncmp(data->env[i], "PATH", 5) == '=')
			return (i);
		i++;
	}
	return (-1);
}

char    *path_value(char **env)
{
    int        i;
    char    *path;

    i = 0;
    while (ft_strncmp(env[i], "PATH", 4) != 0)
        i++;
    path = ft_strdup(env[i] + 5);
    return (path);
}

int which_path(char	**command_path, char **all_path, char *str)
{
	char 	*tmp;
	char 	*tmp2;
	int		i;

	i = 0;
	while(all_path && all_path[i])
	{
		tmp = ft_strjoin("/", str);
		tmp2 = ft_strjoin(all_path[i], tmp);
		if (!tmp2)
			return (free(tmp), 0);
		*command_path = ft_strdup(tmp2);
		free(tmp2);
		free(tmp);
		if (!(*command_path))
			return (2);
		if (access(*command_path, F_OK) == 0)
			return (1);
		free(*command_path);
		i++;
	}
	return (0);
}

int	find_command_in_path(char *str, t_data *data, char **path_to_command)
{
    char	*path;
    char	**all_path;
    char	*command_path;

	all_path = NULL;
    if (path_exist(data) != -1)
	{
		path = path_value(data->env);
		all_path = ft_split(path, ':');
		free(path);
		if (!all_path)
			return (free(all_path), 0);
		if (which_path(&command_path, all_path, str) == 1)
		{
			*path_to_command = command_path;
			return (ft_free_dbchar_tab(all_path, 0), 1);
		}
		ft_free_dbchar_tab(all_path, 0);
	}
	*path_to_command = NULL;
    return (1);
}
