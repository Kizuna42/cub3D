/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 00:00:00 by kizuna            #+#    #+#             */
/*   Updated: 2025/07/03 20:30:00 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	process_single_line(char **lines, t_scene *scene,
		int i, int *map_start)
{
	char	*trimmed;

	trimmed = ft_strtrim(lines[i], " \t\n\r");
	if (!trimmed)
		return (0);
	if (ft_strlen(trimmed) == 0)
		return (free(trimmed), 1);
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
			return (free(trimmed),
				error_msg("Invalid element order: map must come after all "
					"texture and color definitions"), 0);
	}
	free(trimmed);
	return (1);
}

int	process_lines(char **lines, t_scene *scene, int *map_start)
{
	int	i;
	int	result;

	i = 0;
	*map_start = -1;
	while (lines[i])
	{
		result = process_single_line(lines, scene, i, map_start);
		if (result <= 0)
			return (result);
		i++;
	}
	return (1);
}
