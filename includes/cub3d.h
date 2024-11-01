/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshamkha <pshamkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 13:02:17 by pshamkha          #+#    #+#             */
/*   Updated: 2024/10/28 18:31:39 by pshamkha         ###   ########.fr       */
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

typedef struct s_icoord
{
	int	x;
	int	y;
}	t_icoord;

typedef struct s_dcoord
{
	double	x;
	double	y;
}	t_dcoord;

typedef struct s_raycast
{
	t_dcoord	pos;
	t_dcoord	dir;
	t_dcoord	plane;
	double		cameraX;
	t_dcoord	rayDir;
	t_icoord	map;
	t_dcoord	sideDist;
	t_dcoord	deltaDist;
	double		perpWallDist;
	t_icoord	step;
	int			hit;
	int			side;
	int			lineHeight;
	int			drawStart;
	int			drawEnd;
	t_icoord	drawStEn;
}	t_raycast;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_game
{
	void		*mlx;
	void		*mlx_win;
	void		*img[4];
	t_data		*img_data;
	char		*data_path[6];
	int			img_width;
	int			img_height;
	t_color		colors[2];
	t_icoord	player;
	t_raycast	ray;
	int			map_width;
	int			map_height;
	char		**map;
}	t_game;

int		main(int argc, char **argv);
void	game_init(t_game *g);
int		check_textures(t_game *g, int fd, char **line);
int		check_map(t_game *g, int fd, char **line);
int		check_data(t_game *g);

void	free_split(char **tokens);
int		split_size(char **tokens);
// void	error_exit(const char *err);
void	err_msg(const char *err);
int		str2rgb(char *color);
int		is_empty_line(char *line);
double	ternary(int condition, double t, double f);

void	start(t_game *g);

void	clean_map(t_game *g);
void	clean_data(t_game *g);
void	clean_mlx(t_game *g);

void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
// void	draw_square(t_data *data, t_coord corner, int size, int color);
// void	draw_line(t_data *data, t_coord xy0, t_coord xy1, int color);
void	draw_vline(t_data *data, int x, t_icoord y12, int color);
void	*xpm2img(t_game *g, char *path);

#endif
