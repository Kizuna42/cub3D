/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by KIZUNA            #+#    #+#             */
/*   Updated: 2025/06/21 23:55:20 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include "../../include/keycodes.h"

static int	is_wall(t_game *game, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (map_x < 0 || map_x >= game->scene.map.width
		|| map_y < 0 || map_y >= game->scene.map.height)
		return (1);
	return (game->scene.map.grid[map_y][map_x] == '1');
}

static void	move_player(t_game *game, double move_x, double move_y)
{
	double	new_x;
	double	new_y;

	new_x = game->scene.player.pos.x + move_x;
	new_y = game->scene.player.pos.y + move_y;
	if (!is_wall(game, new_x, game->scene.player.pos.y))
		game->scene.player.pos.x = new_x;
	if (!is_wall(game, game->scene.player.pos.x, new_y))
		game->scene.player.pos.y = new_y;
}

static void	rotate_player(t_game *game, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->scene.player.dir.x;
	game->scene.player.dir.x = game->scene.player.dir.x * cos(angle)
		- game->scene.player.dir.y * sin(angle);
	game->scene.player.dir.y = old_dir_x * sin(angle)
		+ game->scene.player.dir.y * cos(angle);
	old_plane_x = game->scene.player.plane.x;
	game->scene.player.plane.x = game->scene.player.plane.x * cos(angle)
		- game->scene.player.plane.y * sin(angle);
	game->scene.player.plane.y = old_plane_x * sin(angle)
		+ game->scene.player.plane.y * cos(angle);
}

void	handle_movement(t_game *game)
{
	if (game->keys[KEY_W])
		move_player(game, game->scene.player.dir.x * MOVE_SPEED,
			game->scene.player.dir.y * MOVE_SPEED);
	if (game->keys[KEY_S])
		move_player(game, -game->scene.player.dir.x * MOVE_SPEED,
			-game->scene.player.dir.y * MOVE_SPEED);
	if (game->keys[KEY_A])
		move_player(game, -game->scene.player.plane.x * MOVE_SPEED,
			-game->scene.player.plane.y * MOVE_SPEED);
	if (game->keys[KEY_D])
		move_player(game, game->scene.player.plane.x * MOVE_SPEED,
			game->scene.player.plane.y * MOVE_SPEED);
	if (game->keys[KEY_LEFT])
		rotate_player(game, ROT_SPEED);
	if (game->keys[KEY_RIGHT])
		rotate_player(game, -ROT_SPEED);
} 