/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tile_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dopereir <dopereir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 19:53:22 by dopereir          #+#    #+#             */
/*   Updated: 2025/01/05 19:53:24 by dopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libraries/libft/libft.h"
#include "minilibx-linux/mlx.h"
#include "so_long.h"
#include <complex.h>
#include <string.h>

void	init_tiles(t_data *data)
{
	data->tiles.floor1 = mlx_xpm_file_to_image(data->mlx,
			"textures/tiles/floor1.xpm",
			&data->tiles.width, &data->tiles.height);
	data->tiles.wall = mlx_xpm_file_to_image(data->mlx,
			"textures/tiles/empty_space1.xpm",
			&data->tiles.width, &data->tiles.height);
	data->tiles.wall2 = mlx_xpm_file_to_image(data->mlx,
			"textures/tiles/blue_flame1.xpm",
			&data->tiles.width, &data->tiles.height);
	data->tiles.exit = mlx_xpm_file_to_image(data->mlx,
			"textures/tiles/exit.xpm",
			&data->tiles.width, &data->tiles.height);
	data->tiles.collectible = mlx_xpm_file_to_image(data->mlx,
			"textures/tiles/collectible_tile1.xpm",
			&data->tiles.width, &data->tiles.height);
	if (!data->tiles.floor1 || !data->tiles.wall || !data->tiles.wall2
		|| !data->tiles.exit || !data->tiles.collectible)
	{
		ft_printf("Error: Failed to load tiles.\n");
		exit(EXIT_FAILURE);
	}
}

// Decorative torch wall on every 3rd tile if conditions are met
// Standard wall for other '0' tiles
void	*tile_variation(t_data *data, int x, int y)
{
	if (y < data->map.height - 1
		&& data->map.grid[y + 1][x] == '1' && x % 6 == 0)
	{
		return (data->tiles.wall2);
	}
	else
	{
		return (data->tiles.wall);
	}
}

void	render_tiles_helper(t_data *data, int x, int y)
{
	void	*tile;

	if (data->map.grid[y][x] != '1'
		&& data->map.grid[y][x] != 'E' && data->map.grid[y][x] != 'C')
	{
		tile = tile_variation(data, x, y);
		mlx_put_image_to_window(data->mlx, data->win, tile,
			x * TILE_SIZE, y * TILE_SIZE);
	}
	else if (data->map.grid[y][x] == '1')
		mlx_put_image_to_window(data->mlx, data->win,
			data->tiles.floor1,
			x * TILE_SIZE, y * TILE_SIZE);
	else if (data->map.grid[y][x] == 'E')
		mlx_put_image_to_window(data->mlx, data->win, data->tiles.exit,
			x * TILE_SIZE, y * TILE_SIZE);
	else if (data->map.grid[y][x] == 'C')
		mlx_put_image_to_window(data->mlx, data->win,
			data->tiles.collectible,
			x * TILE_SIZE, y * TILE_SIZE);
}

void	render_tiles(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (y < data->map.height)
	{
		x = 0;
		while (x < data->map.width)
		{
			render_tiles_helper(data, x, y);
			x++;
		}
		y++;
	}
}

void	clean_tiles(t_data *data)
{
	if (data->tiles.floor1)
	{
		mlx_destroy_image(data->mlx, data->tiles.floor1);
		data->tiles.floor1 = NULL;
	}
	if (data->tiles.wall)
	{
		mlx_destroy_image(data->mlx, data->tiles.wall);
		data->tiles.wall = NULL;
	}
	if (data->tiles.wall2)
	{
		mlx_destroy_image(data->mlx, data->tiles.wall2);
		data->tiles.wall2 = NULL;
	}
	if (data->tiles.exit)
	{
		mlx_destroy_image(data->mlx, data->tiles.exit);
		data->tiles.exit = NULL;
	}
	if (data->tiles.collectible)
	{
		mlx_destroy_image(data->mlx, data->tiles.collectible);
		data->tiles.collectible = NULL;
	}
}
