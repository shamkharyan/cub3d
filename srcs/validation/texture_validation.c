/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_validation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshamkha <pshamkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 18:54:18 by pshamkha          #+#    #+#             */
/*   Updated: 2024/12/27 17:33:50 by pshamkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_commas(char *color)
{
	int		i;
	int		count;
	char	*trimed;

	i = -1;
	count = 0;
	trimed = ft_strtrim(color, " ");
	if (trimed[0] == ',' || trimed[ft_strlen(color) - 1] == ',')
		return (free(trimed), 0);
	while (trimed[++i] != '\0')
	{
		if (ft_isdigit(trimed[i]) == 0 && trimed[i] != ',')
			return (free(trimed), 0);
		if (trimed[i] == ',' && trimed[i + 1] == ',')
			return (0);
		if (trimed[i] == ',')
			++count;
	}
	free(trimed);
	return (count == 2);
}

static int	check_rgbs(char **colors[2])
{
	int	rgb;
	int	i;
	int	j;

	i = -1;
	while (++i < 2)
	{
		j = -1;
		while (++j < 3)
		{
			if (ft_strlen(colors[i][j]) > 3)
				return (0);
			rgb = ft_atoi(colors[i][j]);
			if (!(rgb >= 0 && rgb <= 255))
				return (0);
		}
	}
	return (1);
}

static int	check_colors(t_game *g)
{
	char	**clrs[2];

	if (!check_commas(g->map_data[F]) || !check_commas(g->map_data[C]))
		return (0);
	clrs[0] = ft_split(g->map_data[C], ',');
	clrs[1] = ft_split(g->map_data[F], ',');
	if (!check_rgbs(clrs))
	{
		free_split(clrs[0]);
		free_split(clrs[1]);
		return (0);
	}
	g->colors[0] = create_trgb(0, ft_atoi(clrs[0][0]),
			ft_atoi(clrs[0][1]), ft_atoi(clrs[0][2]));
	g->colors[1] = create_trgb(0, ft_atoi(clrs[1][0]),
			ft_atoi(clrs[1][1]), ft_atoi(clrs[1][2]));
	free_split(clrs[0]);
	free_split(clrs[1]);
	return (1);
}

static int	check_xpm(t_game *g)
{
	int	i;

	g->mlx = mlx_init();
	g->walls[NO].img = xpm2img(g, g->map_data[NO]);
	if (g->walls[NO].img == NULL)
		return (0);
	g->walls[SO].img = xpm2img(g, g->map_data[SO]);
	if (g->walls[SO].img == NULL)
		return (0);
	g->walls[EA].img = xpm2img(g, g->map_data[EA]);
	if (g->walls[EA].img == NULL)
		return (0);
	g->walls[WE].img = xpm2img(g, g->map_data[WE]);
	if (g->walls[WE].img == NULL)
		return (0);
	i = -1;
	while (++i < 4)
		g->walls[i].addr = mlx_get_data_addr(g->walls[i].img,
				&g->walls[i].bits_per_pixel,
				&g->walls[i].line_length, &g->walls[i].endian);
	return (1);
}

int	check_data(t_game *g)
{
	if (!check_colors(g))
		return (err_msg("Wrong color format.\n"), 0);
	if (!check_xpm(g))
		return (err_msg("Can't parse images.\n"), 0);
	return (1);
}
