/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by KIZUNA            #+#    #+#             */
/*   Updated: 2025/06/21 23:26:51 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	validate_arguments(int argc, char **argv)
{
	int		len;
	char	*filename;

	if (argc != 2)
	{
		ft_putendl_fd(ERR_USAGE, STDERR_FILENO);
		return (0);
	}
	filename = argv[1];
	len = ft_strlen(filename);
	if (len < 4 || ft_strncmp(filename + len - 4, ".cub", 4) != 0)
	{
		ft_putendl_fd(ERR_FILE_EXT, STDERR_FILENO);
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (!validate_arguments(argc, argv))
		return (1);
	ft_memset(&game, 0, sizeof(t_game));
	if (!init_game(&game, argv[1]))
	{
		cleanup_game(&game);
		return (1);
	}
	game_loop(&game);
	cleanup_game(&game);
	return (0);
}