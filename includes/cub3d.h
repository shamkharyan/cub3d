/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshamkha <pshamkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 13:02:17 by pshamkha          #+#    #+#             */
/*   Updated: 2024/12/25 18:53:27 by pshamkha         ###   ########.fr       */
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
# define KEY_Q 12
# define KEY_E 14

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

typedef struct s_vector2i
{
	int	x;
	int	y;
}	t_vector2i;

typedef struct s_vector2f
{
	double	x;
	double	y;
}	t_vector2f;

typedef struct s_minimap
{
	int			scale;
	t_vector2i	offset;
	t_vector2i	size;
	int			border_width;
	int			wall_color;
	int			player_color;
	int			void_color;
	int			ground_color;
	int			border_color;
}	t_minimap;

typedef struct s_player
{
	t_vector2f	pos;
	t_vector2f	dir;
	t_vector2f	plane;
}	t_player;

typedef struct s_raycast
{
	t_vector2f	ray_dir;
	t_vector2i	map;
	t_vector2f	side_dist;
	t_vector2f	delta_dist;
	double		perp_wall_dist;
	t_vector2i	step;
	int			hit;
	int			side;
	int			tex_ind;
	double		wall_x;
	t_vector2i	tex_pos;
	int			color;
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
	t_player	player;
	t_raycast	ray;
	t_vector2i	start_pos;
	int			map_width;
	int			map_height;
	char		**map;
	t_minimap	minimap;
	int			prev_mouse_x;
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
void	*xpm2img(t_game *g, char *path);

int		exit_game(t_game *g);
int		movement(int keycode, t_game *game);
int		draw_scene(t_game *g);
void	clean_scene(t_game *g);
int		get_tex_color(t_textures *texture, t_vector2i tex_pos);
int		mouse_rotate(int x, int y, t_game *g);

void	init_minimap(t_game *g);
void	draw_minimap(t_game *g);
void	draw_rectangle(t_game *g, t_vector2i start, t_vector2i size, int color);
void	draw_circle(t_game *g, t_vector2i start, int radius, int color);
void	draw_vline(t_game *g, int x);
void	init_player(t_game *g);
void	init_game(t_game *g);
void	clean_scene(t_game *g);
void	setup_dda_x(t_game *g);
void	setup_dda_y(t_game *g);
void	set_new_pos(t_game *g, t_vector2f move_dir);

#endif
