/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-carv <gde-carv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 23:15:15 by gde-carv          #+#    #+#             */
/*   Updated: 2023/03/17 19:40:37 by gde-carv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	**creat_data_pipe(t_data *all)
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
