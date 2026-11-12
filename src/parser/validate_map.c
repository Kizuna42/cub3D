/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by KIZUNA            #+#    #+#             */
/*   Updated: 2026/11/12 12:00:00 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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
	if (!validate_map_closed(scene))
		return (0);
	return (1);
}
