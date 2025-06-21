/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by KIZUNA            #+#    #+#             */
/*   Updated: 2025/06/21 23:59:30 by kizuna           ###   ########.fr       */
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

void	draw_column(t_game *game, int x, t_ray *ray)
{
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		tex_index;
	t_texture	*texture;
	double	wall_x;
	int		tex_x;
	int		y;

	line_height = (int)(WIN_HEIGHT / ray->perp_wall_dist);
	draw_start = -line_height / 2 + WIN_HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + WIN_HEIGHT / 2;
	if (draw_end >= WIN_HEIGHT)
		draw_end = WIN_HEIGHT - 1;
	tex_index = get_wall_texture_index(ray);
	texture = &game->scene.textures[tex_index];
	if (ray->side == 0)
		wall_x = game->scene.player.pos.y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		wall_x = game->scene.player.pos.x + ray->perp_wall_dist * ray->ray_dir_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)texture->width);
	if (ray->side == 0 && ray->ray_dir_x > 0)
		tex_x = texture->width - tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y < 0)
		tex_x = texture->width - tex_x - 1;
	y = draw_start;
	while (y <= draw_end)
	{
		int tex_y = (int)(((y - WIN_HEIGHT / 2 + line_height / 2) * texture->height) / line_height);
		int color = get_texture_color(texture, tex_x, tex_y);
		put_pixel(game, x, y, color);
		y++;
	}
} 