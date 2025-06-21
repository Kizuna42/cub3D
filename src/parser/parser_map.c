/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 00:00:00 by kizuna            #+#    #+#             */
/*   Updated: 2025/06/21 22:06:12 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	set_player_start(t_game *game, int y, int x)
{
	if (game->player.dir_x != 0 || game->player.dir_y != 0)
		return (printf("Error\nMultiple player start positions.\n"), 0);
	game->player.pos_x = x + 0.5;
	game->player.pos_y = y + 0.5;
	if (game->map.grid[y][x] == 'N')
		game->player.dir_y = -1;
	else if (game->map.grid[y][x] == 'S')
		game->player.dir_y = 1;
	else if (game->map.grid[y][x] == 'W')
		game->player.dir_x = -1;
	else if (game->map.grid[y][x] == 'E')
		game->player.dir_x = 1;
	game->map.grid[y][x] = '0';
	return (1);
}

static int	find_player_position(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			if (ft_strchr("NSEW", game->map.grid[y][x]))
			{
				if (!set_player_start(game, y, x))
					return (0);
			}
			x++;
		}
		y++;
	}
	if (game->player.dir_x == 0 && game->player.dir_y == 0)
		return (printf("Error\nNo player start position found.\n"), 0);
	return (1);
}

static void	calculate_map_dimensions(t_list *map_lines, t_map *map)
{
	t_list	*current;
	size_t	len;

	map->height = ft_lstsize(map_lines);
	map->width = 0;
	current = map_lines;
	while (current)
	{
		len = ft_strlen(current->content);
		if (len > map->width)
			map->width = len;
		current = current->next;
	}
}

static int	populate_grid(t_game *game, t_list *map_lines)
{
	int		y;
	t_list	*current;

	game->map.grid = ft_calloc(game->map.height + 1, sizeof(char *));
	if (!game->map.grid)
		return (printf("Error\nMap memory allocation failed.\n"), 0);
	y = 0;
	current = map_lines;
	while (y < game->map.height)
	{
		game->map.grid[y] = ft_calloc(game->map.width + 1, sizeof(char));
		if (!game->map.grid[y])
		{
			free_tokens(game->map.grid);
			return (printf("Error\nMap row memory allocation failed.\n"), 0);
		}
		ft_memset(game->map.grid[y], ' ', game->map.width);
		ft_memcpy(game->map.grid[y], current->content,
			ft_strlen(current->content));
		current = current->next;
		y++;
	}
	return (1);
}

int	convert_list_to_grid(t_game *game, t_list *map_lines)
{
	calculate_map_dimensions(map_lines, &game->map);
	if (!populate_grid(game, map_lines))
		return (0);
	if (!find_player_position(game))
	{
		free_tokens(game->map.grid);
		game->map.grid = NULL;
		return (0);
	}
	return (1);
} 