/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 03:30:00 by kizuna            #+#    #+#             */
/*   Updated: 2025/06/22 03:31:42 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	init_minimap(t_game *game)
{
	game->minimap.x = 10;
	game->minimap.y = 10;
	game->minimap.size = MINIMAP_SIZE;
	game->minimap.scale = MINIMAP_SCALE;
	game->minimap.player_size = 4;
}

void	draw_minimap_walls(t_game *game)
{
	int	map_x;
	int	map_y;
	int	pixel_x;
	int	pixel_y;
	int	tile_size;

	tile_size = (int)game->minimap.scale;
	map_y = 0;
	while (map_y < game->scene.map_height)
	{
		map_x = 0;
		while (map_x < game->scene.map_width)
		{
			if (game->scene.map[map_y][map_x] == '1')
			{
				pixel_x = game->minimap.x + (map_x * tile_size);
				pixel_y = game->minimap.y + (map_y * tile_size);
				draw_minimap_square(game, pixel_x, pixel_y, tile_size);
			}
			map_x++;
		}
		map_y++;
	}
}

void	draw_minimap_player(t_game *game)
{
	int	player_x;
	int	player_y;
	int	tile_size;
	int	i;
	int	j;

	tile_size = (int)game->minimap.scale;
	player_x = game->minimap.x + (int)(game->scene.player.pos.x * tile_size);
	player_y = game->minimap.y + (int)(game->scene.player.pos.y * tile_size);
	i = -game->minimap.player_size;
	while (i <= game->minimap.player_size)
	{
		j = -game->minimap.player_size;
		while (j <= game->minimap.player_size)
		{
			if (player_x + i >= 0 && player_x + i < WIN_WIDTH
				&& player_y + j >= 0 && player_y + j < WIN_HEIGHT)
				put_pixel(game, player_x + i, player_y + j, 0xFF0000);
			j++;
		}
		i++;
	}
}
