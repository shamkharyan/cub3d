/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshamkha <pshamkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 14:28:55 by shamkharyan       #+#    #+#             */
/*   Updated: 2024/11/07 17:05:20 by pshamkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_extention(char *path)
{
	if (ft_strlen(path) <= 4
		|| !ft_strncmp(path + ft_strlen(path) - 5, "/.cub", 5)
		|| ft_strncmp(path + ft_strlen(path) - 4, ".cub", 4))
		return (0);
	return (1);
}

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

int	is_empty_line(char *line)
{
	int	i;

	i = -1;
	while (line[++i] != '\0')
		if (line[i] != ' ' && line[i] != '\n')
			return (0);
	return (1);
}

void	*xpm2img(t_game *g, char *path)
{
	return (mlx_xpm_file_to_image(g->mlx, path, &g->img_width, &g->img_height));
}
