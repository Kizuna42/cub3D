/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by KIZUNA            #+#    #+#             */
/*   Updated: 2025/06/22 03:30:56 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	count_map_lines(char **lines, int start)
{
	int	count;

	count = 0;
	while (lines[start + count])
		count++;
	return (count);
}

int	get_max_width(char **lines, int start, int count)
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

int	fill_map_line(t_scene *scene, char **lines, int start, int i)
{
	int	j;
	int	max_width;

	max_width = scene->map_width;
	j = 0;
	while (j < max_width)
	{
		if (j < (int)ft_strlen(lines[start + i]))
		{
			if (!process_map_char(scene, lines[start + i][j], j, i))
				return (0);
		}
		else
			scene->map[i][j] = ' ';
		j++;
	}
	scene->map[i][max_width] = '\0';
	return (1);
}

void	free_partial_map(t_scene *scene, int allocated_rows)
{
	int	i;

	if (!scene->map)
		return ;
	i = 0;
	while (i < allocated_rows)
	{
		if (scene->map[i])
			free(scene->map[i]);
		i++;
	}
	free(scene->map);
	scene->map = NULL;
}

int	set_player_position(t_scene *scene, int x, int y, char dir)
{
	if (scene->player.spawn_dir != 0)
		return (error_msg("Multiple player positions found"), 0);
	scene->player.pos.x = x + 0.5;
	scene->player.pos.y = y + 0.5;
	scene->player.spawn_dir = dir;
	return (1);
}
