/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamkharyan <shamkharyan@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 13:02:17 by pshamkha          #+#    #+#             */
/*   Updated: 2024/09/24 23:17:49 by shamkharyan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H

# define CUB3D_H

# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include "get_next_line.h"
# include <stdio.h>
# include <fcntl.h>

# define KEY_W 13
# define KEY_S 1
# define KEY_A 0
# define KEY_D 2
# define KEY_ESC 53

# define TEX_WIDTH 64
# define TEX_HEIGHT 64

typedef struct s_color
{
	short	r;
	short	g;
	short	b;
}	t_color;

typedef struct s_game
{
	void	*mlx;
	void	*mlx_win;
	void	*img[4];
	char	*data_path[6];
	int		img_width;
	int		img_height;
	t_color	colors[2];
	int		map_width;
	int		map_height;
	char	**map;
}	t_game;

int		main(int argc, char **argv);
void	check_textures(t_game *g, char *path);
void	check_map(t_game *g, int fd, char **line);

void	free_split(char **tokens);
int		split_size(char **tokens);
void	error_exit(const char *err);
int		str2rgb(char *color);
int		is_empty_line(char *line);

#endif
