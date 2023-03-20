/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_everythings_is_okay.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etanguy <etanguy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 11:31:59 by etanguy           #+#    #+#             */
/*   Updated: 2023/03/20 14:40:42 by etanguy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_permission_access(char *folder_name, int is_output)
{
	struct stat	sb;

	if (access(folder_name, F_OK) == 0)
	{
		stat(folder_name, &sb);
		if (!((sb.st_mode & S_IFMT) == S_IFDIR))
		{
			if ((access(folder_name, R_OK) == 0 && is_output == 1)
				|| (access(folder_name, W_OK) == 0 && is_output == 0))
				return (1);
			else
				write(2, "Permission denied\n", 18);
		}
		else
			write(2, "Is a directory\n", 15);
	}
	else
		write(2, "No such file or directory\n", 26);
	return (0);
}

int	check_logic_input(t_data *data, int argc)
{
	int	i;

	i = 0;
	while (i < argc - 1)
	{
		if (!data->command_line[i++].path)
		{
			write(2, "command not found\n", 18);
			return (0);
		}
	}
	if (!(check_permission_access(data->command_line[1].path, 0)
			&& check_permission_access(data->command_line[i - 1].path, 1)))
		return (0);
	return (1);
}
