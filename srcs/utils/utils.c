/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshamkha <pshamkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 19:06:57 by pshamkha          #+#    #+#             */
/*   Updated: 2024/10/28 18:10:18 by pshamkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_split(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i] != NULL)
		free(tokens[i++]);
	free(tokens);
}

int	split_size(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i] != NULL)
		++i;
	return (i);
}

void	err_msg(const char *err)
{
	write(2, "Error: ", 7);
	write(2, err, ft_strlen(err));
}

int	is_empty_line(char *line)
{
	int	i;

	i = -1;
	while (line[++i] != '\0')
		if (line[i] != ' ' && line[i] != '\n')
			return (0);
	return (1);
}

void	game_init(t_game *g)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		g->img[i] = NULL;
		g->data_path[i] = NULL;
	}
	g->data_path[4] = NULL;
	g->data_path[5] = NULL;
	g->mlx = NULL;
	g->mlx_win = NULL;
	g->map = NULL;
	g->img_height = IMG_HEIGHT;
	g->img_width = IMG_WIDTH;
	g->map_height = 0;
	g->map_width = 0;
}

double	ternary(int condition, double t, double f)
{
	if (condition)
		return (t);
	return (f);
}
