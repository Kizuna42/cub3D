/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 03:45:00 by kizuna            #+#    #+#             */
/*   Updated: 2025/06/22 03:40:01 by kizuna           ###   ########.fr       */
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

void	draw_minimap_square(t_game *game, int x, int y, int size)
{
	(void)size;
	draw_minimap_square_color(game, x, y, 0xFFFFFF);
}

static void	draw_minimap_background(t_game *game)
{
	int	x;
	int	y;
	int	max_x;
	int	max_y;

	max_x = game->minimap.x + (game->scene.map_width
			* (int)game->minimap.scale);
	max_y = game->minimap.y + (game->scene.map_height
			* (int)game->minimap.scale);
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

static void	draw_minimap_floor(t_game *game)
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
			if (game->scene.map[map_y][map_x] == '0')
			{
				pixel_x = game->minimap.x + (map_x * tile_size);
				pixel_y = game->minimap.y + (map_y * tile_size);
				draw_minimap_square_color(game, pixel_x, pixel_y, 0x404040);
			}
			map_x++;
		}
		map_y++;
	}
}

void	draw_minimap(t_game *game)
{
	draw_minimap_background(game);
	draw_minimap_floor(game);
	draw_minimap_walls(game);
	draw_minimap_player(game);
}
