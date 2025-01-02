#include "libraries/libft/libft.h"
#include "minilibx-linux/mlx.h"
#include "so_long.h"
#include <stdio.h>

void	init_animation(t_animation *animation, void *mlx, char *base_path, int frame_count, t_data *data)
{
	char	frame_path[64];
	int		i;

	animation->frame_count = frame_count;
	animation->frame_index = 0;
	i = 0;
	while(i < frame_count)
	{
		snprintf(frame_path, sizeof(frame_path), "%s%d.xpm", base_path, i + 1);
		animation->frames[i] = mlx_xpm_file_to_image(mlx, frame_path, &data->player.width, &data->player.height);
		if (!animation->frames[i])
		{
			ft_printf("error: failed to load animation frame %d.\n", i + 1);
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
	data->player.state = 'I'; // Idle by default

	init_animation(&data->player.idle, data->mlx, "hero/idle/idle_samurai", 10, data);
	init_animation(&data->player.run, data->mlx, "hero/run/run_samurai", 8, data);
	init_animation(&data->player.run_left, data->mlx, "hero/run/run_samurai_L", 8, data);
	init_animation(&data->player.jump, data->mlx, "hero/jump/jump_samurai", 5, data);
	init_animation(&data->player.crouch, data->mlx, "hero/crouch/crouch_samurai", 1, data);

	// Set the initial animation
	data->player.current_animation = &data->player.idle;
}

void	update_player_animation(t_data *data)
{
	t_animation	*anim = data->player.current_animation;
	void		*current_frame;

	// Advance to the next frame
	anim->frame_index = (anim->frame_index + 1) % anim->frame_count;
	current_frame = anim->frames[anim->frame_index];

	// Center the image on the grid
	int pos_x = data->player.x * TILE_SIZE - (data->player.width - TILE_SIZE) / 2;
	int pos_y = data->player.y * TILE_SIZE - (data->player.height - TILE_SIZE) / 2;

	// Display the frame
	mlx_put_image_to_window(data->mlx, data->win, current_frame, pos_x, pos_y);
}

int	animate_player(t_data *data)
{
	static clock_t last_time = 0;
	clock_t current_time = clock();

	if (((double)(current_time - last_time) / CLOCKS_PER_SEC) > 0.1)
	{
		update_player_animation(data);
		last_time = current_time;
	}
	return (0);
}

void handle_player_state(t_data *data, char new_state)
{
	if (data->player.state == new_state)
		return;

	// Transitioning to a new state
	data->player.state = new_state;

	if (new_state == 'I') // Idle
	{
		data->player.current_animation = &data->player.idle;
		//data->player.current_animation->frame_index = 0;
	}
	else if (new_state == 'R') // Running
		data->player.current_animation = &data->player.run;
	else if (new_state == 'L') // Running
		data->player.current_animation = &data->player.run_left;
	else if (new_state == 'J') // Jumping
		data->player.current_animation = &data->player.jump;
	else if (new_state == 'C') // Crouching
		data->player.current_animation = &data->player.crouch;
}

void	clean_animation(t_animation *animation, void *mlx)
{
	int i = 0;
	while (i < animation->frame_count)
	{
		if (animation->frames[i])
		{
			mlx_destroy_image(mlx, animation->frames[i]);
			animation->frames[i] = NULL;
		}
		i++;
	}
}

void	clean_player(t_data *data)
{
	clean_animation(&data->player.idle, data->mlx);
	clean_animation(&data->player.run, data->mlx);
	clean_animation(&data->player.run_left, data->mlx);
	clean_animation(&data->player.jump, data->mlx);
	clean_animation(&data->player.crouch, data->mlx);
}
