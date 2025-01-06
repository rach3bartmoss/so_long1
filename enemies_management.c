/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies_management.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dopereir <dopereir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 19:51:46 by dopereir          #+#    #+#             */
/*   Updated: 2025/01/05 19:51:49 by dopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	load_enemy_animation(t_data *data, t_animation *anim,
	const char *base_path, int total_frames)
{
	int		i;
	char	frame_path[50];

	anim->frame_count = total_frames;
	anim->frame_index = 0;
	i = 0;
	while (i < total_frames)
	{
		snprintf(frame_path, sizeof(frame_path), "%s%d.xpm", base_path, i + 1);
		anim->frames[i] = mlx_xpm_file_to_image(data->mlx, frame_path,
				&data->enemies[0].width, &data->enemies[0].height);
		if (!anim->frames[i])
		{
			ft_printf("Error: failed to load enemy frame %d.\n", i + 1);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void	init_enemy(t_data *data, t_enemy *enemy, int x, int y)
{
	enemy->x = x;
	enemy->y = y;
	enemy->width = TILE_SIZE;
	enemy->height = TILE_SIZE;
	enemy->alive = 1;
	enemy->frame_delay = 0;
	enemy->state = 'I';
	load_enemy_animation(data, &enemy->idle, "enemies/anim2/ghost_idle", 2);
	enemy->current_animation = &enemy->idle;
}

void	initialize_enemies(t_data *data)
{
	int			x;
	int			y;
	static int	enemy_index = 0;

	data->enemy_count_var = 0;
	initialize_enemies_helper(data, &x, &y, &enemy_index);
}

void	render_enemies(t_data *data)
{
	int		i;
	int		frame_index;
	void	*frame;

	frame_index = 0;
	i = 0;
	while (i < data->enemy_count_var)
	{
		if (data->enemies[i].alive)
		{
			frame_index = data->enemies[i].current_animation->frame_index;
			frame = data->enemies[i].current_animation->frames[frame_index];
			mlx_put_image_to_window(data->mlx, data->win, frame,
				data->enemies[i].x * TILE_SIZE, data->enemies[i].y * TILE_SIZE);
		}
		i++;
	}
}

void	update_enemy_animation(t_data *data)
{
	int			i;
	t_enemy		*enemy;
	t_animation	*anim;

	i = 0;
	while (i < data->enemy_count_var)
	{
		enemy = &data->enemies[i];
		if (enemy->alive)
		{
			anim = enemy->current_animation;
			if (!enemy->frame_delay)
				enemy->frame_delay = 0;
			if (enemy->frame_delay++ >= 500)
			{
				anim->frame_index = (anim->frame_index + 1) % anim->frame_count;
				enemy->frame_delay = 0;
			}
		}
		i++;
	}
}
