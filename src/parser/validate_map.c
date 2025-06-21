/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by KIZUNA            #+#    #+#             */
/*   Updated: 2025/06/21 23:47:13 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	is_border_position(int x, int y, t_map *map)
{
	return (x == 0 || y == 0 || x == map->width - 1 || y == map->height - 1);
}

static int	check_position(int x, int y, t_map *map)
{
	if (x < 0 || y < 0 || x >= map->width || y >= map->height)
		return (0);
	if (map->grid[y][x] == ' ')
		return (0);
	return (1);
}

static int	validate_walkable_area(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->grid[y][x] == '0')
			{
				if (is_border_position(x, y, map))
					return (0);
				if (!check_position(x - 1, y, map) || 
					!check_position(x + 1, y, map) ||
					!check_position(x, y - 1, map) || 
					!check_position(x, y + 1, map))
					return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}

int	validate_map(t_scene *scene)
{
	if (!scene->map.grid || scene->map.height == 0 || scene->map.width == 0)
		return (0);
	return (validate_walkable_area(&scene->map));
} 