/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 12:50:00 by kizuna            #+#    #+#             */
/*   Updated: 2025/07/11 12:50:01 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	**allocate_visited_array(t_scene *scene)
{
	int	**visited;
	int	i;

	visited = malloc(sizeof(int *) * scene->map_height);
	if (!visited)
		return (NULL);
	i = 0;
	while (i < scene->map_height)
	{
		visited[i] = malloc(sizeof(int) * scene->map_width);
		if (!visited[i])
		{
			while (--i >= 0)
				free(visited[i]);
			free(visited);
			return (NULL);
		}
		ft_memset(visited[i], 0, sizeof(int) * scene->map_width);
		i++;
	}
	return (visited);
}

static void	free_visited_array(int **visited, int height)
{
	int	i;

	if (!visited)
		return ;
	i = 0;
	while (i < height)
	{
		free(visited[i]);
		i++;
	}
	free(visited);
}

int	flood_fill_check(t_scene *scene, int x, int y, int **visited)
{
	if (x < 0 || y < 0 || x >= scene->map_width || y >= scene->map_height
		|| visited[y][x])
		return (1);
	if (scene->map[y][x] == '1' || scene->map[y][x] == ' ')
		return (1);
	if (is_border_position(x, y, scene))
		return (0);
	visited[y][x] = 1;
	if (!flood_fill_check(scene, x + 1, y, visited)
		|| !flood_fill_check(scene, x - 1, y, visited)
		|| !flood_fill_check(scene, x, y + 1, visited)
		|| !flood_fill_check(scene, x, y - 1, visited))
		return (0);
	return (1);
}

int	validate_map_with_flood_fill(t_scene *scene)
{
	int	**visited;
	int	player_x;
	int	player_y;
	int	result;

	visited = allocate_visited_array(scene);
	if (!visited)
		return (error_msg("Memory allocation failed for flood fill"), 0);
	player_x = (int)scene->player.pos.x;
	player_y = (int)scene->player.pos.y;
	result = flood_fill_check(scene, player_x, player_y, visited);
	free_visited_array(visited, scene->map_height);
	if (!result)
		return (error_msg("Map not closed by walls (flood fill check)"), 0);
	return (1);
} 