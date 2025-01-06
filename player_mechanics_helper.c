/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_mechanics_helper.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dopereir <dopereir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 19:53:02 by dopereir          #+#    #+#             */
/*   Updated: 2025/01/05 19:53:04 by dopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	handle_keyrelease(int keycode, t_data *data)
{
	ft_printf("Key release detected: %d\n", keycode);
	if (keycode == KEY_RIGHT || keycode == KEY_LEFT
		|| keycode == KEY_UP || keycode == KEY_DOWN)
	{
		ft_printf("entered the key release function inner condition\n");
		handle_player_state(data, 'I');
		update_player_animation(data);
	}
	return (0);
}

void	check_collision(t_data *data)
{
	int		player_x;
	int		player_y;
	char	tile;

	player_x = data->player.x;
	player_y = data->player.y;
	tile = data->map.grid[player_y][player_x];
	if (tile == 'C')
	{
		data->map.grid[player_y][player_x] = '0';
		data->map.collectibles--;
		if (data->map.collectibles == 0)
		{
			data->exit_open = 1;
			open_exit(data);
		}
	}
	else if (tile == 'E')
	{
		if (data->exit_open)
			win_game(data);
	}
}

void	open_exit(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (y < data->map.height)
	{
		x = 0;
		while (x < data->map.width)
		{
			if (data->map.grid[y][x] == 'E')
			{
				mlx_put_image_to_window(data->mlx, data->win, data->tiles.exit,
					x * TILE_SIZE, y * TILE_SIZE);
			}
			x++;
		}
		y++;
	}
}

/*void	render_move_count(t_data *data)
{
	char	*move_text;
	int		x_start;
	int		y_start;
	int		width;
	int		height;
	int		bg_color;

	move_text = ft_itoa(data->moves);
	x_start = 0;
	y_start = 0;
	width = 100;
	height = 20;
	bg_color = 0x000000;

	for (int y = y_start; y < y_start + height; y++)
	{
		for (int x = x_start; x < x_start + width; x++)
		{
			mlx_pixel_put(data->mlx, data->win, x, y, bg_color);
		}
	}
	mlx_string_put(data->mlx, data->win, x_start,
	y_start + 10, 0xFFFFFF, "Moves:");
	mlx_string_put(data->mlx, data->win, x_start + 70,
	y_start + 10, 0xFFFFFF, move_text);

	free(move_text);
	}*/

void	win_game(t_data *data)
{
	mlx_string_put(data->mlx, data->win, data->map.width * TILE_SIZE / 2 - 100,
		data->map.height * TILE_SIZE / 2, 0xFFD700, "Victory Achieved!");
	data->game_won = 1;
	ft_printf("You Won!\n");
}
