/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshamkha <pshamkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 19:06:57 by pshamkha          #+#    #+#             */
/*   Updated: 2024/10/01 16:29:08 by pshamkha         ###   ########.fr       */
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

/*void	*xpm2img(t_game *g, char *path)
{
	return (mlx_xpm_file_to_image(g->mlx, path, &g->img_width, &g->img_height));
}*/

void	error_exit(const char *err)
{
	write(2, "Error: ", 7);
	write(2, err, ft_strlen(err));
	exit(1);
}

int	str2rgb(char *color)
{
	int	i;
	int	rgb;

	i = 0;
	while (ft_isdigit(color[i]) && color[i] != '\0')
		++i;
	if (i < 4 && color[i] == '\0')
	{
		rgb = ft_atoi(color);
		if (rgb < 256)
			return (rgb);
	}
	return (-1);
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
