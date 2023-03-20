/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etanguy <etanguy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 23:38:33 by gde-carv          #+#    #+#             */
/*   Updated: 2023/03/20 13:32:20 by etanguy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftt/libft.h"
#include "pipex.h"
#include <stdio.h>

t_command	make_command(char *str, t_data *data, int yes)
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
	if (res.command && res.command[0] && !res.path && yes == 0)
		find_command_in_path(res.command[0], data, &(res.path));
	else if (!res.path)
		res.path = ft_strdup(command[0]);
	return (res);
}

void	swap_first_param(t_data *data)
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
	int	yes;

	i = 1;
	j = 0;
	data->command_line = malloc(sizeof(t_command) * (argc));
	if (!data->command_line)
		return (0);
	while (i < argc)
	{
		if (i == 1 || i == argc - 1)
			yes = 1;
		else
			yes = 0;
		data->command_line[j++] = make_command(argv[i++], data, yes);
		if (!data->command_line[j - 1].path && !data->command_line[j - 1].command)
			return (0);
	}
	j--;
	need_creat_file(data->command_line[j].path);
	swap_first_param(data);
	return (1);
}
