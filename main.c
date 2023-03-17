/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-carv <gde-carv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 23:01:28 by gde-carv          #+#    #+#             */
/*   Updated: 2023/03/17 19:23:05 by gde-carv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void printtab(char **strings) {
    int i;
    
    i = 0;
    while (strings[i] != NULL)
    {
        printf("%s\n", strings[i]);
        i++;
    }
}

void    setup(t_data *all)
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

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	setup(&data);
	if (argc < 5)
		return (ft_putstr_fd("Invalid Arguments\n", 2), 1);
	if (!parcing(argc, argv, env, &data))
		return (1);
    what_do(&data);
}
