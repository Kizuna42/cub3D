/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 17:30:00 by kizuna            #+#    #+#             */
/*   Updated: 2025/07/05 17:30:00 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	validate_comma_count(char *str)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
		if (str[i++] == ',')
			count++;
	return (count == 2);
}

static int	validate_trimmed_parts(char **rgb_parts)
{
	int		i;
	char	*trimmed;

	i = 0;
	while (i < 3)
	{
		trimmed = ft_strtrim(rgb_parts[i], " \t");
		if (!trimmed || ft_strlen(trimmed) == 0)
		{
			if (trimmed)
				free(trimmed);
			return (0);
		}
		free(trimmed);
		i++;
	}
	return (1);
}

int	validate_rgb_format_and_parts(char *str, char ***rgb_parts)
{
	int	i;

	if (!validate_comma_count(str))
		return (error_msg("RGB must have exactly 2 commas"), 0);
	*rgb_parts = ft_split(str, ',');
	if (!*rgb_parts)
		return (error_msg("Failed to split RGB values"), 0);
	i = 0;
	while ((*rgb_parts)[i])
		i++;
	if (i != 3)
		return (error_msg("RGB must have exactly 3 values"), 0);
	if (!validate_trimmed_parts(*rgb_parts))
		return (error_msg("Empty RGB value found"), 0);
	return (1);
}
