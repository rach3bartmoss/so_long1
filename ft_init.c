#include "so_long.h"

int	init_data(t_data *data)
{
	if (!data)
		return (0);
	memset(data, 0, sizeof(t_data));
	data->mlx = NULL;
	data->win = NULL;
	data->image.img = NULL;
	data->image.addr = NULL;
	return (1);
}
