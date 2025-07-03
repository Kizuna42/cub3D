/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by KIZUNA            #+#    #+#             */
/*   Updated: 2025/06/22 00:38:10 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	is_valid_number_string(char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && str[i] != ' ' && str[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

static int	validate_rgb_value(int value)
{
	return (value >= 0 && value <= 255);
}

static int	parse_rgb_values(char *str, t_color *color)
{
	char	**rgb_parts;
	int		i;

	rgb_parts = ft_split(str, ',');
	if (!rgb_parts)
		return (error_msg("Failed to split RGB values"), 0);
	i = 0;
	while (rgb_parts[i])
		i++;
	if (i != 3)
		return (ft_free_split(rgb_parts),
			error_msg("RGB must have exactly 3 values"), 0);
	if (!is_valid_number_string(rgb_parts[0])
		|| !is_valid_number_string(rgb_parts[1])
		|| !is_valid_number_string(rgb_parts[2]))
		return (ft_free_split(rgb_parts),
			error_msg("RGB values must contain only digits"), 0);
	color->r = ft_atoi(rgb_parts[0]);
	color->g = ft_atoi(rgb_parts[1]);
	color->b = ft_atoi(rgb_parts[2]);
	ft_free_split(rgb_parts);
	if (!validate_rgb_value(color->r) || !validate_rgb_value(color->g)
		|| !validate_rgb_value(color->b))
		return (error_msg("RGB values must be between 0 and 255"), 0);
	return (1);
}

int	parse_color_line(char *line, t_scene *scene)
{
	char		*trimmed;
	t_color		color;

	trimmed = ft_strtrim(line + 1, " \t");
	if (!trimmed)
		return (error_msg("Failed to trim color line"), 0);
	if (!parse_rgb_values(trimmed, &color))
		return (free(trimmed), 0);
	free(trimmed);
	if (line[0] == 'F')
	{
		if (scene->has_floor)
			return (error_msg("Duplicate floor color definition"), 0);
		scene->floor_color = (color.r << 16) | (color.g << 8) | color.b;
		scene->has_floor = 1;
	}
	else if (line[0] == 'C')
	{
		if (scene->has_ceiling)
			return (error_msg("Duplicate ceiling color definition"), 0);
		scene->ceiling_color = (color.r << 16) | (color.g << 8) | color.b;
		scene->has_ceiling = 1;
	}
	return (1);
}
