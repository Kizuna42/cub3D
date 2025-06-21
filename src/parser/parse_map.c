/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by KIZUNA            #+#    #+#             */
/*   Updated: 2025/06/21 23:51:30 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S'
		|| c == 'E' || c == 'W' || c == ' ');
}

static int	find_player(char **grid, int height, t_player *player)
{
	int	y;
	int	x;
	int	player_count;

	player_count = 0;
	y = 0;
	while (y < height)
	{
		x = 0;
		while (grid[y][x])
		{
			if (grid[y][x] == 'N' || grid[y][x] == 'S'
				|| grid[y][x] == 'E' || grid[y][x] == 'W')
			{
				player->pos.x = x + 0.5;
				player->pos.y = y + 0.5;
				player->spawn_dir = grid[y][x];
				grid[y][x] = '0';
				player_count++;
			}
			x++;
		}
		y++;
	}
	return (player_count == 1);
}

static int	get_map_width(char **lines, int height)
{
	int	max_width;
	int	width;
	int	i;

	max_width = 0;
	i = 0;
	while (i < height)
	{
		width = ft_strlen(lines[i]);
		if (width > max_width)
			max_width = width;
		i++;
	}
	return (max_width);
}

int	parse_map_from_lines(char **lines, t_scene *scene)
{
	int	i;
	int	j;

	scene->map.height = 0;
	while (lines[scene->map.height])
		scene->map.height++;
	if (scene->map.height == 0)
		return (0);
	scene->map.width = get_map_width(lines, scene->map.height);
	scene->map.grid = safe_malloc(sizeof(char *) * (scene->map.height + 1));
	i = 0;
	while (i < scene->map.height)
	{
		scene->map.grid[i] = safe_malloc(sizeof(char) * (scene->map.width + 1));
		j = 0;
		while (j < scene->map.width)
		{
			if (j < (int)ft_strlen(lines[i]) && is_valid_map_char(lines[i][j]))
				scene->map.grid[i][j] = lines[i][j];
			else
				scene->map.grid[i][j] = ' ';
			j++;
		}
		scene->map.grid[i][j] = '\0';
		i++;
	}
	scene->map.grid[i] = NULL;
	return (find_player(scene->map.grid, scene->map.height, &scene->player));
} 