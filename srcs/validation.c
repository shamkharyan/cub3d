/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshamkha <pshamkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 13:01:22 by pshamkha          #+#    #+#             */
/*   Updated: 2024/08/31 18:38:25 by pshamkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_color(t_game *g, char *line, int i)
{
	char	**colors;

	if (*line == ',' || line[ft_strlen(line) - 1] == ',')
		return (0);
	colors = ft_split(line, ',');
	if (split_size(colors) == 3)
	{
		g->colors[i].r = str2rgb(colors[0]);
		g->colors[i].g = str2rgb(colors[1]);
		g->colors[i].b = str2rgb(colors[2]);
		if (g->colors[i].r != -1 && g->colors[i].b != -1
			&& g->colors[i].g != -1)
			return (free_split(colors), 1);
	}
	free_split(colors);
	return (0);
}

static int	is_tex_or_color(t_game *g, char **tokens)
{
	int	i;

	if (!ft_strncmp(tokens[0], "NO", ft_strlen(tokens[0])))
		i = 0;
	else if (!ft_strncmp(tokens[0], "SO", ft_strlen(tokens[0])))
		i = 1;
	else if (!ft_strncmp(tokens[0], "WE", ft_strlen(tokens[0])))
		i = 2;
	else if (!ft_strncmp(tokens[0], "EA", ft_strlen(tokens[0])))
		i = 3;
	else if (!ft_strncmp(tokens[0], "C", ft_strlen(tokens[0])))
		i = 4;
	else if (!ft_strncmp(tokens[0], "F", ft_strlen(tokens[0])))
		i = 5;
	else
		i = -1;
	if (i >= 0 && i <= 3)
		g->img_path[i] = ft_strdup(tokens[1]);
	else if (i == 4 || i == 5)
		if (!check_color(g, tokens[1], i - 4))
			return (-1);
	return (i);
}

static void	check_textures(t_game *g, int fd)
{
	int		i;
	int		img[6];
	char	*line;
	char	*new_line;
	char	**tokens;

	line = get_next_line(fd);
	ft_bzero(img, 6 * sizeof(int));
	while (line != NULL)
	{
		new_line = ft_strtrim(line, "\n ");
		free(line);
		tokens = ft_split(new_line, ' ');
		if (split_size(tokens) == 2 && *tokens[0] != '1')
		{
			i = is_tex_or_color(g, tokens);
			if (i >= 0 && i <= 5)
				++img[i];
			else if (i == -1)
			{
				free(new_line);
				free_split(tokens);
				error_exit("Wrong token name or value\n");
			}
		}
		else if (split_size(tokens) != 0 && *tokens[0] == '1')
			break ;
		else if (split_size(tokens) != 0)
			error_exit("Wrong amount of values\n");
		free_split(tokens);
		free(new_line);
		line = get_next_line(fd);
	}
	i = 0;
	while (i < 6)
		if (img[i++] != 1)
			error_exit("Wrong amount of tokens\n");
}

void	check_map(t_game *g, char *path)
{
	int	fd;

	if (ft_strlen(path) <= 4
		|| ft_strncmp(path + ft_strlen(path) - 4, ".cub", 4))
		error_exit("Wrong extention of the map\n");
	fd = open(path, O_RDONLY);
	if (fd < 0)
		error_exit("Can't open file or file not exist\n");
	check_textures(g, fd);
	close(fd);
}
