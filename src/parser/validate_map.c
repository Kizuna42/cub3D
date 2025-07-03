/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by KIZUNA            #+#    #+#             */
/*   Updated: 2025/07/03 19:34:09 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	validate_walkable_area(t_scene *scene)
{
	int	x;
	int	y;

	y = 0;
	while (y < scene->map_height)
	{
		x = 0;
		while (x < scene->map_width)
		{
			if (scene->map[y][x] == '0')
			{
				if (is_border_position(x, y, scene))
					return (error_msg("Map not closed by walls"), 0);
				if (!check_position(x - 1, y, scene)
					|| !check_position(x + 1, y, scene)
					|| !check_position(x, y - 1, scene)
					|| !check_position(x, y + 1, scene))
					return (error_msg("Map not closed by walls"), 0);
			}
			x++;
		}
		y++;
	}
	return (1);
}

int	validate_map(t_scene *scene)
{
	if (!validate_required_elements(scene))
		return (0);
	if (!scene->map || scene->map_height == 0 || scene->map_width == 0)
		return (error_msg("Invalid map dimensions"), 0);
	if (scene->map_height < 3 || scene->map_width < 3)
		return (error_msg("Map too small (minimum 3x3)"), 0);
	if (!validate_player_position(scene))
		return (0);
	if (!validate_walkable_area(scene))
		return (0);
	return (1);
}
