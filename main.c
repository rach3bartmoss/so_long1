/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dopereir <dopereir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 19:52:19 by dopereir          #+#    #+#             */
/*   Updated: 2025/01/12 17:35:51 by dopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	game_loop(t_data *data)
{
	static int	game_over_flag = 1;

	if (game_over_flag == 0)
		return (0);
	check_player_enemy_collision(data);
	if (data->game_over == 1 && game_over_flag)
	{
		ft_printf("Game is over. Stopping game loop actions.\n");
		game_over_flag = 0;
		return (0);
	}
	animate_player(data);
	render_enemies(data);
	update_enemy_animation(data);
	update_enemies_movement(data);
	return (0);
}

static void	init_game(t_data *data)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, data->map.width * TILE_SIZE,
			data->map.height * TILE_SIZE, "SO_LONG");
	data->moves = 0;
	data->game_won = 0;
	data->game_over = 0;
	init_tiles(data);
	render_tiles(data);
	srand(time(NULL));
	init_player(data);
	initialize_enemies(data);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		return (ft_printf("Error\nUsage: <program> <map_name.ber>\n"));
	init_data(&data);
	if (!load_map(&data, argv[1]) || !validate_map(&data))
		return (clean_exit(&data));
	init_game(&data);
	if (!data.mlx || !data.win)
		return (clean_exit(&data));
	mlx_loop_hook(data.mlx, game_loop, &data);
	mlx_hook(data.win, KEYPRESS, 1L << 0, handle_keypress, &data);
	mlx_hook(data.win, KEYRELEASE, 1L << 1, handle_keyrelease, &data);
	mlx_hook(data.win, X_EVENT_EXIT, 0, close_window_x_event, &data);
	mlx_key_hook(data.win, key_exit_handler, &data);
	mlx_loop(data.mlx);
	return (clean_exit(&data));
}
