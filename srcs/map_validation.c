/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamkharyan <shamkharyan@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:34:31 by pshamkha          #+#    #+#             */
/*   Updated: 2024/09/25 00:13:49 by shamkharyan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// static void	check_rows(char **map, int height, int width)
// {
// 	int	i;
// 	int	j;

// 	i = -1;
// 	while (++i < height)
// 	{
// 		j = 0;
// 		while (map[i][j] == ' ')
// 			++j;
// 		if (map[i][j] != '1')
// 			error_exit("Borders isn't closed\n");
// 		j = width - 1;
// 		while (map[i][j] == ' ')
// 			--j;
// 		if (map[i][j] != '1')
// 			error_exit("Borders isn't closed\n");
// 	}
// }

// static void	check_cols(char **map, int height, int width)
// {
// 	int	i;
// 	int	j;

// 	i = -1;
// 	while (++i < width)
// 	{
// 		j = 0;
// 		while (map[j][i] == ' ')
// 			++j;
// 		if (map[j][i] != '1')
// 			error_exit("Borders isn't closed\n");
// 		j = width - 1;
// 		while (map[j][i] == ' ')
// 			--j;
// 		if (map[j][i] != '1')
// 			error_exit("Borders isn't closed\n");
// 	}
// }

static void	parse_map(t_game *g, t_list *head)
{
	t_list	*temp;
	int		i;
	int		j;

	g->map = (char **) malloc(g->map_height * sizeof(char *));
	temp = head;
	i = -1;
	while (++i < g->map_height)
		g->map[i] = (char *) malloc(g->map_width * sizeof(char));
	i = -1;
	while (++i < g->map_height)
	{
		j = -1;
		while (++j < (int) ft_strlen((char *) temp->content))
			map[i][j] = temp->content[j];
		while (++j < g->map_width)
			map[i][j] = ' ';
		map[i][j] = '\0';
	}
}

static void	get_map(t_game *g, int fd, char **line)
{
	t_list	*head;
	t_list	*temp;
	
	while (*line != NULL && is_empty_line(*line))
	{
		free(*line);
		*line = get_next_line(fd);
	}
	head = NULL;
	while (*line != NULL && !is_empty_line(*line))
	{
		ft_lstadd_back(&head, ft_lstnew(ft_strdup(*line)));
		free(*line);
		*line = get_next_line(fd);
	}
	free(*line);
	g->map_height = ft_lstsize(head);
	temp = head;
	while (temp != NULL)
	{
		if (g->map_width < (int) ft_strlen(temp->content))
			g->map_width = (int) ft_strlen(temp->content);
		temp = temp->next;
	}
	parse_map(g, head);
}



void	check_map(t_game *g, int fd, char **line)
{
	get_map(g, fd, line);
}
