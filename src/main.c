/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by KIZUNA            #+#    #+#             */
/*   Updated: 2025/06/22 02:53:50 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	validate_args(int argc, char **argv)
{
	char	*extension;
	int		fd;

	if (argc != 2)
		return (error_msg("Usage: ./cub3D <map.cub>"), 0);
	if (!argv[1] || ft_strlen(argv[1]) < 5)
		return (error_msg("Invalid filename"), 0);
	extension = ft_strrchr(argv[1], '.');
	if (!extension || ft_strncmp(extension, ".cub", 4) != 0
		|| ft_strlen(extension) != 4)
		return (error_msg("Map file must have .cub extension"), 0);
	if (ft_strnstr(argv[1], "../", ft_strlen(argv[1])))
		return (error_msg("Path traversal not allowed"), 0);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (error_msg("Cannot open map file"), 0);
	close(fd);
	return (1);
}

static int	main_loop_hook(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	handle_movement(game);
	render_frame(game);
	return (0);
}

static int	close_window(t_game *game)
{
	cleanup_game(game);
	exit(0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (!validate_args(argc, argv))
		return (1);
	if (!init_game(&game, argv[1]))
		return (1);
	mlx_loop_hook(game.mlx, main_loop_hook, &game);
	mlx_hook(game.win, 17, 0, close_window, &game);
	mlx_loop(game.mlx);
	return (0);
}
