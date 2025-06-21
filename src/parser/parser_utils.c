/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 00:00:00 by kizuna            #+#    #+#             */
/*   Updated: 2025/06/21 19:15:10 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parser.h"

static int	is_valid_rgb_value(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	parse_color(t_color *color, char *rgb_str)
{
	char	**rgb_values;
	int		r;
	int		g;
	int		b;

	if (color->trgb != 0)
		return (ft_putendl_fd("Error: Duplicate color definition.", 2), 0);
	if (!rgb_str)
		return (ft_putendl_fd("Error: Missing color definition.", 2), 0);
	rgb_values = ft_split(rgb_str, ',');
	if (!rgb_values || !rgb_values[0] || !rgb_values[1] || !rgb_values[2]
		|| rgb_values[3] || !is_valid_rgb_value(rgb_values[0])
		|| !is_valid_rgb_value(rgb_values[1]) || !is_valid_rgb_value(rgb_values[2]))
	{
		free_tokens(rgb_values);
		return (ft_putendl_fd("Error: Invalid RGB format.", 2), 0);
	}
	r = ft_atoi(rgb_values[0]);
	g = ft_atoi(rgb_values[1]);
	b = ft_atoi(rgb_values[2]);
	free_tokens(rgb_values);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (ft_putendl_fd("Error: RGB values out of range [0-255].", 2), 0);
	color->r = r;
	color->g = g;
	color->b = b;
	color->trgb = (r << 16) | (g << 8) | b;
	return (1);
}

int	parse_texture(t_texture *texture, char *path)
{
	if (texture->path)
	{
		ft_putendl_fd("Error: Duplicate texture definition.", 2);
		return (0);
	}
	if (!path)
	{
		ft_putendl_fd("Error: Missing texture path.", 2);
		return (0);
	}
	texture->path = ft_strdup(path);
	if (!texture->path)
	{
		ft_putendl_fd("Error: Malloc failed for texture path.", 2);
		return (0);
	}
	return (1);
}

void	free_tokens(char **tokens)
{
	int	i;

	if (!tokens)
		return ;
	i = 0;
	while (tokens[i])
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
} 