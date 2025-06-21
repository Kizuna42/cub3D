/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by KIZUNA            #+#    #+#             */
/*   Updated: 2025/06/21 23:51:54 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	parse_line(char *line, t_scene *scene, int *map_started)
{
	char	*trimmed;

	trimmed = ft_strtrim(line, " \t\n\r");
	if (!trimmed)
		return (0);
	if (ft_strlen(trimmed) == 0)
		return (free(trimmed), 1);
	if (!*map_started && is_texture_line(trimmed))
	{
		if (!parse_textures(trimmed, scene))
			return (free(trimmed), 0);
	}
	else if (!*map_started && is_color_line(trimmed))
	{
		if (!parse_colors(trimmed, scene))
			return (free(trimmed), 0);
	}
	else if (ft_strlen(trimmed) > 0)
		*map_started = 1;
	return (free(trimmed), 1);
}

static int	read_file_content(int fd, t_scene *scene)
{
	char	*file_content;
	char	**all_lines;
	char	**map_lines;
	int		map_line_count;

	file_content = read_entire_file(fd);
	if (!file_content)
		return (0);
	all_lines = ft_split(file_content, '\n');
	free(file_content);
	if (!all_lines)
		return (0);
	map_lines = safe_malloc(sizeof(char *) * 1000);
	map_line_count = process_lines(all_lines, scene, map_lines);
	ft_free_split(all_lines);
	if (map_line_count > 0)
	{
		if (!parse_map_from_lines(map_lines, scene))
			return (ft_free_split(map_lines), 0);
	}
	return (ft_free_split(map_lines), 1);
}

int	parse_file(const char *filename, t_scene *scene)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_putendl_fd(ERR_FILE_OPEN, STDERR_FILENO);
		return (0);
	}
	if (!read_file_content(fd, scene))
		return (close(fd), 0);
	close(fd);
	return (validate_map(scene));
} 