/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   platform_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 00:00:00 by kizuna            #+#    #+#             */
/*   Updated: 2025/07/03 20:35:00 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include "../../include/keycodes.h"
#include <X11/keysym.h>

static int	init_mlx_components(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (0);
	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, WIN_TITLE);
	if (!game->win)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		game->mlx = NULL;
		return (0);
	}
	return (1);
}

static int	init_image_and_hooks(t_game *game)
{
	game->img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!game->img)
	{
		mlx_destroy_window(game->mlx, game->win);
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		game->mlx = NULL;
		game->win = NULL;
		return (0);
	}
	game->addr = mlx_get_data_addr(game->img, &game->bits_per_pixel,
			&game->line_length, &game->endian);
	mlx_hook(game->win, 2, 1L << 0, platform_handle_keypress, game);
	mlx_hook(game->win, 3, 1L << 1, platform_handle_keyrelease, game);
	mlx_hook(game->win, 17, 1L << 17, platform_close_window, game);
	return (1);
}

int	platform_init(t_game *game)
{
	if (!init_mlx_components(game))
		return (0);
	return (init_image_and_hooks(game));
}
