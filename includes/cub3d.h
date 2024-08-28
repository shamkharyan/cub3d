/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshamkha <pshamkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 13:02:17 by pshamkha          #+#    #+#             */
/*   Updated: 2024/08/28 14:33:27 by pshamkha         ###   ########.fr       */
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

typedef enum s_tex
{
	NO,
	SO,
	WE,
	EA,
}	t_tex;

typedef struct s_color
{
	short	red;
	short	green;
	short	blue;
}	t_color;

typedef struct s_game
{
	void	*mlx;
	void	*mlx_win;
	void	*img_tex[4];
	int		img_width;
	int		img_height;
	t_color	*floor;
	t_color	*ceiling;
	int		map_width;
	int		map_height;
	char	**map;
}	t_game;

int		main(int argc, char **argv);
void	check_map(char *map);

void	free_split(char **tokens);
int		split_size(char **tokens);
void	error_exit(const char *err);

#endif
