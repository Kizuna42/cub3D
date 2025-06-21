/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by KIZUNA            #+#    #+#             */
/*   Updated: 2025/06/21 23:56:57 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	put_pixel(t_game *game, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
	{
		dst = game->addr + (y * game->line_length + x * (game->bits_per_pixel / 8));
		*(unsigned int*)dst = color;
	}
}

static void	draw_floor_ceiling(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < WIN_HEIGHT / 2)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			put_pixel(game, x, y, game->scene.ceiling_color.rgb);
			x++;
		}
		y++;
	}
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			put_pixel(game, x, y, game->scene.floor_color.rgb);
			x++;
		}
		y++;
	}
}

void	render_frame(t_game *game)
{
	draw_floor_ceiling(game);
	cast_rays(game);
}

void	draw_column(t_game *game, int x, double wall_dist, int side)
{
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		color;
	int		y;

	line_height = (int)(WIN_HEIGHT / wall_dist);
	draw_start = -line_height / 2 + WIN_HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + WIN_HEIGHT / 2;
	if (draw_end >= WIN_HEIGHT)
		draw_end = WIN_HEIGHT - 1;
	if (side == 1)
		color = 0x808080;
	else
		color = 0xFFFFFF;
	y = draw_start;
	while (y <= draw_end)
	{
		put_pixel(game, x, y, color);
		y++;
	}
} 