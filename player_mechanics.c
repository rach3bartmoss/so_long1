#include "libraries/libft/libft.h"
#include "minilibx-linux/mlx.h"
#include "so_long.h"
#define MOVE_DELAY 0.03

int	handle_keypress(int keycode, t_data *data)
{
	if (keycode == KEY_ESC)
	{
		clean_exit(data);
		return (0);
	}
	if (data->game_won == 1 || data->game_over == 1)
		return (0);
	if (keycode == KEY_RIGHT || keycode == KEY_LEFT || keycode == KEY_UP ||
		keycode == KEY_DOWN)
	{
		move_player(data, keycode);
		return (0);
	}
	return (0);
}

void	move_player(t_data *data, int keycode)
{
	static clock_t	last_move_time = 0;
	clock_t			current_time = clock();

	if (((double)(current_time - last_move_time) / CLOCKS_PER_SEC) < MOVE_DELAY)
		return;

	int new_x = data->player.x;
	int new_y = data->player.y;

	if (keycode == KEY_UP)
		new_y--;
	else if (keycode == KEY_DOWN)
		new_y++;
	else if (keycode == KEY_LEFT)
		new_x--;
	else if (keycode == KEY_RIGHT)
		new_x++;

	//ft_printf("Attempting to move to (%d, %d)\n", new_x, new_y);

	if (is_valid_move(data, new_x, new_y))
	{
		//ft_printf("Moving to (%d, %d)\n", new_x, new_y);
		draw_tile(data, data->player.x, data->player.y);
		data->player.x = new_x;
		data->player.y = new_y;
		data->moves++;
		check_collision(data);
		render_move_count(data);
		if (keycode == KEY_RIGHT)
			handle_player_state(data, 'R'); // Walking right
		else if (keycode == KEY_LEFT)
			handle_player_state(data, 'L'); // Walking left
		else if (keycode == KEY_UP)
			handle_player_state(data, 'J'); // Jumping
		else if (keycode == KEY_DOWN)
			handle_player_state(data, 'C'); // Crouching
		update_player_animation(data); // Update player's animati
		last_move_time = current_time;
		//ft_printf("current players pos(%d, %d)\n", data->player.x, data->player.y);
	}
	else
	{
		ft_printf("Invalid move to (%d, %d)\n", new_x, new_y);
	}
	//ft_printf("number of collectibles on map: %d\n", data->map.collectibles);
}

int	is_valid_move(t_data *data, int new_x, int new_y)
{
	// Check boundaries
	if (new_x < 0 || new_x >= data->map.width || new_y < 0 || new_y >= data->map.height)
		return (0);
	if (data->map.grid[new_y][new_x] == '1')
		return (0);

	return (1); // Valid move
}

void	draw_tile(t_data *data, int x, int y)
{
	int tile_type = data->map.grid[y][x]; // Get tile type from map grid

	if (tile_type == '0') // empty_space
		mlx_put_image_to_window(data->mlx, data->win, data->tiles.wall, x * TILE_SIZE, y * TILE_SIZE);
	else if (tile_type == '1') // Floor
		mlx_put_image_to_window(data->mlx, data->win, data->tiles.floor1, x * TILE_SIZE, y * TILE_SIZE);
	else if (tile_type == 'P')
		mlx_put_image_to_window(data->mlx, data->win, data->tiles.wall, x * TILE_SIZE, y * TILE_SIZE);
	else if (tile_type == 'E')
		mlx_put_image_to_window(data->mlx, data->win, data->tiles.exit, x * TILE_SIZE, y * TILE_SIZE);
	else if (tile_type == 'F')
		mlx_put_image_to_window(data->mlx, data->win, data->tiles.wall, x * TILE_SIZE, y * TILE_SIZE);
}



int	handle_keyrelease(int keycode, t_data *data)
{
	ft_printf("Key release detected: %d\n", keycode);
	if (keycode == KEY_RIGHT || keycode == KEY_LEFT || keycode == KEY_UP || keycode == KEY_DOWN)
	{
		ft_printf("entered the key release function inner condition\n");
		handle_player_state(data, 'I'); // Return to Idle state
		update_player_animation(data);
		//mlx_do_sync(data->mlx);
	}
	return (0);
}

void	check_collision(t_data *data)
{
	int	player_x = data->player.x;
	int	player_y = data->player.y;
	char	tile = data->map.grid[player_y][player_x];

	if (tile == 'C') // Collectible
	{
		data->map.grid[player_y][player_x] = '0'; // Remove collectible
		data->map.collectibles--;
		if (data->map.collectibles == 0)
		{
			data->exit_open = 1;
			open_exit(data); // Change exit animation
		}
	}
	else if (tile == 'E') // Exit
	{
		if (data->exit_open)
		{
			win_game(data); // Handle game win
		}
	}
}

void	open_exit(t_data *data)
{
	for (int y = 0; y < data->map.height; y++)
	{
		for (int x = 0; x < data->map.width; x++)
		{
			if (data->map.grid[y][x] == 'E')
			{
				mlx_put_image_to_window(data->mlx, data->win, data->tiles.exit, x * TILE_SIZE, y * TILE_SIZE);
			}
		}
	}
}

void	render_move_count(t_data *data)
{
	char *move_text = ft_itoa(data->moves);

	// Clear the previous text by drawing a rectangle in the background color
	int x_start = 0;
	int y_start = 0;
	int width = 100;
	int height = 20;
	int bg_color = 0x000000; // Black background color

	for (int y = y_start; y < y_start + height; y++)
	{
		for (int x = x_start; x < x_start + width; x++)
		{
			mlx_pixel_put(data->mlx, data->win, x, y, bg_color);
		}
	}

	// Draw the new move count
	mlx_string_put(data->mlx, data->win, x_start, y_start + 10, 0xFFFFFF, "Moves:");
	mlx_string_put(data->mlx, data->win, x_start + 70, y_start + 10, 0xFFFFFF, move_text);

	free(move_text);
}

void	win_game(t_data *data)
{
	mlx_string_put(data->mlx, data->win, data->map.width * TILE_SIZE / 2 - 100,
					data->map.height * TILE_SIZE / 2, 0xFFD700, "Victory Achieved!");

	data->game_won = 1;
	ft_printf("You Won!\n");
	//clean_exit(data); // Ensure memory and resources are cleaned up
}
