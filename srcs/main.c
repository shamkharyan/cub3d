/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshamkha <pshamkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 13:01:42 by pshamkha          #+#    #+#             */
/*   Updated: 2024/12/27 18:26:16 by pshamkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_fd(char *path)
{
	int		fd;
	char	*trimed;

	trimed = ft_strtrim(path, " \t");
	if (!check_extention(trimed))
	{
		free(trimed);
		return (err_msg("Wrong extention of the map.\n"), 0);
	}
	fd = open(trimed, O_RDONLY);
	free(trimed);
	return (fd);
}

static int	check_all(t_game *g, char *path)
{
	int		fd;
	char	*last_line;

	fd = get_fd(path);
	if (fd < 0)
		return (err_msg("Can't open file or file not exist.\n"), 0);
	if (!check_textures(g, fd, &last_line))
	{
		err_msg("Wrong token name or count.\n");
		clean_data(g);
		return (close(fd), 0);
	}
	if (!check_map(g, fd, &last_line))
	{
		clean_map(g);
		return (clean_data(g), close(fd), 0);
	}
	if (!check_data(g))
	{
		clean_map(g);
		clean_mlx(g);
		return (close(fd), clean_data(g), 0);
	}
	return (clean_data(g), close(fd), 1);
}

int	main(int argc, char **argv)
{
	t_game	g;

	if (argc == 2)
	{
		setup_game(&g);
		if (!check_all(&g, argv[1]))
			return (0);
		printf("OK\n");
		start(&g);
	}
	else
		return (err_msg("Wrong number of arguments.\n"), 1);
	return (0);
}
