/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by KIZUNA            #+#    #+#             */
/*   Updated: 2025/06/22 00:31:19 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	count_map_lines(char **lines, int start)
{
	int	count;

	count = 0;
	while (lines[start + count])
		count++;
	return (count);
}

static int	get_max_width(char **lines, int start, int count)
{
	int	max_width;
	int	width;
	int	i;

	max_width = 0;
	i = 0;
	while (i < count)
	{
		width = ft_strlen(lines[start + i]);
		if (width > max_width)
			max_width = width;
		i++;
	}
	return (max_width);
}

static int	set_player_position(t_scene *scene, int x, int y, char dir)
{
	if (scene->player.spawn_dir != 0)
		return (error_msg("Multiple player positions found"), 0);
	scene->player.pos.x = x + 0.5;
	scene->player.pos.y = y + 0.5;
	scene->player.spawn_dir = dir;
	return (1);
}

static int	process_map_char(t_scene *scene, char c, int x, int y)
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

int	parse_map_data(char **lines, t_scene *scene, int start_line)
{
	int	count;
	int	max_width;
	int	i;
	int	j;

	count = count_map_lines(lines, start_line);
	max_width = get_max_width(lines, start_line, count);
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
			return (error_msg("Memory allocation failed"), 0);
		j = 0;
		while (j < max_width)
		{
			if (j < (int)ft_strlen(lines[start_line + i]))
			{
				if (!process_map_char(scene, lines[start_line + i][j], j, i))
					return (0);
			}
			else
				scene->map[i][j] = ' ';
			j++;
		}
		scene->map[i][max_width] = '\0';
		i++;
	}
	scene->map[count] = NULL;
	return (1);
}
