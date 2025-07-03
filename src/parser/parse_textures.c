/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by KIZUNA            #+#    #+#             */
/*   Updated: 2025/06/22 00:49:12 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	set_texture_path(char **target, char *path)
{
	if (*target)
	{
		free(*target);
		*target = NULL;
		error_msg("Duplicate texture definition");
		return (0);
	}
	*target = ft_strdup(path);
	if (!*target)
		return (error_msg("Memory allocation failed"), 0);
	return (1);
}

static int	parse_single_texture(char *line, char **target, int prefix_len)
{
	char	*path;

	path = ft_strtrim(line + prefix_len, " \t");
	if (!path)
		return (error_msg("Failed to parse texture path"), 0);
	if (!set_texture_path(target, path))
		return (free(path), 0);
	free(path);
	return (1);
}

int	parse_texture_line(char *line, t_scene *scene)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (parse_single_texture(line, &scene->north_texture, 3));
	else if (ft_strncmp(line, "SO ", 3) == 0)
		return (parse_single_texture(line, &scene->south_texture, 3));
	else if (ft_strncmp(line, "WE ", 3) == 0)
		return (parse_single_texture(line, &scene->west_texture, 3));
	else if (ft_strncmp(line, "EA ", 3) == 0)
		return (parse_single_texture(line, &scene->east_texture, 3));
	return (1);
}
