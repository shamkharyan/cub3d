/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamkharyan <shamkharyan@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 13:01:42 by pshamkha          #+#    #+#             */
/*   Updated: 2024/09/27 22:51:33 by shamkharyan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_all(t_game *g, char *path)
{
	int		fd;
	char	*last_line;

	if (ft_strlen(path) <= 4
		|| ft_strncmp(path + ft_strlen(path) - 4, ".cub", 4))
		error_exit("Wrong extention of the map.\n");
	fd = open(path, O_RDONLY);
	if (fd < 0)
		error_exit("Can't open file or file not exist.\n");
	if (!check_textures(g, fd, &last_line))
		error_exit("Wrong token name or count.\n");
	g->map_width = 0;
	check_map(g, fd, &last_line);
	close(fd);
	return (1);
}

int	main(int argc, char **argv)
{
	t_game	g;

	if (argc == 2)
	{
		check_all(&g, argv[1]);
		printf("OK\n");
		//check_map(&g, argv[1]);
	}
	else
		error_exit("Wrong number of parameters\n");
	return (0);
}
