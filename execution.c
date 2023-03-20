/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etanguy <etanguy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 15:16:19 by gde-carv          #+#    #+#             */
/*   Updated: 2023/03/20 11:35:19 by etanguy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	go_last_input_redirect(int *i, t_data *all)
{
	while (all->instructions[all->num_of_opperation + 1]
		&& (ft_strcmp(all->instructions[all->num_of_opperation + 1], "<")
			|| ft_strcmp(all->instructions[all->num_of_opperation + 1], "<<")))
	{
		if (ft_strcmp(all->instructions[all->num_of_opperation], "<<"))
		{
			close(all->fd_heredoc[all->nb_user_input_redirection]);
			all->nb_user_input_redirection++;
		}
		all->num_of_opperation++;
		all->num_command++;
		(*i)++;
	}
}

static int	is_redirection_after(t_data *all, t_command *tCommand, int *j)
{
	if (all->instructions[all->num_of_opperation + 1]
		&& (ft_strcmp(all->instructions[all->num_of_opperation + 1], ">")
			|| ft_strcmp(all->instructions[all->num_of_opperation + 1], ">>")))
	{
		all->num_of_opperation++;
		all->num_command++;
		(*j)++;
		if (is_redirection_after_pipe(all, tCommand, j) == 0)
			return (0);
	}
	return (1);
}

static int	what_input_redirect(t_data *all, t_command *tCommand, int j)
{
	int	fd;

	if (ft_strcmp(all->instructions[all->num_of_opperation - j], "<"))
	{
		fd = open(tCommand[all->num_command + 1 - j].path, O_RDONLY);
		if (dup2(fd, 0) == -1)
			return (close(fd), 0);
		close(fd);
	}
	else
	{
		if (dup2(all->fd_heredoc[all->nb_user_input_redirection], 0) == -1)
			return (0);
		close(all->fd_heredoc[all->nb_user_input_redirection]);
	}
	return (1);
}

int	is_redirection_after_pipe(t_data *all, t_command *tCommand, int *i)
{
	int	file_fd;

	file_fd = -1;
	skip_output_redirect(all, tCommand, i);
	if (ft_strcmp(all->instructions[all->num_of_opperation], ">"))
		file_fd = open(tCommand[all->num_command + 1].path,
				O_WRONLY | O_TRUNC);
	else
		file_fd = open(tCommand[all->num_command + 1].path,
				O_WRONLY | O_APPEND);
	if (dup2(file_fd, 1) == -1)
		return (close(file_fd), 0);
	close(file_fd);
	all->num_of_opperation++;
	all->num_command++;
	(*i)++;
	return (1);
}

int	have_input_redirection(t_data *all, t_command *tCommand, int *i)
{
	int	j;

	j = 0;
	if (all->instructions[all->num_of_opperation]
		&& (ft_strcmp(all->instructions[all->num_of_opperation], "<")
			|| ft_strcmp(all->instructions[all->num_of_opperation], "<<")))
	{
		go_last_input_redirect(i, all);
		if (is_redirection_after(all, tCommand, &j) == 0)
			return (0);
		if (what_input_redirect(all, tCommand, j) == 0)
			return (0);
		all->error_value
			= ft_terminal_command(tCommand[all->num_command - (*i) - j], all);
		return (0);
	}
	return (1);
}
