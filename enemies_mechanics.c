/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies_mechanics.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dopereir <dopereir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 00:53:25 by dopereir          #+#    #+#             */
/*   Updated: 2025/01/06 00:53:26 by dopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#define ENEMY_MOVE_DELAY 0.5

void	update_enemies_movement(t_data *data)
{
	static clock_t	last_time = 0;
	clock_t			current_time;
	int				i;

	current_time = clock();
	if (((double)(current_time - last_time)
		/ CLOCKS_PER_SEC) > ENEMY_MOVE_DELAY)
	{
		i = 0;
		while (i < data->enemy_count_var)
		{
			move_enemy(data, &data->enemies[i]);
			i++;
		}
		last_time = current_time;
	}
}

void	game_over(t_data *data)
{
	data->game_over = 1;
	ft_printf("Game Over! You Died.\n");
	mlx_string_put(data->mlx, data->win, data->map.width * TILE_SIZE / 2 - 50,
		data->map.height * TILE_SIZE / 2, 0xFF0000, "You Died!");
}

void	check_player_enemy_collision(t_data *data)
{
	t_enemy			*enemy;
	t_tempvalues	temp;
	int				player_y;
	int				player_x;
	int				i;

	if (data->game_over || data->game_won)
		return ;
	player_x = data->player.x;
	player_y = data->player.y;
	i = 0;
	while (i < data->enemy_count_var)
	{
		enemy = &data->enemies[i];
		temp.enemy_x = enemy->x;
		temp.enemy_y = enemy->y;
		if (player_x == temp.enemy_x && player_y == temp.enemy_y)
		{
			ft_printf("Collision detected with enemy[%d]!\n", i);
			game_over(data);
			return ;
		}
		i++;
	}
}
