/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshamkha <pshamkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 13:01:22 by pshamkha          #+#    #+#             */
/*   Updated: 2024/08/28 16:46:06 by pshamkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_ext_empty(char *map, int fd)
{
	char	*line;

	if (ft_strlen(map) <= 4
		|| ft_strncmp(map + ft_strlen(map) - 4, ".cub", 4))
		error_exit("Wrong extention of the map\n");
	if (fd < 0)
		error_exit("Can't open file or file not exist\n");
	line = get_next_line(fd);
	if (line == NULL)
		error_exit("Empty map\n");
	free(line);
}

static int	is_tex_or_color(char *token)
{
	if (!ft_strncmp(token, "NO", ft_strlen(token)))
		return (0);
	else if (!ft_strncmp(token, "SO", ft_strlen(token)))
		return (1);
	else if (!ft_strncmp(token, "WE", ft_strlen(token)))
		return (2);
	else if (!ft_strncmp(token, "EA", ft_strlen(token)))
		return (3);
	else if (!ft_strncmp(token, "C", ft_strlen(token)))
		return (4);
	else if (!ft_strncmp(token, "F", ft_strlen(token)))
		return (5);
	else if (!ft_strncmp(token, "\n", ft_strlen(token)))
		return (6);
	else if (!ft_strncmp(token, "1", 1))
		return (7);
	else
		return (-1);
}

static void	check_textures(int fd)
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
		new_line = ft_strtrim(line, " \n");
		free(line);
		tokens = ft_split(new_line, ' ');
		if (split_size(tokens) <= 2)
		{
			i = is_tex_or_color(tokens[0]);
			if (i >= 0 && i <= 5)
				++img[i];
			else if (i == -1)
			{
				free(new_line);
				free_split(tokens);
				error_exit("Wrong token name\n");
			}
			else if (i == 7)
				break;
		}
		else
			error_exit("Wrong token count\n");
		free_split(tokens);
		free(new_line);
		line = get_next_line(fd);
	}
	i = 0;
	while (i < 6)
		if (img[i++] != 1)
			error_exit("Wrong amount of tokens\n");
}

void	check_map(char *map)
{
	int	fd;

	fd = open(map, O_RDONLY);
	check_ext_empty(map, fd);
	close(fd);
	get_next_line(-1);
	fd = open(map, O_RDONLY);
	check_textures(fd);
	close(fd);
}
