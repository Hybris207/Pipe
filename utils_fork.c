/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_fork.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-carv <gde-carv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 15:29:54 by gde-carv          #+#    #+#             */
/*   Updated: 2023/03/17 19:38:56 by gde-carv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	count_pipe(t_data *all)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while(all->instructions && all->instructions[i])
	{
		if (ft_strcmp(all->instructions[i], "|"))
			res++;
		i++;
	}
	return (res);
}

void	free_pipes(int len, int **all_pipes)
{
	int	i;

	i = 0;
	while (i < len)
	{
		free(all_pipes[i]);
		i++;
	}
	free(all_pipes);
}

void	close_unused_fd(t_data *all, int **all_pipes, int i)
{
	int	j;

	j = 0;
	all->is_in_fork = 1;
	while (j < count_pipe(all))
	{
		if (j != i)
			close(all_pipes[j][1]);
		if (j != i - 1)
			close(all_pipes[j][0]);
		j++;
	}
}

int	alloc_pipes_pid(int **all_pid, int ***all_pipes, t_data *all)
{
	*all_pipes = creat_all_pipe(all);
	if (!(*all_pipes))
		return (0);
	(*all_pid) = malloc((count_pipe(all) + 1) * sizeof(int));
	if (!(*all_pid))
		return (free_pipes(count_pipe(all), *all_pipes), 0);
	return (1);
}

int	check_is_any_redirection(t_data *all, t_command *tC, int i, int **api)
{
	int	tmp;

	tmp = is_in_redirect(all, i, api, tC);
	if (tmp == -1)
		return (-1);
	tmp = is_out_redirect(all, tC, api, i);
	if (tmp == -1)
		return (-1);
	return (tmp);
}
