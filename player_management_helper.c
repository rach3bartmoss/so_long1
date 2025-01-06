/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_management_helper.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dopereir <dopereir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 19:52:48 by dopereir          #+#    #+#             */
/*   Updated: 2025/01/05 19:52:51 by dopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	clean_animation(t_animation *animation, void *mlx)
{
	int	i;

	i = 0;
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
