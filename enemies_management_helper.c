#include "so_long.h"

int	animate_enemies(t_data *data)
{
	static clock_t	last_time = 0;
	time_t			current_time;

	current_time = time(NULL);
	if (difftime(current_time, last_time) > 0.5)
	{
		update_enemy_animation(data);
		last_time = current_time;
	}
	return (0);
}

void	initialize_enemies_helper(t_data *data, int *x, int *y,
	int *enemy_index)
{
	*y = 0;
	while (*y < data->map.height)
	{
		*x = 0;
		while (*x < data->map.width)
		{
			if (data->map.grid[*y][*x] == 'F')
			{
				if (*enemy_index < MAX_ENEMIES)
				{
					init_enemy(data, &data->enemies[*enemy_index], *x, *y);
					(*enemy_index)++;
					data->enemy_count_var++;
				}
				else
					break ;
			}
			(*x)++;
		}
		if (*enemy_index >= MAX_ENEMIES)
			break ;
		(*y)++;
	}
}

void	clean_enemies(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->enemy_count_var)
	{
		j = 0;
		while (j < data->enemies[i].idle.frame_count)
		{
			if (data->enemies[i].idle.frames[j])
			{
				mlx_destroy_image(data->mlx, data->enemies[i].idle.frames[j]);
				data->enemies[i].idle.frames[j] = NULL;
			}
			j++;
		}
		i++;
	}
}
