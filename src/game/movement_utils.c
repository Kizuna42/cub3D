/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 03:50:00 by kizuna            #+#    #+#             */
/*   Updated: 2025/06/22 03:27:29 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	is_wall(t_game *game, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (map_x < 0 || map_x >= game->scene.map_width
		|| map_y < 0 || map_y >= game->scene.map_height)
		return (1);
	return (game->scene.map[map_y][map_x] == '1');
}

int	check_collision(t_game *game, double x, double y)
{
	double	radius;
	int		i;
	int		j;
	double	check_x;
	double	check_y;

	radius = COLLISION_RADIUS;
	i = -1;
	while (++i <= 1)
	{
		j = -1;
		while (++j <= 1)
		{
			check_x = x + i * radius;
			check_y = y + j * radius;
			if (is_wall(game, check_x, check_y))
				return (1);
		}
	}
	return (0);
}
