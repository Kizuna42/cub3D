/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by KIZUNA            #+#    #+#             */
/*   Updated: 2025/06/22 00:49:12 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	process_map_char(t_scene *scene, char c, int x, int y)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (!set_player_position(scene, x, y, c))
			return (0);
		scene->map[y][x] = '0';
	}
	else if (c == '0' || c == '1' || c == ' ')
		scene->map[y][x] = c;
	else
		return (error_msg("Invalid character in map"), 0);
	return (1);
}

static int	allocate_map_memory(t_scene *scene, int count, int max_width)
{
	int	i;

	scene->map_height = count;
	scene->map_width = max_width;
	scene->map = malloc(sizeof(char *) * (count + 1));
	if (!scene->map)
		return (error_msg("Memory allocation failed"), 0);
	i = 0;
	while (i < count)
	{
		scene->map[i] = malloc(sizeof(char) * (max_width + 1));
		if (!scene->map[i])
		{
			free_partial_map(scene, i);
			return (error_msg("Memory allocation failed"), 0);
		}
		i++;
	}
	scene->map[count] = NULL;
	return (1);
}

int	parse_map_data(char **lines, t_scene *scene, int start_line)
{
	int	count;
	int	max_width;
	int	i;

	count = count_map_lines(lines, start_line);
	max_width = get_max_width(lines, start_line, count);
	if (!allocate_map_memory(scene, count, max_width))
		return (0);
	i = 0;
	while (i < count)
	{
		if (!fill_map_line(scene, lines, start_line, i))
		{
			free_partial_map(scene, i + 1);
			return (0);
		}
		i++;
	}
	return (1);
}
