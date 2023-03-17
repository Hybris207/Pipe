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

	command = ft_split(str, ' ');
	res.command = command;
	if (res.command && res.command[0])
		find_command_in_path(res.command[0], data, &(res.path));
	return (res);
}

t_command	empty_command()
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

int	make_command_line(int argc, char **argv, t_data *data)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	data->command_line = malloc(sizeof(t_command) * (argc));
	while (i < argc)
	{
		data->command_line[j] = make_command(argv[i], data);
		j++;
		i++;
	}
	j--;
	data->command_line[j].path = data->command_line[j].command[0];
	data->command_line[0].path = data->command_line[0].command[0];
	swap_first_param(data);
	return (0);
}