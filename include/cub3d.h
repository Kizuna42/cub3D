/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 00:00:00 by kizuna            #+#    #+#             */
/*   Updated: 2025/06/21 19:05:00 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// --- Standard Libraries ---
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <math.h>

// --- Libft ---
# include "libft.h"

// --- MiniLibX ---
// This header will be included via CFLAGS in Makefile
// # include "mlx.h" 

// --- Project Headers ---
// Will be added as the project grows
// # include "parser.h"

// --- Constants ---
# define SCREEN_WIDTH 1280
# define SCREEN_HEIGHT 720

// --- Structures ---

// Example of a game data structure
typedef struct s_game
{
	void	*mlx;
	void	*win;
	// Will be expanded with map data, player data, textures, etc.
}	t_game;

#endif 