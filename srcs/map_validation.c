/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshamkha <pshamkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:34:31 by pshamkha          #+#    #+#             */
/*   Updated: 2024/08/31 16:16:36 by pshamkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static void	get_map()
{
	
}

static void	check_rows(char **map, int height, int width)
{
	int	i;
	int	j;

	i = -1;
	while (++i < height)
	{
		j = 0;
		while (map[i][j] == ' ')
			++j;
		if (map[i][j] != '1')
			error_exit("Borders isn't closed\n");
		j = width - 1;
		while (map[i][j] == ' ')
			--j;
		if (map[i][j] != '1')
			error_exit("Borders isn't closed\n");
	}
}

static void	check_cols(char **map, int height, int width)
{
	int	i;
	int	j;

	i = -1;
	while (++i < width)
	{
		j = 0;
		while (map[j][i] == ' ')
			++j;
		if (map[j][i] != '1')
			error_exit("Borders isn't closed\n");
		j = width - 1;
		while (map[j][i] == ' ')
			--j;
		if (map[j][i] != '1')
			error_exit("Borders isn't closed\n");
	}
}
