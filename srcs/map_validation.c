/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshamkha <pshamkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:34:31 by pshamkha          #+#    #+#             */
/*   Updated: 2024/10/01 16:31:43 by pshamkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_borders(t_game *g)
{
	int	i;
	int	j;

	i = -1;
	while (++i < g->map_height)
	{
		j = -1;
		while (++j < g->map_width)
		{
			if (g->map[i][j] == '0')
			{
				if (i == 0 || i == g->map_height - 1 || j == 0 || j == g->map_width - 1)
					return (0);
				if (g->map[i][j + 1] == ' ')
					return (0);
				if (g->map[i][j - 1] == ' ')
					return (0);
				if (g->map[i + 1][j] == ' ')
					return (0);
				if (g->map[i - 1][j] == ' ')
					return (0);
			}
		}
	}
	return (1);
}

static int	check_content(t_game *g)
{
	int	i;
	int	j;
	int	player;

	player = 0;
	i = -1;
	while (++i < g->map_height)
	{
		j = -1;
		while (++j < g->map_width)
		{
			if (g->map[i][j] == 'N' || g->map[i][j] == 'S' || g->map[i][j] == 'E' || g->map[i][j] == 'W')
			{
				g->player.x = j;
				g->player.y = i;
				++player;
			}
			else if (g->map[i][j] != '1' && g->map[i][j] != '0' && g->map[i][j] != ' ')
				return (0);
		}
	}
	return (player == 1);
}

static void	parse_map(t_game *g, t_list *head)
{
	t_list	*temp;
	int		i;
	int		j;

	g->map = (char **) malloc(g->map_height * sizeof(char *));
	temp = head;
	i = -1;
	while (++i < g->map_height)
	{
		g->map[i] = (char *) malloc((g->map_width + 1) * sizeof(char));
		j = -1;
		while (++j < g->map_width)
			if (j < (int) ft_strlen((char *) temp->content))
				g->map[i][j] = *((char *) temp->content + j);
			else
				g->map[i][j] = ' ';
		g->map[i][j] = '\0';
		temp = temp->next;
	}
	ft_lstclear(&head, free);
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
		ft_lstadd_back(&head, ft_lstnew(ft_strtrim(*line, "\n")));
		free(*line);
		*line = get_next_line(fd);
	}
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
	if (!check_content(g))
		error_exit("Wront content of the map\n");
	if (!check_borders(g))
		error_exit("Borders aren't closed\n");
	while (*line != NULL && is_empty_line(*line))
	{
		free(*line);
		*line = get_next_line(fd);
	}
	if (*line != NULL)
		free(*line), error_exit("Content after map\n");

}
