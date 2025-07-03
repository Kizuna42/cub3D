/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by KIZUNA            #+#    #+#             */
/*   Updated: 2025/07/01 23:44:40 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	validate_texture_extension(char *path)
{
	char	*extension;

	if (!path)
		return (0);
	extension = ft_strrchr(path, '.');
	if (!extension || ft_strncmp(extension, ".xpm", 4) != 0)
		return (error_msg("Texture file must have .xpm extension"), 0);
	return (1);
}

int	load_texture(t_game *game, t_texture *texture, char *path)
{
	if (!validate_texture_extension(path))
		return (0);
	texture->img = mlx_xpm_file_to_image(game->mlx, path,
			&texture->width, &texture->height);
	if (!texture->img)
		return (error_msg("Failed to load texture file"), 0);
	texture->addr = mlx_get_data_addr(texture->img,
			&texture->bits_per_pixel, &texture->line_length, &texture->endian);
	if (!texture->addr)
		return (error_msg("Failed to get texture data"), 0);
	return (1);
}

static int	init_texture_array(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		game->scene.textures[i].img = NULL;
		i++;
	}
	return (1);
}

static int	load_required_textures(t_game *game)
{
	if (!load_texture(game, &game->scene.textures[0],
			game->scene.north_texture)
		|| !load_texture(game, &game->scene.textures[1],
			game->scene.south_texture)
		|| !load_texture(game, &game->scene.textures[2],
			game->scene.west_texture)
		|| !load_texture(game, &game->scene.textures[3],
			game->scene.east_texture))
	{
		cleanup_textures(game);
		return (0);
	}
	return (1);
}

int	load_all_textures(t_game *game)
{
	init_texture_array(game);
	return (load_required_textures(game));
}
