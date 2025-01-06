/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_close.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dopereir <dopereir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 19:51:07 by dopereir          #+#    #+#             */
/*   Updated: 2025/01/05 19:51:12 by dopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx-linux/mlx.h"
#include "so_long.h"
#include <mlx.h>
#include <stdlib.h>

int	clean_exit(t_data *data)
{
	if (data)
	{
		clean_tiles(data);
		clean_player(data);
		clean_enemies(data);
	}
	clean_img_win_display(data);
	cleanup_map(data);
	exit (0);
	return (0);
}

void	clean_img_win_display(t_data *data)
{
	if (data && data->image.img)
	{
		mlx_destroy_image(data->mlx, data->image.img);
		data->image.img = NULL;
		data->image.addr = NULL;
	}
	if (data && data->win)
	{
		mlx_destroy_window(data->mlx, data->win);
		data->win = NULL;
	}
	if (data && data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		data->mlx = NULL;
	}
}

int	close_window_x_event(t_data *data)
{
	clean_exit(data);
	return (0);
}

int	key_exit_handler(int keycode, t_data *data)
{
	if (keycode == KEY_ESC)
		clean_exit (data);
	return (0);
}

void	cleanup_map(t_data *data)
{
	int	y;

	if (!data->map.grid)
		return ;
	y = 0;
	while (y < data->map.height)
	{
		free(data->map.grid[y]);
		y++;
	}
	free(data->map.grid);
	data->map.grid = NULL;
}
