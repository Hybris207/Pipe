#include "pipex.h"

void	end_fork(t_data *all, int *all_pid, int **all_pipes)
{
	int	i;
	int	ret_value;

	i = 0;
	ret_value = 0;
	while (i < count_pipe(all))
	{
		close(all_pipes[i][0]);
		close(all_pipes[i][1]);
		i++;
	}
	i = 0;
	while (i < (count_pipe(all) + 1))
	{
		waitpid(all_pid[i], &ret_value, 0);
		i++;
	}
	free_pipes(count_pipe(all), all_pipes);
	free(all_pid);
}

void	value_incremantation(t_data *all, int *i)
{
	while (all->instructions[all->num_of_opperation]
		   && (ft_strcmp(all->instructions[all->num_of_opperation], "<")
			   || ft_strcmp(all->instructions[all->num_of_opperation], "<<")))
	{
		if (ft_strcmp(all->instructions[all->num_of_opperation], "<<"))
		{
			close(all->fd_heredoc[all->nb_user_input_redirection]);
			all->nb_user_input_redirection++;
		}
		all->num_of_opperation++;
		all->num_command++;
	}
	while (all->instructions[all->num_of_opperation]
		   && (ft_strcmp(all->instructions[all->num_of_opperation], ">")
			   || ft_strcmp(all->instructions[all->num_of_opperation], ">>")))
	{
		all->num_of_opperation++;
		all->num_command++;
	}
	all->num_of_opperation++;
	all->num_command++;
	(*i)++;
}

static int	return_start_value(t_data *all, int ***api, int **aid)
{
	if (!alloc_pipes_pid(aid, api, all))
		return (0);
	return (2);
}

static int	child_process(t_data *all, t_command *tCommand, t_forking *pip, int i)
{
	int tmp;

	while (i < (count_pipe(all) + 1))
	{
		pip->all_pid[i] = fork();
		if (pip->all_pid[i] == -1)
			return (0);
		if (pip->all_pid[i] == 0)
		{
			close_unused_fd(all, pip->all_pipes, i);
			tmp = check_is_any_redirection(all, tCommand, i, pip->all_pipes);
			if (tmp == -1)
				return (free(pip->all_pid), free_pipes(count_pipe(all), pip->all_pipes), 0);
			if (is_other_pipe(i, pip->all_pipes, all, pip->all_pid) == 0)
				return (free(pip->all_pid), free_pipes(count_pipe(all), pip->all_pipes), 0);
			tmp = ft_terminal_command(tCommand[all->num_command - tmp], all);
			return (free_pipes(count_pipe(all), pip->all_pipes),
					free(pip->all_pid), tmp);
		}
		value_incremantation(all, &i);
	}
	return (-5);
}

int	alpha_fork(t_data *all, t_command *tCommand)
{
	int			*all_pid;
	int			**all_pipes;
	int			i;
	int			tmp;
	t_forking	pid_pipes;

	tmp = return_start_value(all, &all_pipes, &all_pid);
	pid_pipes.all_pipes = all_pipes;
	pid_pipes.all_pid = all_pid;
	if (tmp < 2)
		return (tmp);
	i = 0;
	tmp = child_process(all, tCommand, &pid_pipes, i);
	if (tmp != -5)
		return (tmp);
	end_fork(all, all_pid, all_pipes);
	return (1);
}
