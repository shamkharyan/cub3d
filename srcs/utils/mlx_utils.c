/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshamkha <pshamkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 11:25:01 by pshamkha          #+#    #+#             */
/*   Updated: 2024/10/05 15:45:57 by pshamkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*xpm2img(t_game *g, char *path)
{
	return (mlx_xpm_file_to_image(g->mlx, path, &g->img_width, &g->img_height));
}
