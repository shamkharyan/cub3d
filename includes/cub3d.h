/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshamkha <pshamkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 13:02:17 by pshamkha          #+#    #+#             */
/*   Updated: 2024/10/01 18:49:32 by pshamkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H

# define CUB3D_H

# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include "get_next_line.h"
# include <stdio.h>
# include <fcntl.h>
# include <math.h>

# define KEY_W 13
# define KEY_S 1
# define KEY_A 0
# define KEY_D 2
# define KEY_ESC 53

# define IMG_WIDTH 64
# define IMG_HEIGHT 64

# define WIN_WIDTH 1024
# define WIN_HEIGHT 512

typedef enum s_textures
{
	NO,
	SO,
	WE,
	EA,
	C,
	F
}	t_textures;

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_cord
{
	int	x;
	int	y;
}	t_cord;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
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
	t_cord	player;
	int		map_width;
	int		map_height;
	char	**map;
}	t_game;

int		main(int argc, char **argv);
void	game_init(t_game *g);
int		check_textures(t_game *g, int fd, char **line);
int		check_map(t_game *g, int fd, char **line);
int		check_data(t_game *g);

void	free_split(char **tokens);
int		split_size(char **tokens);
void	error_exit(const char *err);
void	err_msg(const char *err);
int		str2rgb(char *color);
int		is_empty_line(char *line);
void	*xpm2img(t_game *g, char *path);

void	start(t_game *g);

void	clean_map(t_game *g);
void	clean_data(t_game *g);
void	clean_mlx(t_game *g);

#endif
