/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by KIZUNA            #+#    #+#             */
/*   Updated: 2025/06/22 00:51:44 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	is_texture_line(char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0)
		return (1);
	return (0);
}

int	is_color_line(char *line)
{
	if (ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0)
		return (1);
	return (0);
}

int	is_map_line(char *line)
{
	int	i;
	int	has_map_char;

	i = 0;
	has_map_char = 0;
	while (line[i])
	{
		if (line[i] == '0' || line[i] == '1' || line[i] == 'N'
			|| line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
			has_map_char = 1;
		else if (line[i] != ' ' && line[i] != '\t')
			return (0);
		i++;
	}
	return (has_map_char);
}

int	validate_post_map_lines(char **lines, int map_start, int map_count)
{
	int		i;
	char	*trimmed;

	i = map_start + map_count;
	while (lines[i])
	{
		trimmed = ft_strtrim(lines[i], " \t\n\r");
		if (!trimmed)
			return (error_msg("Memory allocation failed"), 0);
		if (ft_strlen(trimmed) > 0)
		{
			free(trimmed);
			return (error_msg("Invalid data after map"), 0);
		}
		free(trimmed);
		i++;
	}
	return (1);
}

int	process_lines(char **lines, t_scene *scene, int *map_start)
{
	int		i;
	char	*trimmed;

	i = 0;
	*map_start = -1;
	while (lines[i])
	{
		trimmed = ft_strtrim(lines[i], " \t\n\r");
		if (!trimmed)
			return (0);
		if (ft_strlen(trimmed) == 0)
		{
			free(trimmed);
			i++;
			continue;
		}
		if (*map_start == -1 && is_map_line(lines[i]))
			*map_start = i;
		else if (*map_start == -1)
		{
			if (!process_config_line(lines[i], scene))
				return (free(trimmed), 0);
		}
		else if (*map_start != -1)
		{
			if (is_texture_line(trimmed) || is_color_line(trimmed))
				return (free(trimmed), error_msg("Invalid element order: map must come after all texture and color definitions"), 0);
		}
		free(trimmed);
		i++;
	}
	return (1);
}
