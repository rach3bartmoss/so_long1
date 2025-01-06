/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_mechanics_helper2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dopereir <dopereir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 19:53:09 by dopereir          #+#    #+#             */
/*   Updated: 2025/01/05 19:53:11 by dopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	draw_background(t_data *data, t_rectangle rect, int bg_color)
{
	int	y;
	int	x;

	y = rect.y_start;
	while (y < rect.y_start + rect.height)
	{
		x = rect.x_start;
		while (x < rect.x_start + rect.width)
		{
			mlx_pixel_put(data->mlx, data->win, x, y, bg_color);
			x++;
		}
		y++;
	}
}

static void	display_move_text(t_data *data, t_text text)
{
	mlx_string_put(data->mlx, data->win, text.x_start,
		text.y_start + 10, 0xFFFFFF, text.label);
	mlx_string_put(data->mlx, data->win, text.x_start + 70,
		text.y_start + 10, 0xFFFFFF, text.value);
}

void	render_move_count(t_data *data)
{
	t_rectangle	rect;
	t_text		text;
	char		*move_text;

	rect.x_start = 0;
	rect.y_start = 0;
	rect.width = 100;
	rect.height = 20;
	move_text = ft_itoa(data->moves);
	text.label = "Moves:";
	text.value = move_text;
	text.x_start = rect.x_start;
	text.y_start = rect.y_start;
	draw_background(data, rect, 0x000000);
	display_move_text(data, text);
	free(move_text);
}
