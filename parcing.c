/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-carv <gde-carv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 23:33:06 by gde-carv          #+#    #+#             */
/*   Updated: 2023/03/17 14:33:48 by gde-carv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	make_instruction_line(int argc, t_data *data)
{
	int	i;

	i = 1;
	data->instructions = malloc(sizeof(char *) * argc - 1);
	data->instructions[0] = ft_strdup("<");
	while (i < argc - 3)
	{
		data->instructions[i] = ft_strdup("|");
		i++;
	}
	data->instructions[i] = ft_strdup(">");
	data->instructions[i + 1] = NULL;
}

int	parcing(int argc, char **argv, char **env, t_data *data)
{
	data->env = env;
	make_command_line(argc, argv, data);
	make_instruction_line(argc, data);
	return (1);
}
