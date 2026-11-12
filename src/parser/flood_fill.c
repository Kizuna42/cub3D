/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 12:50:00 by kizuna            #+#    #+#             */
/*   Updated: 2026/11/12 12:00:00 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	is_open_cell(t_scene *scene, int x, int y)
{
	if (x < 0 || y < 0 || x >= scene->map_width || y >= scene->map_height)
		return (1);
	return (scene->map[y][x] == ' ');
}

static void	push_cell(t_fill *fill, int x, int y)
{
	t_scene	*scene;

	scene = fill->scene;
	if (x < 0 || y < 0 || x >= scene->map_width || y >= scene->map_height)
		return ;
	if (scene->map[y][x] != '0'
		|| fill->visited[(size_t)y * scene->map_width + x])
		return ;
	fill->visited[(size_t)y * scene->map_width + x] = 1;
	fill->stack[fill->top++] = (size_t)y * scene->map_width + x;
}

static int	fill_region(t_fill *fill, int start_x, int start_y)
{
	t_scene	*s;
	size_t	idx;
	int		x;
	int		y;

	s = fill->scene;
	push_cell(fill, start_x, start_y);
	while (fill->top > 0)
	{
		idx = fill->stack[--fill->top];
		x = (int)(idx % s->map_width);
		y = (int)(idx / s->map_width);
		if (is_border_position(x, y, s) || is_open_cell(s, x - 1, y)
			|| is_open_cell(s, x + 1, y) || is_open_cell(s, x, y - 1)
			|| is_open_cell(s, x, y + 1))
			return (0);
		push_cell(fill, x + 1, y);
		push_cell(fill, x - 1, y);
		push_cell(fill, x, y + 1);
		push_cell(fill, x, y - 1);
	}
	return (1);
}

static int	fill_all_regions(t_fill *fill)
{
	t_scene	*s;
	int		x;
	int		y;

	s = fill->scene;
	y = 0;
	while (y < s->map_height)
	{
		x = 0;
		while (x < s->map_width)
		{
			if (s->map[y][x] == '0'
				&& !fill->visited[(size_t)y * s->map_width + x]
				&& !fill_region(fill, x, y))
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

/*
** Iterative flood fill (explicit stack on the heap, no recursion).
** Every walkable cell ('0', the player spawn is stored as '0') must be off
** the map border and must not touch a space or the outside of the map.
** Each region of walkable cells is filled once, so unreachable regions are
** checked as well.
*/
int	validate_map_closed(t_scene *scene)
{
	t_fill	fill;
	size_t	cells;
	int		result;

	cells = (size_t)scene->map_width * scene->map_height;
	fill.scene = scene;
	fill.top = 0;
	fill.visited = ft_calloc(cells, sizeof(char));
	fill.stack = malloc(sizeof(size_t) * cells);
	if (!fill.visited || !fill.stack)
	{
		free(fill.visited);
		free(fill.stack);
		return (error_msg("Memory allocation failed for flood fill"), 0);
	}
	result = fill_all_regions(&fill);
	free(fill.visited);
	free(fill.stack);
	if (!result)
		return (error_msg("Map not closed by walls"), 0);
	return (1);
}
