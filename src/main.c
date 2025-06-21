/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 00:00:00 by kizuna            #+#    #+#             */
/*   Updated: 2025/06/21 19:08:56 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_putendl_fd("Error: Invalid number of arguments.", 2);
		ft_putendl_fd("Usage: ./cub3D <map_file.cub>", 2);
		return (1);
	}
	// TODO: Check for .cub extension
	// TODO: Initialize game data
	// TODO: Parse map file
	// TODO: Initialize MLX and window
	// TODO: Setup hooks and start game loop
	ft_putstr_fd("Argument received: ", 1);
	ft_putendl_fd(argv[1], 1);
	return (0);
} 