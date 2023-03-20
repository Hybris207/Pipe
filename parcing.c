/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etanguy <etanguy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 23:33:06 by gde-carv          #+#    #+#             */
/*   Updated: 2023/03/20 13:40:27 by etanguy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	make_instruction_line(int argc, t_data *data)
{
	int	i;

	i = 1;
	data->instructions = malloc(sizeof(char *) * argc - 1);
	if (!data->instructions)
		return (0);
	data->instructions[0] = ft_strdup("<");
	if (!data->instructions[0])
		return (0);
	while (i < argc - 3)
	{
		data->instructions[i] = ft_strdup("|");
		if (!data->instructions[i])
			return (0);
		i++;
	}
	data->instructions[i] = ft_strdup(">");
	if (!data->instructions[i])
		return (0);
	data->instructions[i + 1] = NULL;
	return (1);
}

int	parcing(int argc, char **argv, char **env, t_data *data)
{
	data->env = env;
	if (!make_command_line(argc, argv, data))
		return (0);
	if (!make_instruction_line(argc, data))
		return (0);
	if (!check_logic_input(data, argc))
		return (0);
	return (1);
}
