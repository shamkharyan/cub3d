/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshamkha <pshamkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 12:40:34 by pshamkha          #+#    #+#             */
/*   Updated: 2024/10/23 17:27:21 by pshamkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*) dst = color;
}

void	draw_vline(t_data *data, int x, t_icoord y12, int color)
{
	int y;

	y = y12.x - 1;
	while (++y <= y12.y)
		my_mlx_pixel_put(data, x, y, color);
}

// void	draw_square(t_data *data, t_coord xy0, int size, int color)
// {
// 	int	x;
// 	int	y;

// 	y = -1;

// 	while (++y < size)
// 	{
// 		x = -1;
// 		while (++x < size)
// 			my_mlx_pixel_put(data, xy0.x + x, xy0.y + y, color);
// 	}
// }

// void	draw_line(t_data *data, t_coord xy0, t_coord xy1, int color)
// {
// 	t_coord d_xy;
// 	t_coord s_xy;
// 	t_coord err1_2;

// 	d_xy.x = abs(xy1.x - xy0.x);
//     d_xy.y = abs(xy1.y - xy0.y);
// 	s_xy.x = ternary(xy0.x < xy1.x, 1, -1);
//     s_xy.y = ternary(xy0.y < xy1.y, 1, -1);
//     err1_2.x = d_xy.x - d_xy.y;
// 	while (1)
// 	{
// 		my_mlx_pixel_put(data, xy0.x, xy0.y, color);
// 		if (xy0.x == xy1.x && xy0.y == xy1.y)
// 			return ;
// 		err1_2.y = err1_2.x * 2;
// 		if (err1_2.y > -d_xy.y)
// 		{
// 			err1_2.x -= d_xy.y;
// 			xy0.x += s_xy.x;
// 		}
// 		if (err1_2.y < d_xy.x)
// 		{
// 			err1_2.x += d_xy.x;
// 			xy0.y += s_xy.y;
// 		}
// 	}
// }
