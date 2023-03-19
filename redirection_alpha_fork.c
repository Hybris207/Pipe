/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_alpha_fork.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-carv <gde-carv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 19:24:45 by gde-carv          #+#    #+#             */
/*   Updated: 2023/03/19 17:40:21 by gde-carv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	is_in_redirect(t_data *all, int i, int **all_pipes, t_command *tCo)
{
	int	tmp;

	tmp = 0;
	if (all->instructions[all->num_of_opperation]
		&& (ft_strcmp(all->instructions[all->num_of_opperation], "<")
			|| ft_strcmp(all->instructions[all->num_of_opperation], "<<")))
	{
		if (i < count_pipe(all))
		{
			if (dup2(all_pipes[i][1], 1) == -1)
				return (free_pipes(count_pipe(all), all_pipes), -1);
			close(all_pipes[i][1]);
		}
		if (i - 1 >= 0)
			close(all_pipes[i - 1][0]);
		if (have_input_redirection(all, tCo, &tmp) == 0)
			return (free_pipes(count_pipe(all), all_pipes), -1);
	}
	return (tmp);
}

int	is_out_redirect(t_data *all, t_command *tCo, int **all_pipes, int i)
{
	int	tmp;

	tmp = 0;
	if (all->instructions[all->num_of_opperation]
		&& (ft_strcmp(all->instructions[all->num_of_opperation], ">")
			|| ft_strcmp(all->instructions[all->num_of_opperation], ">>")))
	{
		if (is_redirection_after_pipe(all, tCo, &tmp) == 0)
			return (free_pipes(count_pipe(all), all_pipes), -1);
		if (i < count_pipe(all))
			close(all_pipes[i][1]);
	}
	else if (i < count_pipe(all))
	{
		if (dup2(all_pipes[i][1], 1) == -1)
			return (free_pipes(count_pipe(all), all_pipes), -1);
		close(all_pipes[i][1]);
	}
	return (tmp);
}

int	is_other_pipe(int i, int **all_pipes, t_data *all, int *all_pid)
{
	if (i - 1 >= 0)
	{
		if (dup2(all_pipes[i - 1][0], 0) == -1)
			return (free_pipes(count_pipe(all), all_pipes),
					free(all_pid), 0);
		close(all_pipes[i - 1][0]);
	}
	return (1);
}
