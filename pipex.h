/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-carv <gde-carv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 21:53:45 by gde               #+#    #+#             */
/*   Updated: 2023/03/18 15:56:38 by gde-carv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

#define PIPEX_H

#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <errno.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include "libftt/libft.h"
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <sys/wait.h>

typedef	struct s_command
{
	char	**command;
	char	*path;
} t_command;

typedef struct s_data
{
	t_command	*command_line;
	int 	free_buf;
	int		split_len_cut;
	char	*actual_path;
	char	*last_path;
	char	**env;
	char	**instructions;
	char	***user_input_redirection;
	char	*num_redirection;
	int 	pos_num_redirection;
	int		nb_user_input_redirection;
	int		nb_pipe;
	int		num_command;
	int		nb_opperation_do;
	int		num_of_opperation;
	int		error_value;
	int 	double_backslash_path;
	int 	is_in_fork;
	int 	*fd_heredoc;

} t_data;

typedef struct s_forking
{
	int		**all_pipes;
	int		*all_pid;
} t_forking;

// Pipes

int			**creat_data_pipe(t_data *all);
void		close_unused_fd(t_data *all, int **all_pipes, int i);
void		free_pipes(int len, int **all_pipes);
int			count_pipe(t_data *all);
int			count_pipe(t_data *all);
void		free_pipes(int len, int **all_pipes);


// Utils

int			ft_free_dbchar_tab(char **str, int size);
int			ft_strtablen(char **str);

// Path

int			find_command_in_path(char *str, t_data *data, char **path_to_command);

// Command Line

int			make_command_line(int argc, char **argv, t_data *data);

// ParCings

int			parcing(int argc, char **argv, char **env, t_data *data);

// Debug

void 		printtab(char **strings);

// Execution

int			alpha_fork(t_data *all, t_command *tCommand);
void		what_do(t_data *all);
int			alloc_pipes_pid(int **all_pid, int ***all_pipes, t_data *all);
int			check_is_any_redirection(t_data *all, t_command *tC, int i, int **api);
int			is_other_pipe(int i, int **all_pipes, t_data *all, int *all_pid);
int			is_out_redirect(t_data *all, t_command *tCo, int **all_pipes, int i);
int			is_in_redirect(t_data *all, int i, int **all_pipes, t_command *tCo);
int			ft_terminal_command(t_command com, t_data *all);
int			is_redirection_after_pipe(t_data *all, t_command *tCommand, int *i);
int 		have_input_redirection(t_data *all, t_command *tCommand, int *i);
void		skip_output_redirect(t_data *all, t_command *tCommand, int *i);
int			**creat_all_pipe(t_data *all);
void		need_creat_file(char *folder_name);

#endif