/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by KIZUNA            #+#    #+#             */
/*   Updated: 2025/06/21 23:29:58 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	parse_line(char *line, t_scene *scene, int *map_started)
{
	char	*trimmed;

	trimmed = ft_strtrim(line, " \t\n\r");
	if (!trimmed)
		return (0);
	if (ft_strlen(trimmed) == 0 || trimmed[0] == '\0')
	{
		free(trimmed);
		return (1);
	}
	if (!*map_started && (ft_strncmp(trimmed, "NO ", 3) == 0 || 
		ft_strncmp(trimmed, "SO ", 3) == 0 || ft_strncmp(trimmed, "WE ", 3) == 0 || 
		ft_strncmp(trimmed, "EA ", 3) == 0))
	{
		if (!parse_textures(trimmed, scene))
		{
			free(trimmed);
			return (0);
		}
	}
	else if (!*map_started && (ft_strncmp(trimmed, "F ", 2) == 0 || 
		ft_strncmp(trimmed, "C ", 2) == 0))
	{
		if (!parse_colors(trimmed, scene))
		{
			free(trimmed);
			return (0);
		}
	}
	else
		*map_started = 1;
	free(trimmed);
	return (1);
}

static int	read_file_content(int fd, t_scene *scene)
{
	char	*line;
	int		map_started;
	char	**lines;
	int		i;
	int		line_count;

	map_started = 0;
	line_count = 0;
	lines = safe_malloc(sizeof(char *) * 1000);
	while ((line = get_next_line(fd)) != NULL)
	{
		if (!parse_line(line, scene, &map_started))
		{
			free(line);
			return (0);
		}
		if (map_started)
			lines[line_count++] = line;
		else
			free(line);
	}
	lines[line_count] = NULL;
	if (line_count > 0)
	{
		if (!parse_map_from_lines(lines, scene))
			return (0);
	}
	i = 0;
	while (i < line_count)
		free(lines[i++]);
	free(lines);
	return (1);
}

int	parse_file(const char *filename, t_scene *scene)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		error_exit(ERR_FILE_OPEN);
		return (0);
	}
	if (!read_file_content(fd, scene))
	{
		close(fd);
		return (0);
	}
	close(fd);
	return (validate_map(scene));
} 