/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dopereir <dopereir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 19:52:39 by dopereir          #+#    #+#             */
/*   Updated: 2025/01/12 17:39:51 by dopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
				ft_printf("Error\nMap must be surrounded by walls!\n");
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
	if (ft_toupper(c) == 'C')
		data->map.collectibles++;
	else if (ft_toupper(c) == 'E')
		data->map.exit_count++;
	else if (ft_toupper(c) == 'P')
	{
		data->map.player_count++;
		if (data->map.player_count <= 2)
		{
			data->map.player_x = x;
			data->map.player_y = y;
		}
	}
	else if (ft_toupper(c) == 'F')
	{
		data->map.enemy_count++;
	}
}

int	count_map_elements(t_data *data)
{
	int		x;
	int		y;

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
			if (!validate_map_chars(ft_toupper(data->map.grid[y][x])))
			{
				ft_printf("Error\nInvalid character at map[%d][%d]\n",
					(y + 1), (x + 1));
				return (clean_exit(data));
			}
			init_map_elements(data, data->map.grid[y][x], y, x);
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
		print_element_errors(data);
		return (0);
	}
	if (!validate_map_path(data))
	{
		ft_printf("Error\nMap doesn't have a valid path.\n");
		return (0);
	}
	if (data->map.width == data->map.height)
	{
		ft_printf("Error\nMap are not in a rectangular format\n");
		return (0);
	}
	return (1);
}
