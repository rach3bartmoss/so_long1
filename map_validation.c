/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dopereir <dopereir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 19:52:39 by dopereir          #+#    #+#             */
/*   Updated: 2025/01/06 00:55:34 by dopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libraries/libft/libft.h"
#include "so_long.h"

int	validate_map_chars(char c)
{
	return (c == '0' || c == '1' || c == 'C'
		|| c == 'E' || c == 'P' || c == 'F');
}

int	check_map_borders(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->map.height)
	{
		x = 0;
		while (x < data->map.width)
		{
			if ((y == 0 || y == data->map.height - 1
					|| x == 0 || x == data->map.width - 1)
				&& data->map.grid[y][x] != '1')
			{
				ft_printf("Error: Map must be surrounded by walls('1')\n");
				return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}

//inits
void	init_map_elements(t_data *data, char c, int y, int x)
{
	if (c == 'C')
		data->map.collectibles++;
	else if (c == 'E')
		data->map.exit_count++;
	else if (c == 'P')
	{
		data->map.player_count++;
		if (data->map.player_count <= 2)
		{
			data->map.player_x = x;
			data->map.player_y = y;
		}
	}
	else if (c == 'F')
	{
		data->map.enemy_count++;
	}
}

int	count_map_elements(t_data *data)
{
	int		x;
	int		y;
	char	c;

	data->map.collectibles = 0;
	data->map.exit_count = 0;
	data->map.player_count = 0;
	data->map.enemy_count = 0;
	y = 0;
	while (y < data->map.height)
	{
		x = 0;
		while (x < data->map.width)
		{
			c = data->map.grid[y][x];
			if (!validate_map_chars(c))
				return (0);
			init_map_elements(data, c, y, x);
			x++;
		}
		y++;
	}
	return (data->map.player_count <= 2);
}

int	validate_map(t_data *data)
{
	if (!check_map_borders(data) || !count_map_elements(data))
		return (0);
	if (data->map.collectibles == 0 || data->map.exit_count != 1
		|| data->map.player_count != 1)
	{
		ft_printf("Error: map must have 1>= collectible, 1 exit and 1 player\n");
		return (0);
	}
	if (!validate_map_path(data))
	{
		ft_printf("Error: Collectibles or the exit are not reachable.\n");
		return (0);
	}
	return (1);
}
