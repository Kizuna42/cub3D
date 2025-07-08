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

static int	convert_to_number(char *trimmed, int *result)
{
	long	num;
	int		i;

	num = 0;
	i = 0;
	while (trimmed[i])
	{
		num = num * 10 + (trimmed[i] - '0');
		if (num > 255)
			return (0);
		i++;
	}
	*result = (int)num;
	return (1);
}

static int	safe_atoi(char *str, int *result)
{
	int		i;
	char	*trimmed;

	trimmed = ft_strtrim(str, " \t");
	if (!trimmed)
		return (0);
	if (ft_strlen(trimmed) > 3 || ft_strlen(trimmed) == 0)
		return (free(trimmed), 0);
	i = 0;
	while (trimmed[i])
	{
		if (!ft_isdigit(trimmed[i]))
			return (free(trimmed), 0);
		i++;
	}
	if (!convert_to_number(trimmed, result))
		return (free(trimmed), 0);
	free(trimmed);
	return (1);
}

static int	parse_rgb_values(char *str, t_color *color)
{
	char	**rgb_parts;

	if (!validate_rgb_format_and_parts(str, &rgb_parts))
		return (0);
	if (!safe_atoi(rgb_parts[0], &color->r)
		|| !safe_atoi(rgb_parts[1], &color->g)
		|| !safe_atoi(rgb_parts[2], &color->b))
	{
		ft_free_split(rgb_parts);
		return (error_msg("Invalid RGB values"), 0);
	}
	ft_free_split(rgb_parts);
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
