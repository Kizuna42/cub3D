/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 10:00:00 by kizuna            #+#    #+#             */
/*   Updated: 2025/06/21 22:37:36 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_game_data(t_game *game)
{
	game->mlx = NULL;
	game->win = NULL;
	game->textures.north = NULL;
	game->textures.south = NULL;
	game->textures.west = NULL;
	game->textures.east = NULL;
	game->textures.floor = -1;
	game->textures.ceiling = -1;
	game->map.grid = NULL;
	game->map.width = 0;
	game->map.height = 0;
	game->player.pos_x = 0;
	game->player.pos_y = 0;
	game->player.direction = '\0';
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		printf("Error\n%s\n", ERR_ARGC);
		return (1);
	}
	init_game_data(&game);
	printf("Parsing seems successful (WIP).\n");
	return (0);
}
