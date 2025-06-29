/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by KIZUNA            #+#    #+#             */
/*   Updated: 2025/06/22 00:53:10 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	process_config_line(char *line, t_scene *scene)
{
	char	*trimmed;
	int		result;

	trimmed = ft_strtrim(line, " \t\n\r");
	if (!trimmed)
		return (0);
	if (ft_strlen(trimmed) == 0)
		return (free(trimmed), 1);
	result = 1;
	if (is_texture_line(trimmed))
		result = parse_texture_line(trimmed, scene);
	else if (is_color_line(trimmed))
		result = parse_color_line(trimmed, scene);
	free(trimmed);
	return (result);
}

int	parse_file(const char *filename, t_scene *scene)
{
	int		fd;
	char	*file_content;
	char	**lines;
	int		map_start;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (error_msg("Cannot open file"), 0);
	file_content = read_entire_file(fd);
	close(fd);
	if (!file_content)
		return (error_msg("Cannot read file"), 0);
	lines = ft_split(file_content, '\n');
	free(file_content);
	if (!lines)
		return (error_msg("Cannot split file content"), 0);
	if (!process_lines(lines, scene, &map_start))
		return (ft_free_split(lines), 0);
	if (map_start != -1)
	{
		if (!parse_map_data(lines, scene, map_start))
			return (ft_free_split(lines), 0);
	}
	ft_free_split(lines);
	return (validate_map(scene));
}
