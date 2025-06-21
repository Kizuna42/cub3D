/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by KIZUNA            #+#    #+#             */
/*   Updated: 2025/06/22 03:27:25 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	move_forward_backward(t_game *game, int forward)
{
	double	new_x;
	double	new_y;
	double	dir_factor;

	if (forward)
		dir_factor = MOVE_SPEED;
	else
		dir_factor = -MOVE_SPEED;
	new_x = game->scene.player.pos.x + game->scene.player.dir.x * dir_factor;
	new_y = game->scene.player.pos.y + game->scene.player.dir.y * dir_factor;
	if (!check_collision(game, new_x, game->scene.player.pos.y))
		game->scene.player.pos.x = new_x;
	if (!check_collision(game, game->scene.player.pos.x, new_y))
		game->scene.player.pos.y = new_y;
}

static void	move_left_right(t_game *game, int right)
{
	double	new_x;
	double	new_y;
	double	dir_factor;

	if (right)
		dir_factor = MOVE_SPEED;
	else
		dir_factor = -MOVE_SPEED;
	new_x = game->scene.player.pos.x + game->scene.player.plane.x * dir_factor;
	new_y = game->scene.player.pos.y + game->scene.player.plane.y * dir_factor;
	if (!check_collision(game, new_x, game->scene.player.pos.y))
		game->scene.player.pos.x = new_x;
	if (!check_collision(game, game->scene.player.pos.x, new_y))
		game->scene.player.pos.y = new_y;
}

static void	rotate_player(t_game *game, int clockwise)
{
	double	old_dir_x;
	double	old_plane_x;
	double	cos_angle;
	double	sin_angle;
	double	rot_speed;

	if (clockwise)
		rot_speed = ROT_SPEED;
	else
		rot_speed = -ROT_SPEED;
	cos_angle = cos(rot_speed);
	sin_angle = sin(rot_speed);
	old_dir_x = game->scene.player.dir.x;
	game->scene.player.dir.x = game->scene.player.dir.x * cos_angle
		- game->scene.player.dir.y * sin_angle;
	game->scene.player.dir.y = old_dir_x * sin_angle
		+ game->scene.player.dir.y * cos_angle;
	old_plane_x = game->scene.player.plane.x;
	game->scene.player.plane.x = game->scene.player.plane.x * cos_angle
		- game->scene.player.plane.y * sin_angle;
	game->scene.player.plane.y = old_plane_x * sin_angle
		+ game->scene.player.plane.y * cos_angle;
}

void	handle_movement(t_game *game)
{
	if (game->keys[KEY_W])
		move_forward_backward(game, 1);
	if (game->keys[KEY_S])
		move_forward_backward(game, 0);
	if (game->keys[KEY_A])
		move_left_right(game, 0);
	if (game->keys[KEY_D])
		move_left_right(game, 1);
	if (game->keys[KEY_LEFT])
		rotate_player(game, 0);
	if (game->keys[KEY_RIGHT])
		rotate_player(game, 1);
}
