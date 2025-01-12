/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_mechanics.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dopereir <dopereir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 19:53:16 by dopereir          #+#    #+#             */
/*   Updated: 2025/01/12 13:35:40 by dopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#define MOVE_DELAY 0.03

int	handle_keypress(int keycode, t_data *data)
{
	if (keycode == KEY_ESC)
	{
		clean_exit(data);
		return (0);
	}
	if (data->game_won == 1 || data->game_over == 1)
		return (0);
	if (keycode == KEY_RIGHT || keycode == KEY_LEFT || keycode == KEY_UP
		|| keycode == KEY_DOWN)
	{
		move_player(data, keycode);
		return (0);
	}
	return (0);
}

void	attempt_move(t_data *data, int keycode, int new_x, int new_y)
{
	if (is_valid_move(data, new_x, new_y))
	{
		draw_tile(data, data->player.x, data->player.y);
		data->player.x = new_x;
		data->player.y = new_y;
		data->moves++;
		check_collision(data);
		render_move_count(data);
		if (keycode == KEY_RIGHT)
			handle_player_state(data, 'R');
		else if (keycode == KEY_LEFT)
			handle_player_state(data, 'L');
		else if (keycode == KEY_UP)
			handle_player_state(data, 'J');
		else if (keycode == KEY_DOWN)
			handle_player_state(data, 'C');
		update_player_animation(data);
	}
	else
		ft_printf("Invalid move to (%d, %d)\n", new_x, new_y);
}

void	move_player(t_data *data, int keycode)
{
	static clock_t	last_move_time = 0;
	clock_t			current_time;
	int				new_x;
	int				new_y;

	new_x = data->player.x;
	new_y = data->player.y;
	current_time = clock();
	if (((double)(current_time - last_move_time) / CLOCKS_PER_SEC) < MOVE_DELAY)
		return ;
	if (keycode == KEY_UP)
		new_y--;
	else if (keycode == KEY_DOWN)
		new_y++;
	else if (keycode == KEY_LEFT)
		new_x--;
	else if (keycode == KEY_RIGHT)
		new_x++;
	attempt_move(data, keycode, new_x, new_y);
	last_move_time = current_time;
}

int	is_valid_move(t_data *data, int new_x, int new_y)
{
	if (new_x < 0 || new_x >= data->map.width || new_y < 0
		|| new_y >= data->map.height)
		return (0);
	if (data->map.grid[new_y][new_x] == '1')
		return (0);
	return (1);
}

void	draw_tile(t_data *data, int x, int y)
{
	int	tile_type;

	tile_type = data->map.grid[y][x];
	if (tile_type == '0')
		mlx_put_image_to_window(data->mlx, data->win, data->tiles.wall,
			x * TILE_SIZE, y * TILE_SIZE);
	else if (tile_type == '1')
		mlx_put_image_to_window(data->mlx, data->win, data->tiles.floor1,
			x * TILE_SIZE, y * TILE_SIZE);
	else if (tile_type == 'P')
		mlx_put_image_to_window(data->mlx, data->win, data->tiles.wall,
			x * TILE_SIZE, y * TILE_SIZE);
	else if (tile_type == 'E')
		mlx_put_image_to_window(data->mlx, data->win, data->tiles.exit,
			x * TILE_SIZE, y * TILE_SIZE);
	else if (tile_type == 'F')
		mlx_put_image_to_window(data->mlx, data->win, data->tiles.wall,
			x * TILE_SIZE, y * TILE_SIZE);
}
