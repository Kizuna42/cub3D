/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   platform_hooks.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by KIZUNA            #+#    #+#             */
/*   Updated: 2025/06/22 00:55:00 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include "../../include/keycodes.h"
#include <X11/keysym.h>

/* Linux specific key codes */
#define LINUX_KEY_W XK_w
#define LINUX_KEY_A XK_a
#define LINUX_KEY_S XK_s
#define LINUX_KEY_D XK_d
#define LINUX_KEY_LEFT XK_Left
#define LINUX_KEY_RIGHT XK_Right
#define LINUX_KEY_ESC XK_Escape

static int	map_keycode_to_abstract(int keycode)
{
	if (keycode == LINUX_KEY_W)
		return (KEY_W);
	else if (keycode == LINUX_KEY_A)
		return (KEY_A);
	else if (keycode == LINUX_KEY_S)
		return (KEY_S);
	else if (keycode == LINUX_KEY_D)
		return (KEY_D);
	else if (keycode == LINUX_KEY_LEFT)
		return (KEY_LEFT);
	else if (keycode == LINUX_KEY_RIGHT)
		return (KEY_RIGHT);
	else if (keycode == LINUX_KEY_ESC)
		return (KEY_ESC);
	return (-1);
}

void	platform_cleanup(t_game *game)
{
	if (game->img)
		mlx_destroy_image(game->mlx, game->img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
}

int	platform_handle_keypress(int keycode, t_game *game)
{
	int	abstract_key;

	abstract_key = map_keycode_to_abstract(keycode);
	if (abstract_key >= 0 && abstract_key < 256)
		game->keys[abstract_key] = KEY_PRESSED;
	if (abstract_key == KEY_ESC)
		platform_close_window(game);
	return (0);
}

int	platform_handle_keyrelease(int keycode, t_game *game)
{
	int	abstract_key;

	abstract_key = map_keycode_to_abstract(keycode);
	if (abstract_key >= 0 && abstract_key < 256)
		game->keys[abstract_key] = KEY_RELEASED;
	return (0);
}
