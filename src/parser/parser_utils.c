/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by KIZUNA            #+#    #+#             */
/*   Updated: 2025/06/21 23:50:23 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	is_texture_line(char *trimmed)
{
	return (!ft_strncmp(trimmed, "NO ", 3) || !ft_strncmp(trimmed, "SO ", 3)
		|| !ft_strncmp(trimmed, "WE ", 3) || !ft_strncmp(trimmed, "EA ", 3));
}

int	is_color_line(char *trimmed)
{
	return (!ft_strncmp(trimmed, "F ", 2) || !ft_strncmp(trimmed, "C ", 2));
}

char	*read_entire_file(int fd)
{
	char	*content;
	char	*buffer;
	int		bytes_read;
	char	*temp;

	content = safe_malloc(1024);
	content[0] = '\0';
	buffer = safe_malloc(1024);
	bytes_read = read(fd, buffer, 1023);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		temp = ft_strjoin(content, buffer);
		free(content);
		content = temp;
		bytes_read = read(fd, buffer, 1023);
	}
	free(buffer);
	return (content);
}

int	process_lines(char **all_lines, t_scene *scene, char **map_lines)
{
	int	i;
	int	map_started;
	int	map_line_count;

	i = 0;
	map_started = 0;
	map_line_count = 0;
	while (all_lines[i])
	{
		if (!parse_line(all_lines[i], scene, &map_started))
		{
			ft_free_split(all_lines);
			free(map_lines);
			return (0);
		}
		if (map_started)
			map_lines[map_line_count++] = ft_strdup(all_lines[i]);
		i++;
	}
	map_lines[map_line_count] = NULL;
	return (map_line_count);
} 