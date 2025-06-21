/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 00:00:00 by kizuna            #+#    #+#             */
/*   Updated: 2025/06/21 22:04:09 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_game_struct(t_game *game)
{
	game->mlx = NULL;
	game->win = NULL;
	game->map.grid = NULL;
	game->map.height = 0;
	game->map.width = 0;
	game->north_tex.path = NULL;
	game->south_tex.path = NULL;
	game->west_tex.path = NULL;
	game->east_tex.path = NULL;
	game->floor_color.trgb = 0;
	game->ceiling_color.trgb = 0;
	game->player.pos_x = -1;
	game->player.pos_y = -1;
	game->player.dir_x = 0;
	game->player.dir_y = 0;
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		printf("Error\nUsage: ./cub3D <map_file.cub>\n");
		return (1);
	}
	init_game_struct(&game);
	if (!parse_map_file(&game, argv[1]))
		return (1);
	printf("Game validated and ready to launch!\n");
	return (0);
} 