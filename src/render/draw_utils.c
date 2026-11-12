/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by KIZUNA            #+#    #+#             */
/*   Updated: 2025/06/22 00:32:01 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	init_texture_params(t_ray *ray, t_texture *texture,
		double *step, double *tex_pos)
{
	*step = 1.0 * texture->height / ray->line_height;
	*tex_pos = (ray->draw_start - WINDOW_HEIGHT / 2 + ray->line_height / 2)
		* (*step);
}

void	draw_texture_column(t_game *game, t_ray *ray, int x, int tex_x)
{
	int			y;
	int			tex_y;
	double		step;
	double		tex_pos;
	t_texture	*texture;

	texture = &game->scene.textures[get_wall_texture_index(ray)];
	init_texture_params(ray, texture, &step, &tex_pos);
	y = ray->draw_start;
	while (y <= ray->draw_end)
	{
		tex_y = (int)tex_pos;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= texture->height)
			tex_y = texture->height - 1;
		tex_pos += step;
		put_pixel(game, x, y, get_texture_color(texture, tex_x, tex_y));
		y++;
	}
}
