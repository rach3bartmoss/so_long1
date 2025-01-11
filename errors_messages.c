/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_messages.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dopereir <dopereir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 22:44:26 by dopereir          #+#    #+#             */
/*   Updated: 2025/01/08 22:44:29 by dopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libraries/libft/libft.h"
#include "so_long.h"
#include <string.h>

void	print_error_and_exit(char *error_msg, t_data *data)
{
	if (error_msg)
		ft_printf("Error\n%s\n", error_msg);
	clean_exit(data);
	exit (EXIT_FAILURE);
}

void	clean_map_loading_helper(t_data *data, int fd, char *line)
{
	char	*temp;

	while (1)
	{
		temp = get_next_line(fd);
		if (temp == NULL)
			break ;
		free (temp);
	}
	free (line);
	close (fd);
	clean_exit(data);
}

void	print_element_errors(t_data *data)
{
	if (data->map.exit_count != 1)
		ft_printf("Error:\nMap must have exactly one exit.\n");
	if (data->map.player_count != 1)
		ft_printf("Error:\nMap must have exactly one starting position.\n");
	if (data->map.collectibles == 0)
		ft_printf("Error:\nMap must have at least one collectible.\n");
}
