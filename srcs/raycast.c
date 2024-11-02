/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamkharyan <shamkharyan@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 17:03:53 by pshamkha          #+#    #+#             */
/*   Updated: 2024/10/28 23:37:38 by shamkharyan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	start(t_game *g)
{
    int worldMap[24][24] = {
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};
    
	int	x;

	g->mlx_win = mlx_new_window(g->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3d");
	g->ray.pos.x = g->player.x;
	g->ray.pos.y = g->player.y;
	g->ray.dir.x = -1;
	g->ray.dir.y = 0;
	g->ray.plane.x = 0;
	g->ray.plane.y = 0.66;
    while (1)
	{
		x = -1;
		while (++x < WIN_WIDTH)
		{
			g->ray.cameraX = 2 * x / (double) WIN_WIDTH - 1;
            g->ray.rayDir.x = g->ray.dir.x + g->ray.plane.x * g->ray.cameraX;
            g->ray.rayDir.y = g->ray.dir.y + g->ray.plane.y * g->ray.cameraX;
            g->ray.map.x = (int) g->ray.pos.x;
            g->ray.map.y = (int) g->ray.pos.y;

            g->ray.deltaDist.x = ternary(g->ray.rayDir.x == 0, 1e30, fabs(1 / g->ray.rayDir.x));
            g->ray.deltaDist.y = ternary(g->ray.rayDir.y == 0, 1e30, fabs(1 / g->ray.rayDir.y));
			g->ray.hit = 0;
            if (g->ray.rayDir.x < 0)
			{
                g->ray.step.x = -1;
                g->ray.sideDist.x = (g->ray.pos.x - g->ray.map.x) * g->ray.deltaDist.x;
            }
			else
			{
                g->ray.step.x = 1;
                g->ray.sideDist.x = (g->ray.map.x + 1.0 - g->ray.pos.x) * g->ray.deltaDist.x;
            }
            if (g->ray.rayDir.y < 0)
			{
                g->ray.step.y = -1;
                g->ray.sideDist.y = (g->ray.pos.y - g->ray.map.y) * g->ray.deltaDist.y;
            }
			else
			{
                g->ray.step.y = 1;
                g->ray.sideDist.y = (g->ray.map.y + 1.0 - g->ray.pos.y) * g->ray.deltaDist.y;
            }
            while (g->ray.hit == 0)
			{
                if (g->ray.sideDist.x < g->ray.sideDist.y)
				{
                    g->ray.sideDist.x += g->ray.deltaDist.x;
                    g->ray.map.x += g->ray.step.x;
                    g->ray.side = 0;
                }
				else
				{
                    g->ray.sideDist.y += g->ray.deltaDist.y;
                    g->ray.map.y += g->ray.step.y;
                    g->ray.side = 1;
                }
					printf("x = %d, y = %d\n", g->ray.map.x, g->ray.map.y);
					printf("c = %c\n", worldMap[g->ray.map.x][g->ray.map.y]);
        			if (worldMap[g->ray.map.x][g->ray.map.y] == 1)
						g->ray.hit = 1;
            }
            
            if (g->ray.side == 0)
				g->ray.perpWallDist = (g->ray.map.x - g->ray.pos.x + (1 - g->ray.step.x) / 2) / g->ray.rayDir.x;
            else
				g->ray.perpWallDist = (g->ray.map.y - g->ray.pos.y + (1 - g->ray.step.y) / 2) / g->ray.rayDir.y;

            g->ray.lineHeight = (int)(WIN_HEIGHT / g->ray.perpWallDist);

            g->ray.drawStEn.x = -g->ray.lineHeight / 2 + WIN_HEIGHT / 2;
            if (g->ray.drawStEn.x < 0)
				g->ray.drawStEn.x = 0;
            g->ray.drawStEn.y = g->ray.lineHeight / 2 + WIN_HEIGHT / 2;
            if (g->ray.drawStEn.y >= WIN_HEIGHT)
				g->ray.drawStEn.y = WIN_HEIGHT - 1;

            int color = 0xFFFFFF;
            if (g->ray.side == 1)
				color = color / 2;

            draw_vline(g->img_data, x, g->ray.drawStEn, color);
        }
		mlx_loop(g->mlx);
    }
}


