/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshamkha <pshamkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 18:54:18 by pshamkha          #+#    #+#             */
/*   Updated: 2024/10/01 18:54:19 by pshamkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_commas(char *color)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (color[++i] != '\0')
		if (color[i] == ',')
			++count;
	return (count == 2);
}

static int	check_rgb(char *color)
{
	int	rgb;

	if (ft_strlen(color) > 3)
		return (0);
	rgb = ft_atoi(color);
	if (rgb >= 0 && rgb <= 255)
		return (1);
	return (0);
}

static int	check_colors(t_game *g)
{
	char	**tokens[2];
	int		i;
	int		j;

	if (!check_commas(g->data_path[F]) || !check_commas(g->data_path[C]))
		return (0);
	tokens[F - 4] = ft_split(g->data_path[F], ',');
	tokens[C - 4] = ft_split(g->data_path[C], ',');
	i = -1;
	while (++i < 2)
	{
		j = -1;
		while (++j < 3)
			if (!check_rgb(tokens[i][j]))
				return (0);
	}
	g->colors[C - 4].r = ft_atoi(tokens[F - 4][0]);
	g->colors[C - 4].g = ft_atoi(tokens[F - 4][1]);
	g->colors[C - 4].b = ft_atoi(tokens[F - 4][2]);
	g->colors[F - 4].r = ft_atoi(tokens[F - 4][0]);
	g->colors[C - 4].g = ft_atoi(tokens[F - 4][1]);
	g->colors[C - 4].b = ft_atoi(tokens[F - 4][2]);
	return (1);
}

static int	check_xml(t_game *g)
{
	g->mlx = mlx_init();
	g->img[NO] = xpm2img(g, g->data_path[NO]);
	if (g->img[NO] == NULL)
		return (0);
	g->img[SO] = xpm2img(g, g->data_path[SO]);
	if (g->img[SO] == NULL)
		return (0);
	g->img[EA] = xpm2img(g, g->data_path[EA]);
	if (g->img[EA] == NULL)
		return (0);
	g->img[WE] = xpm2img(g, g->data_path[WE]);
	if (g->img[WE] == NULL)
		return (0);
	return (1);
}

int	check_data(t_game *g)
{
	if (!check_colors(g))
		return (err_msg("Wrong color format.\n"), 0);
	if (!check_xml(g))
		return (err_msg("Can't parse images.\n"), 0);
	return (1);
}
