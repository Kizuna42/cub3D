#ifndef CUB3D_H
# define CUB3D_H

# include "../lib/libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

// This header will be dynamically included by the Makefile based on the OS
# ifdef __APPLE__
#  include "mlx.h"
# else
#  include "mlx.h"
# endif

// Error Messages
# define ERR_ARGC "Invalid number of arguments."
# define ERR_FILE_EXT "Invalid file extension. Must be .cub"
# define ERR_FILE_OPEN "Could not open file."
# define ERR_PARSE_ID "Invalid identifier in file."
# define ERR_PARSE_COLOR "Invalid color format."
# define ERR_PARSE_TEX "Invalid texture path."
# define ERR_MAP_WALL "Map is not surrounded by walls."
# define ERR_MAP_PLAYER "Invalid player position."
# define ERR_MALLOC "Memory allocation failed."

typedef struct s_texture
{
	char			*north;
	char			*south;
	char			*west;
	char			*east;
	int				floor;
	int				ceiling;
}					t_texture;

typedef struct s_map
{
	char			**grid;
	int				width;
	int				height;
}					t_map;

typedef struct s_player
{
	double			pos_x;
	double			pos_y;
	char			direction;
}					t_player;

typedef struct s_game
{
	void			*mlx;
	void			*win;
	t_texture		textures;
	t_map			map;
	t_player		player;
}					t_game;

#endif
