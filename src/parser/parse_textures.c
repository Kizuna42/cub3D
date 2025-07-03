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

static int	is_directory(char *path)
{
	int	len;

	len = ft_strlen(path);
	if (len == 0)
		return (1);
	return (path[len - 1] == '/');
}

static int	validate_texture_file(char *path)
{
	char	*extension;
	int		fd;

	if (!path || ft_strlen(path) == 0)
		return (error_msg("Empty texture path"), 0);
	if (is_directory(path))
		return (error_msg("Texture path cannot be a directory"), 0);
	extension = ft_strrchr(path, '.');
	if (!extension || ft_strncmp(extension, ".xpm", 5) != 0
		|| extension[4] != '\0')
		return (error_msg("Texture must have .xpm extension"), 0);
	if (ft_strnstr(path, "../", ft_strlen(path)))
		return (error_msg("Path traversal not allowed"), 0);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (error_msg("Texture file not found or not readable"), 0);
	close(fd);
	return (1);
}

static int	set_texture_path(char **target, char *path)
{
	if (*target)
	{
		free(*target);
		*target = NULL;
		error_msg("Duplicate texture definition");
		return (0);
	}
	if (!validate_texture_file(path))
		return (0);
	*target = ft_strdup(path);
	if (!*target)
		return (error_msg("Memory allocation failed"), 0);
	return (1);
}

static int	parse_single_texture(char *line, char **target, int prefix_len)
{
	char	*path;
	int		result;

	path = ft_strtrim(line + prefix_len, " \t");
	if (!path)
		return (error_msg("Failed to parse texture path"), 0);
	result = set_texture_path(target, path);
	free(path);
	return (result);
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
