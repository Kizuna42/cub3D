/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 23:45:00 by kizuna            #+#    #+#             */
/*   Updated: 2025/07/03 19:42:03 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	validate_required_elements(t_scene *scene)
{
	if (!scene->north_texture)
		return (error_msg("Missing north texture (NO)"), 0);
	if (!scene->south_texture)
		return (error_msg("Missing south texture (SO)"), 0);
	if (!scene->west_texture)
		return (error_msg("Missing west texture (WE)"), 0);
	if (!scene->east_texture)
		return (error_msg("Missing east texture (EA)"), 0);
	if (!scene->has_floor)
		return (error_msg("Missing floor color (F)"), 0);
	if (!scene->has_ceiling)
		return (error_msg("Missing ceiling color (C)"), 0);
	return (1);
}

int	is_border_position(int x, int y, t_scene *scene)
{
	return (x == 0 || y == 0 || x == scene->map_width - 1
		|| y == scene->map_height - 1);
}

int	check_position(int x, int y, t_scene *scene)
{
	if (x < 0 || y < 0 || x >= scene->map_width || y >= scene->map_height)
		return (0);
	if (scene->map[y][x] == ' ')
		return (0);
	return (1);
}

int	validate_player_position(t_scene *scene)
{
	int	x;
	int	y;

	if (scene->player.spawn_dir == 0)
		return (error_msg("No player position found"), 0);
	x = (int)scene->player.pos.x;
	y = (int)scene->player.pos.y;
	if (is_border_position(x, y, scene))
		return (error_msg("Player cannot be on map border"), 0);
	return (1);
}
