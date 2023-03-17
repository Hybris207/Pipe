/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-carv <gde-carv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 23:38:33 by gde-carv          #+#    #+#             */
/*   Updated: 2023/03/17 15:05:45 by gde-carv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_command	make_command(char *str, t_data *data)
{
	t_command	res;
	char		**command;
	char		*path;

	path = NULL;
	command = ft_split(str, ' ');
	res.command = command;
	if (res.command && res.command[0])
		find_command_in_path(res.command[0], data, &path);
	return (res);
}

t_command	empty_command(char *str)
{
	t_command	res;

	res.command = malloc(sizeof(char *));
	res.command[0] = str;
	res.path = NULL;
	return (res);
}

int	make_command_line(int argc, char **argv, t_data *data)
{
	int	i;
	int	j;

	i = 2;
	j = 1;
	data->command_line = malloc(sizeof(t_command) * (argc));
	data->command_line[0] = empty_command(argv[1]);
	while (i < argc - 1)
	{
		data->command_line[j++] = make_command(argv[i++], data);
	}
	data->command_line[j] = empty_command(argv[argc - 1]);
	data->command_line[j + 1] = empty_command(NULL);
	return (0);
}