/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-carv <gde-carv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 23:38:33 by gde-carv          #+#    #+#             */
/*   Updated: 2023/03/19 17:50:23 by gde-carv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftt/libft.h"
#include "pipex.h"
#include <stdio.h>

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

t_command	make_command(char *str, t_data *data)
{
	t_command	res;
	char		**command;
	char		**new_split;
	int			pathl;

	res.path = NULL;
	command = ft_split(str, ' ');
	pathl = how_many_child(command[0]);
	if (!change_path_value(&pathl, command, &new_split, &(res.path)))
		return (res);
	res.command = command;
	if (res.command && res.command[0] && !res.path)
		find_command_in_path(res.command[0], data, &(res.path));
	if (!res.path)
		res.path = command[0];
	return (res);
}

t_command	empty_command(void)
{
	t_command	res;

	res.command = malloc(sizeof(char *));
	res.command = NULL;
	res.path = NULL;
	return (res);
}

void swap_first_param(t_data *data)
{
	t_command	tmp;

	tmp = data->command_line[0];
	data->command_line[0] = data->command_line[1];
	data->command_line[1] = tmp;
}

void	need_creat_file(char *folder_name)
{
	int			fd;
	struct stat	sb;

	sb.st_mode = 0;
	stat(folder_name, &sb);
	if (!access(folder_name, F_OK) == 0)
	{
		fd = open(folder_name, O_RDWR | O_CREAT, S_IRUSR
			| S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
		close(fd);
	}
}

int	check_file_output(int i, int j, char **split, t_command *command_line)
{
	need_creat_file(split[i]);
	if (command_line[j].path)
		free(command_line[j].path);
	command_line[j].path = ft_strdup(split[i]);
	if (!command_line[j].path)
		return (0);
	return (1);
}

int	make_command_line(int argc, char **argv, t_data *data)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	data->command_line = malloc(sizeof(t_command) * (argc));
	while (i < argc)
		data->command_line[j++] = make_command(argv[i++], data);
	j--;
	need_creat_file(data->command_line[j].path);
	swap_first_param(data);
	return (0);
}
