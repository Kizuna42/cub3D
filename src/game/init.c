/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by KIZUNA            #+#    #+#             */
/*   Updated: 2025/06/22 03:27:22 by kizuna           ###   ########.fr       */
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
	int	i;

	i = 0;
	while (i < 256)
	{
		game->keys[i] = KEY_RELEASED;
		i++;
	}
	game->mlx = NULL;
	game->win = NULL;
	game->img = NULL;
	if (!platform_init(game))
		return (error_msg("Platform initialization failed"), 0);
	if (!load_all_textures(game))
	{
		platform_cleanup(game);
		return (0);
	}
	return (1);
}

int	init_game(t_game *game, const char *filename)
{
	ft_memset(&game->scene, 0, sizeof(t_scene));
	game->scene.floor_color = -1;
	game->scene.ceiling_color = -1;
	game->scene.has_floor = 0;
	game->scene.has_ceiling = 0;
	if (!parse_file(filename, &game->scene))
		return (0);
	init_player_direction(&game->scene.player);
	init_minimap(game);
	if (!init_mlx(game))
	{
		cleanup_texture_paths(&game->scene);
		cleanup_map(&game->scene);
		return (0);
	}
	return (1);
}
