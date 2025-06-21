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
#include "../../lib/minilibx_opengl_20191021/mlx.h"

/* macOS specific key codes */
#define MAC_KEY_W 13
#define MAC_KEY_A 0
#define MAC_KEY_S 1
#define MAC_KEY_D 2
#define MAC_KEY_LEFT 123
#define MAC_KEY_RIGHT 124
#define MAC_KEY_ESC 53

static int	map_keycode_to_abstract(int keycode)
{
	if (keycode == MAC_KEY_W)
		return (KEY_W);
	else if (keycode == MAC_KEY_A)
		return (KEY_A);
	else if (keycode == MAC_KEY_S)
		return (KEY_S);
	else if (keycode == MAC_KEY_D)
		return (KEY_D);
	else if (keycode == MAC_KEY_LEFT)
		return (KEY_LEFT);
	else if (keycode == MAC_KEY_RIGHT)
		return (KEY_RIGHT);
	else if (keycode == MAC_KEY_ESC)
		return (KEY_ESC);
	return (-1);
}

int	platform_init(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (0);
	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, WIN_TITLE);
	if (!game->win)
		return (0);
	game->img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!game->img)
		return (0);
	game->addr = mlx_get_data_addr(game->img, &game->bits_per_pixel,
			&game->line_length, &game->endian);
	mlx_hook(game->win, 2, 1L << 0, platform_handle_keypress, game);
	mlx_hook(game->win, 3, 1L << 1, platform_handle_keyrelease, game);
	mlx_hook(game->win, 17, 1L << 17, platform_close_window, game);
	return (1);
}

void	platform_cleanup(t_game *game)
{
	if (game->img)
		mlx_destroy_image(game->mlx, game->img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
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
