/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshamkha <pshamkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 13:01:22 by pshamkha          #+#    #+#             */
/*   Updated: 2024/08/22 19:09:27 by pshamkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_ext(char *map)
{
	return (ft_strlen(map) > 4
		&& !ft_strncmp(map + ft_strlen(map) - 4, ".cub", 4));
}

static int	check_textures(t_game *g, char *map)
{
	int		fd;
	char	*line;
	char	**tokens;
	int		i;

	fd = open(map, O_RDONLY);
	line = get_next_line(fd);
	line[ft_strlen(line) - 1] = '\0';
	while (line != NULL)
	{
		tokens = ft_split(line, ' ');
		if (split_size(tokens) == 2)
		{
			if (!ft_strncmp(tokens[0], "NO", ft_strlen(tokens[0])))
				i = NO;
			else if (!ft_strncmp(tokens[0], "SO", ft_strlen(tokens[0])))
				i = SO;
			else if (!ft_strncmp(tokens[0], "WE", ft_strlen(tokens[0])))
				i = WE;
			else if (!ft_strncmp(tokens[0], "EA", ft_strlen(tokens[0])))
				i = EA;
			else
				i = -1;
			if (i != -1)
			{
				printf("%s:\n", tokens[1]);
				g->img_tex[i] = xpm2img(g, tokens[1]);
				if (g->img_tex[i] == NULL)
				{
					printf("Error: Invalid path to texture\n");
					return (0);
				}
				free(line);
				line = get_next_line(fd);
				line[ft_strlen(line) - 1] = '\0';
			}
			else
			{
				printf("Error: Invalid parameter\n");
				return (0);
			}
		}
		else
		{
			printf("Error: Invalid parameter\n");
			return (0);
		}
	}
	return (1);
}

int	check_map(t_game *g, char *map)
{
	int		fd;
	char	*line;

	if (check_ext(map))
	{
		fd = open(map, O_RDONLY);
		if (fd < 0)
		{
			printf("Error: Can't open file or file not exist\n");
			return (0);
		}
		line = get_next_line(fd);
		if (line == NULL)
		{
			printf("Error: Empty map\n");
			return (close(fd), 0);
		}
		close(fd);
		check_textures(g, map);
	}
	else
	{
		printf("Error: Wrong extention\n");
		return (0);
	}
	return (1);
}
