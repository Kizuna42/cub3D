/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by KIZUNA            #+#    #+#             */
/*   Updated: 2025/06/21 23:55:08 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include "../../lib/minilibx_opengl_20191021/mlx.h"

static void	init_player_direction(t_player *player)
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
	else if (player->spawn_dir == 'E')
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

int	init_game(t_game *game, const char *filename)
{
	ft_memset(&game->scene, 0, sizeof(t_scene));
	if (!parse_file(filename, &game->scene))
		return (0);
	init_player_direction(&game->scene.player);
	if (!platform_init(game))
		return (0);
	return (1);
}

static int	game_loop_hook(t_game *game)
{
	handle_movement(game);
	render_frame(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}

int	game_loop(t_game *game)
{
	mlx_loop_hook(game->mlx, (int (*)(void *))game_loop_hook, game);
	mlx_loop(game->mlx);
	return (0);
} 