/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dopereir <dopereir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 22:46:49 by dopereir          #+#    #+#             */
/*   Updated: 2025/01/12 13:34:13 by dopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include "libraries/mlx/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <unistd.h>
# include <fcntl.h>
# include <time.h>
# include <complex.h>
# include <string.h>
# include "libraries/libft/libft.h"

# define TILE_SIZE 32

# define MAX_ENEMIES 50

# define KEY_ESC 65307
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_UP 65362
# define KEY_DOWN 65364
# define ATTACK_Q 113
# define X_EVENT_EXIT 17

# define KEYPRESS 2
# define KEYRELEASE 3

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	int		collectibles;
	int		temp_collectibles;
	int		exit_count;
	int		temp_exit_count;
	int		player_count;
	int		enemy_count;
	int		player_y;
	int		player_x;
}				t_map;

typedef struct s_rectangle
{
	int	x_start;
	int	y_start;
	int	width;
	int	height;
}				t_rectangle;

typedef struct s_text
{
	char		*label;
	char		*value;
	int			x_start;
	int			y_start;
}				t_text;

typedef struct s_data_img
{
	char	*addr;
	void	*img;
}				t_data_img;

typedef struct temp_values //gambiarras i know and i sorry
{
	int		enemy_x;
	int		enemy_y;
}				t_tempvalues;

typedef struct temp
{
	int	new_y;
	int	new_x;
}				t_temp;

typedef struct s_animation
{
	int		frame_count;
	int		frame_index;
	void	*frames[10];
}				t_animation;

typedef struct s_tiles
{
	int		width;
	int		height;
	void	*floor1;
	void	*wall;
	void	*wall2;
	void	*exit;
	void	*collectible;
}				t_tiles;

typedef struct s_enemy
{
	char		state;
	int			y;
	int			x;
	int			width;
	int			height;
	int			alive;
	int			frame_delay;
	t_animation	idle;
	t_animation	walk;
	t_animation	walk_left;
	t_animation	*current_animation;
}				t_enemy;

typedef struct s_player
{
	int			x;
	int			y;
	int			width;
	int			height;
	char		state;
	t_animation	idle;
	t_animation	run;
	t_animation	run_left;
	t_animation	jump;
	t_animation	crouch;
	t_animation	*current_animation;
}				t_player;
//struct for handle events
typedef struct s_data
{
	int			moves;
	int			enemy_count_var;
	int			exit_open;
	int			game_won;
	int			game_over;
	t_map		map;
	t_temp		temp; //gambiarra
	t_data_img	image;
	t_tiles		tiles;
	t_enemy		enemies[MAX_ENEMIES];
	t_player	player;
	void		*mlx;
	void		*win;
}				t_data;
//clean_close.c
int		clean_exit(t_data *data);
int		close_window_x_event(t_data *data);
int		key_exit_handler(int keycode, t_data *data);
void	cleanup_map(t_data *data);
void	clean_img_win_display(t_data *data);

int		init_data(t_data *data);

//map_loading.c
int		load_map(t_data *data, char *filename);
int		read_map_dimensions(t_data *data, char *filename);
int		init_map_memory(t_data *data);
int		cleanup_and_close(t_data *data, int fd);
int		process_map_line(t_data *data, char *line);

//map_validation.c
int		validate_map(t_data *data);
int		count_map_elements(t_data *data);
int		check_map_borders(t_data *data);
int		validate_map_chars(char c);
void	init_map_elements(t_data *data, char c, int y, int x);

//dfs_path_validation.c
int		validate_map_path(t_data *data);

//tile_management.c
void	init_tiles(t_data *data);
void	render_tiles(t_data *data);
void	clean_tiles(t_data *data);

//player_management.c
void	init_animation(t_animation *animation, char *base_path,
			int frame_count, t_data *data);
void	init_player(t_data *data);
void	update_player_animation(t_data *data);
int		animate_player(t_data *data);
void	handle_player_state(t_data *data, char new_state);
//player_management_helper.c
void	clean_animation(t_animation *animation, void *mlx);
void	clean_player(t_data *data);

//player_mechanics.c
int		handle_keypress(int keycode, t_data *data);
void	attempt_move(t_data *data, int keycode, int new_x, int new_y);
void	move_player(t_data *data, int keycode);
int		is_valid_move(t_data *data, int new_x, int new_y);
void	draw_tile(t_data *data, int x, int y);
//player_mechanics_helper.c
int		handle_keyrelease(int keycode, t_data *data);
void	check_collision(t_data *data);
void	open_exit(t_data *data);
void	win_game(t_data *data);
//player_mechanics_helper2.c
void	render_move_count(t_data *data);

//enemies_mechanics.c
void	update_enemies_movement(t_data *data);
void	game_over(t_data *data);
void	check_player_enemy_collision(t_data *data);
//enemies_mechanics_helper.c
void	move_enemy(t_data *data, t_enemy *enemy);

//enemies_management.c 1/2
void	load_enemy_animation(t_data *data, t_animation *anim,
			const char *filename, int total_frames);
void	init_enemy(t_data *data, t_enemy *enemy, int x, int y);
void	initialize_enemies(t_data *data);
void	render_enemies(t_data *data);
void	update_enemy_animation(t_data *data);

//enemies_management_helper.c 2/2
int		animate_enemies(t_data *data);
void	clean_enemies(t_data *data);
void	initialize_enemies_helper(t_data *data, int *x,
			int *y, int *enemy_index);

void	print_error_and_exit(char *error_msg, t_data *data);
void	print_element_errors(t_data *data);
void	clean_map_loading_helper(t_data *data, int fd, char *line);

#endif
