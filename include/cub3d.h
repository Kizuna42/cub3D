/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by KIZUNA            #+#    #+#             */
/*   Updated: 2025/06/22 00:39:07 by kizuna           ###   ########.fr       */
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
# include "../lib/minilibx_opengl_20191021/mlx.h"
# include "keycodes.h"

/* Window settings */
# define WINDOW_WIDTH 1024
# define WINDOW_HEIGHT 768
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
}	t_texture;

/* Ray structure for raycasting */
typedef struct s_ray
{
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	side_dist_x;
	double	side_dist_y;
	int		step_x;
	int		step_y;
	int		side;
	double	perp_wall_dist;
	int		line_height;
	int		draw_start;
	int		draw_end;
}	t_ray;

/* Scene configuration */
typedef struct s_scene
{
	t_texture		textures[4];
	unsigned int	floor_color;
	unsigned int	ceiling_color;
	char			**map;
	int				map_width;
	int				map_height;
	t_player		player;
	char			*north_texture;
	char			*south_texture;
	char			*west_texture;
	char			*east_texture;
	int				has_floor;
	int				has_ceiling;
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

/* Function prototypes */

/* Parser */
int		parse_file(const char *filename, t_scene *scene);
int		parse_color_line(char *line, t_scene *scene);
int		parse_texture_line(char *line, t_scene *scene);
int		parse_map_data(char **lines, t_scene *scene, int start_line);
int		validate_map(t_scene *scene);
char	*read_entire_file(int fd);
void	ft_free_split(char **split);

/* Game */
int		init_game(t_game *game, const char *filename);
void	cleanup_game(t_game *game);
void	handle_movement(t_game *game);
void	set_north_south_direction(t_player *player);
void	set_east_west_direction(t_player *player);

/* Rendering */
void	render_frame(t_game *game);
void	cast_ray(t_game *game, t_ray *ray, int x);
void	draw_floor_ceiling(t_game *game);
void	put_pixel(t_game *game, int x, int y, int color);
void	draw_texture_column(t_game *game, t_ray *ray, int x, int tex_x);

/* Textures */
int				load_texture(t_game *game, t_texture *texture, char *path);
int				load_all_textures(t_game *game);
unsigned int	get_texture_color(t_texture *texture, int x, int y);
int				get_wall_texture_index(t_ray *ray);
int				get_texture_x(t_ray *ray, t_texture *texture);
void			cleanup_textures(t_game *game);

/* Utils */
void	error_msg(char *msg);
void	cleanup_and_exit(t_game *game, char *msg);
double	ft_abs(double x);
double	ft_sqrt(double x);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_isspace(int c);

#endif
