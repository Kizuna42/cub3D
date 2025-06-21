/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by KIZUNA            #+#    #+#             */
/*   Updated: 2025/06/22 00:31:22 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	is_texture_line(char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0)
		return (1);
	return (0);
}

static int	is_color_line(char *line)
{
	if (ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0)
		return (1);
	return (0);
}

static int	is_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != ' '
			&& line[i] != 'N' && line[i] != 'S' && line[i] != 'E'
			&& line[i] != 'W')
			return (0);
		i++;
	}
	return (1);
}

static int	process_config_line(char *line, t_scene *scene)
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
	int		i;
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
	i = 0;
	map_start = -1;
	while (lines[i])
	{
		if (map_start == -1 && is_map_line(lines[i]))
			map_start = i;
		else if (map_start == -1)
		{
			if (!process_config_line(lines[i], scene))
				return (ft_free_split(lines), 0);
		}
		i++;
	}
	if (map_start != -1)
	{
		if (!parse_map_data(lines, scene, map_start))
			return (ft_free_split(lines), 0);
	}
	ft_free_split(lines);
	return (validate_map(scene));
}
