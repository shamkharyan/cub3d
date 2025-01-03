/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshamkha <pshamkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 13:01:22 by pshamkha          #+#    #+#             */
/*   Updated: 2024/12/27 15:25:24 by pshamkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_token(t_game *g, char **tokens, int *tokens_count)
{
	int	i;

	i = -1;
	if (split_size(tokens) != 2)
		return (i);
	if (!ft_strncmp(tokens[0], "NO", ft_strlen(tokens[0])))
		i = 0;
	else if (!ft_strncmp(tokens[0], "SO", ft_strlen(tokens[0])))
		i = 1;
	else if (!ft_strncmp(tokens[0], "WE", ft_strlen(tokens[0])))
		i = 2;
	else if (!ft_strncmp(tokens[0], "EA", ft_strlen(tokens[0])))
		i = 3;
	else if (!ft_strncmp(tokens[0], "C", ft_strlen(tokens[0])))
		i = 4;
	else if (!ft_strncmp(tokens[0], "F", ft_strlen(tokens[0])))
		i = 5;
	if (i != -1 && ++tokens_count[i] == 1)
		g->map_data[i] = ft_strdup(tokens[1]);
	return (i);
}

static int	check_token_count(int *tokens_count)
{
	int	i;

	i = 0;
	while (i < 6)
		if (tokens_count[i++] != 1)
			return (0);
	return (1);
}

//If returns 0, need to clean map_data
int	check_textures(t_game *g, int fd, char **line)
{
	char	*new_line;
	char	**tokens;
	int		tokens_count[6];

	*line = get_next_line(fd);
	ft_bzero(tokens_count, 6 * sizeof(int));
	while (*line != NULL && !check_token_count(tokens_count))
	{
		new_line = ft_strtrim(*line, " \n");
		free(*line);
		if (*new_line != '\0')
		{
			tokens = ft_split(new_line, ' ');
			if (check_token(g, tokens, tokens_count) == -1)
				return (free_split(tokens), free(new_line), 0);
			free_split(tokens);
		}
		free(new_line);
		*line = get_next_line(fd);
	}
	return (check_token_count(tokens_count));
}
