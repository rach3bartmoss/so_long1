/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dopereir <dopereir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 19:52:56 by dopereir          #+#    #+#             */
/*   Updated: 2025/01/12 15:15:47 by dopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_animation(t_animation *animation, char *base_path,
	int frame_count, t_data *data)
{
	char	frame_path[64];
	int		i;

	animation->frame_count = frame_count;
	animation->frame_index = 0;
	i = 0;
	while (i < frame_count)
	{
		snprintf(frame_path, sizeof(frame_path), "%s%d.xpm", base_path, i + 1);
		animation->frames[i] = mlx_xpm_file_to_image(data->mlx, frame_path,
				&data->player.width, &data->player.height);
		if (!animation->frames[i])
		{
			ft_printf("Error\n failed to load animation frame %d.\n", i + 1);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void	init_player(t_data *data)
{
	data->player.width = 32;
	data->player.height = 32;
	data->player.x = data->map.player_x;
	data->player.y = data->map.player_y;
	data->player.state = 'I';
	init_animation(&data->player.idle, "textures/hero/idle_samurai", 10, data);
	init_animation(&data->player.run, "textures/hero/run_samurai", 8, data);
	init_animation(&data->player.run_left, "textures/hero/run_samurai_L",
		8, data);
	init_animation(&data->player.jump, "textures/hero/jump_samurai", 5, data);
	init_animation(&data->player.crouch, "textures/hero/crouch_samurai",
		1, data);
	data->player.current_animation = &data->player.idle;
}

void	update_player_animation(t_data *data)
{
	t_animation	*anim;
	void		*current_frame;
	int			pos_x;
	int			pos_y;

	anim = data->player.current_animation;
	anim->frame_index = (anim->frame_index + 1) % anim->frame_count;
	current_frame = anim->frames[anim->frame_index];
	pos_x = data->player.x * TILE_SIZE - (data->player.width - TILE_SIZE) / 2;
	pos_y = data->player.y * TILE_SIZE - (data->player.height - TILE_SIZE) / 2;
	mlx_put_image_to_window(data->mlx, data->win, current_frame, pos_x, pos_y);
}

int	animate_player(t_data *data)
{
	static clock_t	last_time = 0;
	clock_t			current_time;

	current_time = clock();
	if (((double)(current_time - last_time) / CLOCKS_PER_SEC) > 0.1)
	{
		update_player_animation(data);
		last_time = current_time;
	}
	return (0);
}

void	handle_player_state(t_data *data, char new_state)
{
	if (data->player.state == new_state)
		return ;
	data->player.state = new_state;
	if (new_state == 'I')
		data->player.current_animation = &data->player.idle;
	else if (new_state == 'R')
		data->player.current_animation = &data->player.run;
	else if (new_state == 'L')
		data->player.current_animation = &data->player.run_left;
	else if (new_state == 'J')
		data->player.current_animation = &data->player.jump;
	else if (new_state == 'C')
		data->player.current_animation = &data->player.crouch;
}
