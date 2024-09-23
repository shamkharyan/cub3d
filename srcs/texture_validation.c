/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_validation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamkharyan <shamkharyan@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 13:01:22 by pshamkha          #+#    #+#             */
/*   Updated: 2024/09/24 00:05:22 by shamkharyan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// static int	check_color(t_game *g, char *line, int i)
// {
// 	char	**colors;

// 	if (*line == ',' || line[ft_strlen(line) - 1] == ',')
// 		return (0);
// 	colors = ft_split(line, ',');
// 	if (split_size(colors) == 3)
// 	{
// 		g->colors[i].r = str2rgb(colors[0]);
// 		g->colors[i].g = str2rgb(colors[1]);
// 		g->colors[i].b = str2rgb(colors[2]);
// 		if (g->colors[i].r != -1 && g->colors[i].b != -1
// 			&& g->colors[i].g != -1)
// 			return (free_split(colors), 1);
// 	}
// 	free_split(colors);
// 	return (0);
// }

static int	check_token(t_game *g, char **tokens, int *tokens_count)
{
	int	i;

	if (split_size(tokens) == 2)
	{
		i = -1;
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
		if (i != -1 && ++tokens_count[i] == 1)
			g->data_path[i] = ft_strdup(tokens[1]);
		return (i);
	}
	return (-1);
}

static int	check_tokens_count(int *tokens_count)
{
	int	i;

	i = 0;
	while (i < 6)
		if (tokens_count[i++] != 1)
			return (0);
	return (1);
}

static int	check_texts(t_game *g, int fd)
{
	char	*line;
	char	*new_line;
	char	**tokens;
	int		tokens_count[6];
	int		flag;

	line = get_next_line(fd);
	ft_bzero(tokens_count, 6 * sizeof(int));
	flag = 0;
	while (line != NULL && !check_tokens_count(tokens_count))
	{
		new_line = ft_strtrim(line, " \n");
		free(line);
		if (*new_line != '\0')
		{
			tokens = ft_split(new_line, ' ');
			flag = check_token(g, tokens, tokens_count);
			free_split(tokens);
			if (flag == -1)
				error_exit("Wrong token or token count\n");
		}
		free(new_line);
		line = get_next_line(fd);
	}
	return (check_tokens_count(tokens_count));
}

void	check_textures(t_game *g, char *path)
{
	int	fd;

	if (ft_strlen(path) <= 4
		|| ft_strncmp(path + ft_strlen(path) - 4, ".cub", 4))
		error_exit("Wrong extention of the map\n");
	fd = open(path, O_RDONLY);
	if (fd < 0)
		error_exit("Can't open file or file not exist\n");
	if (!check_texts(g, fd))
		error_exit("Wrong token count\n");
	close(fd);
}
