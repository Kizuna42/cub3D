/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by KIZUNA            #+#    #+#             */
/*   Updated: 2025/06/21 23:30:15 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	get_texture_index(char *identifier)
{
	if (ft_strncmp(identifier, "NO", 2) == 0)
		return (NORTH);
	else if (ft_strncmp(identifier, "SO", 2) == 0)
		return (SOUTH);
	else if (ft_strncmp(identifier, "WE", 2) == 0)
		return (WEST);
	else if (ft_strncmp(identifier, "EA", 2) == 0)
		return (EAST);
	return (-1);
}

static char	*extract_path(char *line)
{
	char	*path;
	char	*start;
	int		len;

	start = line + 2;
	while (*start == ' ' || *start == '\t')
		start++;
	len = ft_strlen(start);
	while (len > 0 && (start[len - 1] == ' ' || start[len - 1] == '\t' ||
		start[len - 1] == '\n' || start[len - 1] == '\r'))
		len--;
	path = ft_substr(start, 0, len);
	return (path);
}

int	parse_textures(char *line, t_scene *scene)
{
	int		index;
	char	*path;

	index = get_texture_index(line);
	if (index == -1)
		return (0);
	if (scene->textures[index].path != NULL)
		return (0);
	path = extract_path(line);
	if (!path)
		return (0);
	scene->textures[index].path = path;
	return (1);
} 