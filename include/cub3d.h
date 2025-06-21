/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 00:00:00 by kizuna            #+#    #+#             */
/*   Updated: 2025/06/21 22:04:42 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <math.h>

# include "libft.h"
# include "mlx.h"

// Forward Declarations & Structures
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

void	free_game_resources(t_game *game);

// --- Function Prototypes ---

// Parser
int		parse_map_file(t_game *game, const char *filename);
int		parse_texture(t_texture *texture, char *path);
int		parse_color(t_color *color, char *rgb_str);
int		convert_list_to_grid(t_game *game, t_list *map_lines);
int		dispatch_config(t_game *game, char **tokens);
int		parse_config_line(t_game *game, const char *line);

#endif 