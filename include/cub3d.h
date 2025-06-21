/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 00:00:00 by kizuna            #+#    #+#             */
/*   Updated: 2025/06/21 19:13:26 by kizuna           ###   ########.fr       */
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
// # include "parser.h" // Removed to break circular dependency

// --- Forward Declarations ---
struct s_game;

// --- Constants ---
# define SCREEN_WIDTH 1280
# define SCREEN_HEIGHT 720

// --- Structures ---

typedef struct s_texture
{
	char	*path;
	void	*img_ptr;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_texture;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
	int	trgb;
}	t_color;

typedef struct s_map
{
	char		**grid;
	int			width;
	int			height;
}	t_map;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_texture	north_tex;
	t_texture	south_tex;
	t_texture	west_tex;
	t_texture	east_tex;
	t_color		floor_color;
	t_color		ceiling_color;
	t_map		map;
	t_player	player;
	int			is_running;
}	t_game;

// --- Function Prototypes ---
// Moved to respective modules

#endif 