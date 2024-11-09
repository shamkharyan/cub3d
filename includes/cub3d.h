/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshamkha <pshamkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 13:02:17 by pshamkha          #+#    #+#             */
/*   Updated: 2024/11/09 17:41:32 by pshamkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H

# define CUB3D_H

# include "../libft/libft.h"
# include <mlx.h>
# include "get_next_line.h"
# include <stdio.h>
# include <fcntl.h>
# include <math.h>

//Linux
// # define KEY_W 119
// # define KEY_UP 65362
// # define KEY_S 115
// # define KEY_DOWN 65364
// # define KEY_A 97
// # define KEY_LEFT 65361
// # define KEY_D 100
// # define KEY_RIGHT 65363
// # define KEY_ESC 65307

//MacOS
# define KEY_W 13
# define KEY_UP 126
# define KEY_S 1
# define KEY_DOWN 125
# define KEY_A 0
# define KEY_LEFT 123
# define KEY_D 2
# define KEY_RIGHT 124
# define KEY_ESC 53

# define TEXTURE_W 64
# define TEXTURE_H 64

# define SCREEN_W 1024
# define SCREEN_H 720

# define MOVE_SPEED 0.35
# define ROT_SPEED 0.1
# define MOUSE_ROT_SPEED 0.005

typedef enum s_directions
{
	NO,
	SO,
	WE,
	EA,
	C,
	F
}	t_directions;

typedef struct s_textures
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		width;
	int		height;
	int		endian;
}	t_textures;

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
	double		camera_x;
	t_dcoord	ray_dir;
	t_icoord	map;
	t_dcoord	side_dist;
	t_dcoord	delta_dist;
	double		perp_wall_dist;
	t_icoord	step;
	int			hit;
	int			side;
	int			line_height;
	int			draw_start;
	int			draw_end;
	int			tex_num;
	double		wall_x;
	t_icoord	tex;
	int			color;
	int			prev_mouse_x;
}	t_raycast;

typedef struct s_game
{
	void		*mlx;
	void		*mlx_win;
	t_textures	walls[4];
	t_textures	screen_buff;
	char		*map_data[6];
	int			tex_width;
	int			tex_height;
	int			colors[2];
	t_icoord	player;
	t_raycast	ray;
	int			map_width;
	int			map_height;
	char		**map;
}	t_game;

int		main(int argc, char **argv);
void	game_init(t_game *g);
int		check_extention(char *path);
int		check_textures(t_game *g, int fd, char **line);
int		check_map(t_game *g, int fd, char **line);
int		check_data(t_game *g);

void	free_split(char **tokens);
int		split_size(char **tokens);
void	err_msg(const char *err);
int		str2rgb(char *color);
int		is_empty_line(char *line);
double	ternary(int condition, double t, double f);
int		create_trgb(int t, int r, int g, int b);

void	start(t_game *g);

void	clean_map(t_game *g);
void	clean_data(t_game *g);
void	clean_mlx(t_game *g);

void	my_mlx_pixel_put(t_textures *data, int x, int y, int color);
void	draw_vline(t_textures *data, int x, t_icoord y12, int color);
void	*xpm2img(t_game *g, char *path);

int		exit_game(t_game *g);
int		movement(int keycode, t_game *game);
int		draw_scene(t_game *g);
void	clean_scene(t_game *g);
int		get_texture_color(t_textures *texture, int x, int y);
int		mouse_rotate(int x, int y, t_game *g);

#endif
