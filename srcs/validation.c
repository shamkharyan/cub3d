/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshamkha <pshamkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 13:01:22 by pshamkha          #+#    #+#             */
/*   Updated: 2024/08/21 18:36:58 by pshamkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_ext(char *map)
{
	return (ft_strlen(map) > 4
		&& !ft_strncmp(map + ft_strlen(map) - 4, ".cub", 4));
}

static int	check_textures(char *map, t_game *game)
{
	int		fd;
	char	*line;
	char	**tokens;

	fd = open(map, O_RDONLY);
	line = get_next_line(fd);
	
}

int	check_map(char *map, t_game *game)
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
	}
	else
	{
		printf("Error: Wrong extention\n");
		return (0);
	}
	return (1);
}
