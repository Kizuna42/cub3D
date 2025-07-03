/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by KIZUNA            #+#    #+#             */
/*   Updated: 2025/07/01 19:29:28 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	cleanup_map(t_scene *scene)
{
	int	i;

	if (!scene->map)
		return ;
	i = 0;
	while (i < scene->map_height)
	{
		if (scene->map[i])
			free(scene->map[i]);
		i++;
	}
	free(scene->map);
	scene->map = NULL;
}

void	cleanup_texture_paths(t_scene *scene)
{
	if (scene->north_texture)
	{
		free(scene->north_texture);
		scene->north_texture = NULL;
	}
	if (scene->south_texture)
	{
		free(scene->south_texture);
		scene->south_texture = NULL;
	}
	if (scene->west_texture)
	{
		free(scene->west_texture);
		scene->west_texture = NULL;
	}
	if (scene->east_texture)
	{
		free(scene->east_texture);
		scene->east_texture = NULL;
	}
}

void	cleanup_game(t_game *game)
{
	if (!game)
		return ;
	cleanup_textures(game);
	cleanup_texture_paths(&game->scene);
	cleanup_map(&game->scene);
	if (game->img)
		mlx_destroy_image(game->mlx, game->img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
		mlx_destroy_display(game->mlx);
	free(game->mlx);
}
