/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dopereir <dopereir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 19:52:07 by dopereir          #+#    #+#             */
/*   Updated: 2025/01/05 19:52:10 by dopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
