#include "so_long.h"

static void	dfs_validation(char **grid, int x, int y, t_data *data)
{
	if (x < 0 || y < 0 || y >= data->map.height || x >= data->map.width)
		return ;
	if (grid[y][x] == '1' || grid[y][x] == 'V')
		return ;
	if (grid[y][x] == 'C')
		data->map.temp_collectibles--;
	if (grid[y][x] == 'E')
		data->map.temp_exit_count--;
	grid[y][x] = 'V';
	dfs_validation(grid, x + 1, y, data);
	dfs_validation(grid, x - 1, y, data);
	dfs_validation(grid, x, y + 1, data);
	dfs_validation(grid, x, y - 1, data);
}

static char	**copy_grid(char **original_grid, int height)
{
	char	**grid_copy;
	int		y;

	grid_copy = malloc(sizeof(char *) * height);
	if (!grid_copy)
		return (NULL);
	y = 0;
	while (y < height)
	{
		grid_copy[y] = ft_strdup(original_grid[y]);
		if (!grid_copy[y])
		{
			while (--y >= 0)
				free(grid_copy[y]);
			free(grid_copy);
			return (NULL);
		}
		y++;
	}
	return (grid_copy);
}

static void	free_grid(char **grid, int height)
{
	int	y;

	y = 0;
	while (y < height)
		free(grid[y++]);
	free(grid);
}

int	validate_map_path(t_data *data)
{
	char	**grid_copy;

	grid_copy = copy_grid(data->map.grid, data->map.height);
	if (!grid_copy)
		return (0);
	data->map.temp_collectibles = data->map.collectibles;
	data->map.temp_exit_count = data->map.exit_count;
	dfs_validation(grid_copy, data->map.player_x, data->map.player_y, data);
	free_grid(grid_copy, data->map.height);
	return (data->map.temp_collectibles == 0 && data->map.temp_exit_count == 0);
}
