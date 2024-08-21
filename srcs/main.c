/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshamkha <pshamkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 13:01:42 by pshamkha          #+#    #+#             */
/*   Updated: 2024/08/21 18:26:08 by pshamkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_null(t_game *game)
{
	mlx = NULL;
	mlx_win = NULL;
	img_no = NULL;
	img_so = NULL;
	img_we = NULL;
	img_ea = NULL;
	img_width = 0;
	img_height = 0;
	floor = NULL;
	ceiling = NULL;
}

int	main(int argc, char **argv)
{
	t_game	game;

	init_null(&game);
	if (argc == 2 && check_map(argv[1]))
	{
		printf("OK");
	}
	else
	{
		printf("KO");
	}
	return (0);
}
