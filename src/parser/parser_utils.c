/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 10:00:00 by kizuna            #+#    #+#             */
/*   Updated: 2025/06/21 22:38:18 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse_texture(char *line, t_game *game)
{
	char	**split_line;

	split_line = ft_split(line, ' ');
	if (!split_line || !split_line[0] || !split_line[1] || split_line[2])
	{
		// TODO: free split_line
		return (printf("Error\n%s\n", ERR_PARSE_TEX), 1);
	}
	if (ft_strncmp(split_line[0], "NO", 3) == 0)
		game->textures.north = ft_strdup(split_line[1]);
	else if (ft_strncmp(split_line[0], "SO", 3) == 0)
		game->textures.south = ft_strdup(split_line[1]);
	else if (ft_strncmp(split_line[0], "WE", 3) == 0)
		game->textures.west = ft_strdup(split_line[1]);
	else if (ft_strncmp(split_line[0], "EA", 3) == 0)
		game->textures.east = ft_strdup(split_line[1]);
	// TODO: free split_line
	return (0);
}

// TODO: Implement proper RGB to int conversion and validation
static int	convert_rgb_to_int(char *rgb_str)
{
	char	**rgb_values;
	int		r;
	int		g;
	int		b;
	int		color;

	rgb_values = ft_split(rgb_str, ',');
	if (!rgb_values || !rgb_values[0] || !rgb_values[1] || !rgb_values[2]
		|| rgb_values[3])
	{
		// TODO: free rgb_values
		return (-1);
	}
	r = ft_atoi(rgb_values[0]);
	g = ft_atoi(rgb_values[1]);
	b = ft_atoi(rgb_values[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		// TODO: free rgb_values
		return (-1);
	}
	color = (r << 16) | (g << 8) | b;
	// TODO: free rgb_values
	return (color);
}

int	parse_color(char *line, t_game *game)
{
	char	**split_line;
	int		color;

	split_line = ft_split(line, ' ');
	if (!split_line || !split_line[0] || !split_line[1] || split_line[2])
	{
		// TODO: free split_line
		return (printf("Error\n%s\n", ERR_PARSE_COLOR), 1);
	}
	color = convert_rgb_to_int(split_line[1]);
	if (color == -1)
	{
		// TODO: free split_line
		return (printf("Error\n%s\n", ERR_PARSE_COLOR), 1);
	}
	if (ft_strncmp(split_line[0], "F", 2) == 0)
		game->textures.floor = color;
	else if (ft_strncmp(split_line[0], "C", 2) == 0)
		game->textures.ceiling = color;
	// TODO: free split_line
	return (0);
} 