/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by KIZUNA            #+#    #+#             */
/*   Updated: 2025/06/22 03:17:15 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	convert_color_endian(int color, int endian)
{
	int	r;
	int	g;
	int	b;

	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	if (endian == 0)
		return ((r << 16) | (g << 8) | b);
	else
		return ((b << 16) | (g << 8) | r);
}

void	put_pixel(t_game *game, int x, int y, int color)
{
	char	*dst;
	int		final_color;

	if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
	{
		final_color = convert_color_endian(color, game->endian);
		dst = game->addr + (y * game->line_length
				+ x * (game->bits_per_pixel / 8));
		*(unsigned int *)dst = final_color;
	}
}

void	draw_floor_ceiling(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < WINDOW_HEIGHT / 2)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			put_pixel(game, x, y, game->scene.ceiling_color);
			x++;
		}
		y++;
	}
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			put_pixel(game, x, y, game->scene.floor_color);
			x++;
		}
		y++;
	}
}

static void	draw_wall_stripe(t_game *game, t_ray *ray, int x)
{
	int	tex_x;

	tex_x = get_texture_x(ray,
			&game->scene.textures[get_wall_texture_index(ray)],
			&game->scene.player);
	draw_texture_column(game, ray, x, tex_x);
}

void	render_frame(t_game *game)
{
	int		x;
	t_ray	ray;

	mlx_clear_window(game->mlx, game->win);
	draw_floor_ceiling(game);
	x = 0;
	while (x < WINDOW_WIDTH)
	{
		cast_ray(game, &ray, x);
		draw_wall_stripe(game, &ray, x);
		x++;
	}
	draw_minimap(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}
