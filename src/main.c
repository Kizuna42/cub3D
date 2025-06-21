/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 00:00:00 by kizuna            #+#    #+#             */
/*   Updated: 2025/06/21 19:11:03 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_game_struct(t_game *game)
{
	ft_memset(game, 0, sizeof(t_game));
	// Further initializations can be added here
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		ft_putendl_fd("Error: Invalid number of arguments.", 2);
		ft_putendl_fd("Usage: ./cub3D <map_file.cub>", 2);
		return (1);
	}
	init_game_struct(&game);
	if (!parse_map_file(&game, argv[1]))
	{
		// TODO: Add proper resource cleanup here
		ft_putendl_fd("Error: Failed to parse map file.", 2);
		return (1);
	}
	ft_putendl_fd("Map file parsed successfully.", 1);
	// TODO: Initialize MLX and window
	// TODO: Setup hooks and start game loop
	return (0);
} 