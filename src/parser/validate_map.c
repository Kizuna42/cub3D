/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by KIZUNA            #+#    #+#             */
/*   Updated: 2025/06/22 00:32:42 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	validate_required_elements(t_scene *scene)
{
	if (!scene->north_texture)
		return (error_msg("Missing north texture (NO)"), 0);
	if (!scene->south_texture)
		return (error_msg("Missing south texture (SO)"), 0);
	if (!scene->west_texture)
		return (error_msg("Missing west texture (WE)"), 0);
	if (!scene->east_texture)
		return (error_msg("Missing east texture (EA)"), 0);
	if (scene->floor_color == -1)
		return (error_msg("Missing floor color (F)"), 0);
	if (scene->ceiling_color == -1)
		return (error_msg("Missing ceiling color (C)"), 0);
	return (1);
}

static int	is_border_position(int x, int y, t_scene *scene)
{
	return (x == 0 || y == 0 || x == scene->map_width - 1
		|| y == scene->map_height - 1);
}

static int	check_position(int x, int y, t_scene *scene)
{
	if (x < 0 || y < 0 || x >= scene->map_width || y >= scene->map_height)
		return (0);
	if (scene->map[y][x] == ' ')
		return (0);
	return (1);
}

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

static int	validate_player_position(t_scene *scene)
{
	if (scene->player.spawn_dir == 0)
		return (error_msg("No player position found"), 0);
	return (1);
}

int	validate_map(t_scene *scene)
{
	if (!validate_required_elements(scene))
		return (0);
	if (!scene->map || scene->map_height == 0 || scene->map_width == 0)
		return (error_msg("Invalid map dimensions"), 0);
	if (!validate_player_position(scene))
		return (0);
	if (!validate_walkable_area(scene))
		return (0);
	return (1);
}
