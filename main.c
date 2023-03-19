/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-carv <gde-carv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 23:01:28 by gde-carv          #+#    #+#             */
/*   Updated: 2023/03/19 19:46:05 by gde-carv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>
#include <stdlib.h>

void	setup(t_data *all)
{
	all->actual_path = NULL;
	all->num_command = 0;
	all->num_of_opperation = 0;
	all->instructions = NULL;
	all->user_input_redirection = NULL;
	all->nb_user_input_redirection = 0;
	all->error_value = 0;
	all->double_backslash_path = 0;
	all->free_buf = 0;
	all->num_redirection = NULL;
	all->pos_num_redirection = 0;
	all->is_in_fork = 0;
	all->fd_heredoc = NULL;
}

void	free_all(t_data *data, int argc)
{
	int	i;

	i = 0;
	while (i < argc - 1)
	{
		if (data->command_line[i].command)
			ft_free_dbchar_tab(data->command_line[i].command, 0);
		if (data->command_line[i].path)
			free(data->command_line[i].path);
		i++;
	}
	free(data->command_line);
	ft_free_dbchar_tab(data->instructions, 0);
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	setup(&data);
	if (argc < 5)
		return (ft_putstr_fd("Invalid Arguments\n", 2), 1);
	if (!parcing(argc, argv, env, &data))
		return (1);
	what_do(&data);
	free_all(&data, argc);
}
