/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by KIZUNA            #+#    #+#             */
/*   Updated: 2025/06/22 00:31:06 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	set_texture_path(char **target, char *path)
{
	if (*target)
		return (error_msg("Duplicate texture definition"), 0);
	*target = ft_strdup(path);
	if (!*target)
		return (error_msg("Memory allocation failed"), 0);
	return (1);
}

int	parse_texture_line(char *line, t_scene *scene)
{
	char	*path;

	if (ft_strncmp(line, "NO ", 3) == 0)
	{
		path = ft_strtrim(line + 3, " \t");
		if (!path)
			return (error_msg("Failed to parse texture path"), 0);
		if (!set_texture_path(&scene->north_texture, path))
			return (free(path), 0);
		free(path);
	}
	else if (ft_strncmp(line, "SO ", 3) == 0)
	{
		path = ft_strtrim(line + 3, " \t");
		if (!path)
			return (error_msg("Failed to parse texture path"), 0);
		if (!set_texture_path(&scene->south_texture, path))
			return (free(path), 0);
		free(path);
	}
	else if (ft_strncmp(line, "WE ", 3) == 0)
	{
		path = ft_strtrim(line + 3, " \t");
		if (!path)
			return (error_msg("Failed to parse texture path"), 0);
		if (!set_texture_path(&scene->west_texture, path))
			return (free(path), 0);
		free(path);
	}
	else if (ft_strncmp(line, "EA ", 3) == 0)
	{
		path = ft_strtrim(line + 3, " \t");
		if (!path)
			return (error_msg("Failed to parse texture path"), 0);
		if (!set_texture_path(&scene->east_texture, path))
			return (free(path), 0);
		free(path);
	}
	return (1);
}
