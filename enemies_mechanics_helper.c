/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies_mechanics_helper.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dopereir <dopereir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 00:55:45 by dopereir          #+#    #+#             */
/*   Updated: 2025/01/06 00:55:48 by dopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	rand_direction(t_enemy *enemy, t_data *data)
{
	int	direction;

	if (!enemy->alive || data->game_won)
		return ;
	direction = rand() % 4;
	data->temp.new_x = enemy->x;
	data->temp.new_y = enemy->y;
	if (direction == 0)
		data->temp.new_y -= 1;
	else if (direction == 1)
		data->temp.new_x += 1;
	else if (direction == 2)
		data->temp.new_y += 1;
	else if (direction == 3)
		data->temp.new_x -= 1;
}

void	move_enemy(t_data *data, t_enemy *enemy)
{
	char	next_tile;

	rand_direction(enemy, data);
	if (data->temp.new_x >= 0 && data->temp.new_x < data->map.width
		&& data->temp.new_y >= 0 && data->temp.new_y < data->map.height)
	{
		next_tile = data->map.grid[data->temp.new_y][data->temp.new_x];
		if (next_tile == '0')
		{
			draw_tile(data, enemy->x, enemy->y);
			enemy->x = data->temp.new_x;
			enemy->y = data->temp.new_y;
			mlx_put_image_to_window(data->mlx, data->win,
				enemy->current_animation
				->frames[enemy->current_animation->frame_index],
				enemy->x * TILE_SIZE, enemy->y * TILE_SIZE);
		}
	}
}
