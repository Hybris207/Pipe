/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etanguy <etanguy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 13:13:58 by gde-carv          #+#    #+#             */
/*   Updated: 2023/03/20 11:37:27 by etanguy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	what_do(t_data *all)
{
	t_command	*tcommand;

	tcommand = all->command_line;
	alpha_fork(all, tcommand);
}

int	ft_strtablen(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_free_dbchar_tab(char **str, int size)
{
	int	i;

	i = size;
	if (i == 0)
		i = ft_strtablen(str) - 1;
	while (i >= 0 && str[i])
		free(str[i--]);
	free(str);
	str = NULL;
	return (0);
}

void	skip_output_redirect(t_data *all, t_command *tCommand, int *i)
{
	int	file_fd;

	file_fd = 0;
	while (all->instructions[all->num_of_opperation + 1]
		&& (ft_strcmp(all->instructions[all->num_of_opperation + 1], ">")
			|| ft_strcmp(all->instructions[all->num_of_opperation + 1], ">>")))
	{
		if (ft_strcmp(all->instructions[all->num_of_opperation], ">"))
			file_fd = open(tCommand[all->num_command + 1].path,
					O_WRONLY | O_TRUNC);
		else if (ft_strcmp(all->instructions[all->num_of_opperation], ">>"))
			file_fd = open(tCommand[all->num_command + 1].path,
					O_WRONLY | O_APPEND);
		if (file_fd != -1)
			close(file_fd);
		all->num_of_opperation++;
		all->num_command++;
		(*i)++;
	}
}

int	**creat_all_pipe(t_data *all)
{
	int	i;
	int	**pipes;

	i = 0;
	pipes = malloc(sizeof(int *) * count_pipe(all));
	if (!pipes)
		return (NULL);
	while (i < count_pipe(all))
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i])
		{
			while (i - 1 >= 0)
			{
				i--;
				free(pipes[i]);
			}
			free(pipes);
			return (NULL);
		}
		pipe(pipes[i]);
		i++;
	}
	return (pipes);
}
