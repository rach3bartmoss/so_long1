#include "libraries/libft/libft.h"
#include "so_long.h"

int	process_map_line(t_data *data, char *line)
{
	if (data->map.height == 0)
		data->map.width = ft_strlen(line);
	else if ((int)ft_strlen(line) != data->map.width)
	{
		free(line);
		return (0);
	}
	data->map.height++;
	return (1);
}

//every time sucessfully aknowledge a line update height
//define width of first line
int	read_map_dimensions(t_data *data, char *filename)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	data->map.height = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		if (!process_map_line(data, line))
			return (close(fd));
		free(line);
	}
	close(fd);
	return (data->map.height > 0 && data->map.width > 0);
}

int	init_map_memory(t_data *data)
{
	int	y;

	data->map.grid = malloc(sizeof(char *) * (data->map.height + 1));
	if (!data->map.grid)
		return (0);
	y = 0;
	while (y <= data->map.height)
	{
		data->map.grid[y] = NULL;
		y++;
	}
	return (1);
}

int	cleanup_and_close(t_data *data, int fd)
{
	cleanup_map(data);
	return (close(fd));
}

int	load_map(t_data *data, char *filename)
{
	int		fd;
	char	*line;
	int		y;

	if (!read_map_dimensions(data, filename) || !init_map_memory(data))
		return (0);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	y = 0;
	while (y < data->map.height)
	{
		line = get_next_line(fd);
		if (line == NULL)
			return (cleanup_and_close(data, fd));
		data->map.grid[y] = ft_strdup(line);
		free(line);
		if (!data->map.grid[y])
			return (cleanup_and_close(data, fd));
		y++;
	}
	line = get_next_line(fd);
	free(line);
	close(fd);
	return (validate_map(data));
}
