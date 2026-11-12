/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 03:45:00 by kizuna            #+#    #+#             */
/*   Updated: 2025/07/11 15:32:35 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	draw_minimap_square_color(t_game *game, int x, int y, int color)
{
	int	i;
	int	j;
	int	size;

	size = (int)game->minimap.scale;
	i = 0;
	while (i < size && x + i < game->minimap.x + game->minimap.size)
	{
		j = 0;
		while (j < size && y + j < game->minimap.y + game->minimap.size)
		{
			if (x + i >= 0 && x + i < WIN_WIDTH
				&& y + j >= 0 && y + j < WIN_HEIGHT)
				put_pixel(game, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

static void	draw_minimap_background(t_game *game)
{
	int	x;
	int	y;
	int	max_x;
	int	max_y;
	int	tile_size;

	tile_size = (int)game->minimap.scale;
	max_x = game->minimap.x + (game->scene.map_width * tile_size);
	max_y = game->minimap.y + (game->scene.map_height * tile_size);
	if (max_x > game->minimap.x + game->minimap.size)
		max_x = game->minimap.x + game->minimap.size;
	if (max_y > game->minimap.y + game->minimap.size)
		max_y = game->minimap.y + game->minimap.size;
	y = game->minimap.y;
	while (y < max_y)
	{
		x = game->minimap.x;
		while (x < max_x)
		{
			if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
				put_pixel(game, x, y, 0x000000);
			x++;
		}
		y++;
	}
}

void	draw_minimap(t_game *game)
{
	draw_minimap_background(game);
	draw_minimap_tiles(game, '0', 0x404040);
	draw_minimap_tiles(game, '1', 0xFFFFFF);
	draw_minimap_player(game);
}
