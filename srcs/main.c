/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshamkha <pshamkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 13:01:42 by pshamkha          #+#    #+#             */
/*   Updated: 2024/08/22 18:57:28 by pshamkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_null(t_game *g)
{
	g->mlx = mlx_init();
	g->mlx_win = NULL;
	g->img_tex[0] = NULL;
	g->img_tex[1] = NULL;
	g->img_tex[2] = NULL;
	g->img_tex[3] = NULL;
	g->img_width = TEX_WIDTH;
	g->img_height = TEX_HEIGHT;
	g->floor = NULL;
	g->ceiling = NULL;
}

int	main(int argc, char **argv)
{
	t_game	g;

	init_null(&g);
	if (argc == 2 && check_map(&g, argv[1]))
	{
		printf("OK");
	}
	else
	{
		printf("KO");
	}
	return (0);
}
