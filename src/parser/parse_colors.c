/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by KIZUNA            #+#    #+#             */
/*   Updated: 2025/06/21 23:34:06 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	validate_rgb_value(int value)
{
	return (value >= 0 && value <= 255);
}

static int	parse_rgb_values(char *rgb_str, t_color *color)
{
	char	**values;
	int		i;

	values = ft_split(rgb_str, ',');
	if (!values)
		return (0);
	i = 0;
	while (values[i])
		i++;
	if (i != 3)
	{
		ft_free_split(values);
		return (0);
	}
	color->r = ft_atoi(values[0]);
	color->g = ft_atoi(values[1]);
	color->b = ft_atoi(values[2]);
	ft_free_split(values);
	if (!validate_rgb_value(color->r) || !validate_rgb_value(color->g) ||
		!validate_rgb_value(color->b))
		return (0);
	color->rgb = create_rgb(color->r, color->g, color->b);
	return (1);
}

int	parse_colors(char *line, t_scene *scene)
{
	char	*rgb_str;
	t_color	*target;

	if (line[0] == 'F')
		target = &scene->floor_color;
	else if (line[0] == 'C')
		target = &scene->ceiling_color;
	else
		return (0);
	if (target->rgb != 0)
		return (0);
	rgb_str = ft_strtrim(line + 1, " \t");
	if (!rgb_str)
		return (0);
	if (!parse_rgb_values(rgb_str, target))
	{
		free(rgb_str);
		return (0);
	}
	free(rgb_str);
	return (1);
}