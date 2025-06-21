/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by KIZUNA            #+#    #+#             */
/*   Updated: 2025/06/22 00:49:12 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	set_north_south_direction(t_player *player)
{
	if (player->spawn_dir == 'N')
	{
		player->dir.x = 0;
		player->dir.y = -1;
		player->plane.x = 0.66;
		player->plane.y = 0;
	}
	else if (player->spawn_dir == 'S')
	{
		player->dir.x = 0;
		player->dir.y = 1;
		player->plane.x = -0.66;
		player->plane.y = 0;
	}
}

static void	set_east_west_direction(t_player *player)
{
	if (player->spawn_dir == 'E')
	{
		player->dir.x = 1;
		player->dir.y = 0;
		player->plane.x = 0;
		player->plane.y = 0.66;
	}
	else if (player->spawn_dir == 'W')
	{
		player->dir.x = -1;
		player->dir.y = 0;
		player->plane.x = 0;
		player->plane.y = -0.66;
	}
}

static void	init_player_direction(t_player *player)
{
	set_north_south_direction(player);
	set_east_west_direction(player);
}

static int	init_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (error_msg("MLX initialization failed"), 0);
	game->win = mlx_new_window(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT,
			WIN_TITLE);
	if (!game->win)
		return (error_msg("Window creation failed"), 0);
	game->img = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!game->img)
		return (error_msg("Image creation failed"), 0);
	game->addr = mlx_get_data_addr(game->img, &game->bits_per_pixel,
			&game->line_length, &game->endian);
	if (!game->addr)
		return (error_msg("Failed to get image data"), 0);
	return (1);
}

int	init_game(t_game *game, const char *filename)
{
	ft_memset(&game->scene, 0, sizeof(t_scene));
	if (!parse_file(filename, &game->scene))
		return (0);
	init_player_direction(&game->scene.player);
	if (!init_mlx(game))
		return (0);
	if (!load_all_textures(game))
		return (0);
	return (1);
}
