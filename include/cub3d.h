/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by KIZUNA            #+#    #+#             */
/*   Updated: 2025/06/21 23:56:48 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <string.h>
# include <errno.h>
# include <sys/time.h>
# include "../lib/libft/libft.h"

/* Window settings */
# define WIN_WIDTH 1024
# define WIN_HEIGHT 768
# define WIN_TITLE "cub3D"

/* Math constants */
# define PI 3.14159265359
# define TWO_PI 6.28318530718
# define HALF_PI 1.57079632679

/* Movement and rotation speed */
# define MOVE_SPEED 0.05
# define ROT_SPEED 0.03

/* Colors */
typedef struct s_color
{
	int	r;
	int	g;
	int	b;
	int	rgb;
}	t_color;

/* Vector for position and direction */
typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

/* Player information */
typedef struct s_player
{
	t_vector	pos;
	t_vector	dir;
	t_vector	plane;
	char		spawn_dir;
}	t_player;

/* Texture information */
typedef struct s_texture
{
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	char	*path;
}	t_texture;

/* Map information */
typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
}	t_map;

/* Scene configuration */
typedef struct s_scene
{
	t_texture	textures[4];
	t_color		floor_color;
	t_color		ceiling_color;
	t_map		map;
	t_player	player;
}	t_scene;

/* Main game structure */
typedef struct s_game
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	t_scene		scene;
	int			keys[256];
}	t_game;

/* Texture indices */
typedef enum e_texture_index
{
	NORTH = 0,
	SOUTH = 1,
	WEST = 2,
	EAST = 3
}	t_texture_index;

/* Error messages */
# define ERR_USAGE "Usage: ./cub3D <map.cub>"
# define ERR_FILE_EXT "Error\nFile must have .cub extension"
# define ERR_FILE_OPEN "Error\nCannot open file"
# define ERR_FILE_READ "Error\nCannot read file"
# define ERR_INVALID_MAP "Error\nInvalid map"
# define ERR_INVALID_TEXTURE "Error\nInvalid texture"
# define ERR_INVALID_COLOR "Error\nInvalid color"
# define ERR_MALLOC "Error\nMemory allocation failed"
# define ERR_MLX "Error\nMLX initialization failed"

/* Function prototypes */

/* Parser */
int		parse_file(const char *filename, t_scene *scene);
int		parse_line(char *line, t_scene *scene, int *map_started);
int		parse_textures(char *line, t_scene *scene);
int		parse_colors(char *line, t_scene *scene);
int		parse_map_from_lines(char **lines, t_scene *scene);
int		validate_map(t_scene *scene);
int		is_texture_line(char *trimmed);
int		is_color_line(char *trimmed);
char	*read_entire_file(int fd);
int		process_lines(char **all_lines, t_scene *scene, char **map_lines);
char	*get_next_line(int fd);
void	ft_free_split(char **split);

/* Game */
int		init_game(t_game *game, const char *filename);
void	cleanup_game(t_game *game);
int		game_loop(t_game *game);
void	handle_movement(t_game *game);

/* Rendering */
void	render_frame(t_game *game);
void	cast_rays(t_game *game);
void	draw_column(t_game *game, int x, double wall_dist, int side);
void	put_pixel(t_game *game, int x, int y, int color);

/* Utils */
void	error_exit(const char *message);
void	*safe_malloc(size_t size);
int		create_rgb(int r, int g, int b);
double	normalize_angle(double angle);

/* Platform-specific functions (implemented in platform/ directory) */
int		platform_init(t_game *game);
void	platform_cleanup(t_game *game);
int		platform_handle_keypress(int keycode, t_game *game);
int		platform_handle_keyrelease(int keycode, t_game *game);
int		platform_close_window(t_game *game);

#endif
