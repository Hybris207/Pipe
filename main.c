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

void    setup(t_data *data)
{
    data->nb_opperation_do = 0;
    data->num_redirection = 0;
    data->nb_pipe = 0;
    data->nb_user_input_redirection = 0;
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	if (argc < 5)
		return (ft_putstr_fd("Invalid Arguments\n", 2), 1);
	if (!parcing(argc, argv, env, &data))
		return (1);
    what_do(&data);
}
