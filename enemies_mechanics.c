#include "so_long.h"
#define ENEMY_MOVE_DELAY 0.5

void	move_enemy(t_data *data, t_enemy *enemy)
{
	int		direction;
	int		new_y;
	int		new_x;
	char	next_tile;

	if (!enemy->alive || data->game_won)
		return ;
	direction = rand() % 4;
	new_x = enemy->x;
	new_y = enemy->y;
	if (direction == 0)
		new_y -= 1;
	else if (direction == 1)
		new_x += 1;
	else if (direction == 2)
		new_y += 1;
	else if (direction == 3)
			new_x -= 1;
	if (new_x >= 0 && new_x < data->map.width && new_y >= 0 && new_y < data->map.height)
	{
		next_tile = data->map.grid[new_y][new_x];
		if (next_tile == '0')
		{
			draw_tile(data, enemy->x, enemy->y);
			enemy->x = new_x;
			enemy->y = new_y;
			mlx_put_image_to_window(data->mlx, data->win,
									enemy->current_animation->frames[enemy->current_animation->frame_index],
									enemy->x * TILE_SIZE, enemy->y * TILE_SIZE);
		}
	}
}

void	update_enemies_movement(t_data *data)
{
	static clock_t	last_time = 0;
	clock_t 		current_time;

	current_time = clock();
	if (((double)(current_time - last_time) / CLOCKS_PER_SEC) > ENEMY_MOVE_DELAY)
	{
		for (int i = 0; i < data->enemy_count_var; i++)
		{
			move_enemy(data, &data->enemies[i]);
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
	t_enemy	*enemy;
	int		player_y;
	int		player_x;
	int		i;

	if (data->game_over || data->game_won)
		return ;
	player_x = data->player.x;
	player_y = data->player.y;
	i = 0;
	while (i < data->enemy_count_var)
	{
		enemy = &data->enemies[i];
		int enemy_x = enemy->x;
		int enemy_y = enemy->y;
		if (player_x == enemy_x && player_y == enemy_y)
		{
			ft_printf("Collision detected with enemy[%d]!\n", i);
			game_over(data);
			return ;
		}
		i++;
	}
}
