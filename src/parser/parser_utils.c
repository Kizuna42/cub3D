/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 00:00:00 by kizuna            #+#    #+#             */
/*   Updated: 2025/06/21 22:05:58 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse_texture(t_texture *texture, char *path)
{
	int	fd;

	if (texture->path)
	{
		printf("Error\nDuplicate texture configuration.\n");
		return (0);
	}
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		printf("Error\nCannot open texture file: %s\n", path);
		return (0);
	}
	close(fd);
	texture->path = ft_strdup(path);
	if (!texture->path)
	{
		printf("Error\nMemory allocation failed for texture path.\n");
		return (0);
	}
	return (1);
}

static int	validate_and_assign_rgb(t_color *color, char **rgb_tokens)
{
	int	i;
	int	rgb[3];

	i = 0;
	while (i < 3)
	{
		rgb[i] = ft_atoi(rgb_tokens[i]);
		if (rgb[i] < 0 || rgb[i] > 255)
		{
			printf("Error\nRGB values must be between 0 and 255.\n");
			return (0);
		}
		i++;
	}
	color->r = rgb[0];
	color->g = rgb[1];
	color->b = rgb[2];
	color->trgb = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
	return (1);
}

int	parse_color(t_color *color, char *rgb_str)
{
	char	**rgb_tokens;
	int		i;
	int		ret;

	if (color->trgb != 0)
		return (printf("Error\nDuplicate color configuration.\n"), 0);
	rgb_tokens = ft_split(rgb_str, ',');
	if (!rgb_tokens)
		return (printf("Error\nMemory allocation failed for RGB tokens.\n"), 0);
	i = 0;
	while (rgb_tokens[i])
		i++;
	if (i != 3)
	{
		free_tokens(rgb_tokens);
		return (printf("Error\nInvalid RGB format. Use R,G,B.\n"), 0);
	}
	ret = validate_and_assign_rgb(color, rgb_tokens);
	free_tokens(rgb_tokens);
	return (ret);
}

int	dispatch_config(t_game *game, char **tokens)
{
	if (ft_strncmp(tokens[0], "NO", 3) == 0)
		return (parse_texture(&game->north_tex, tokens[1]));
	if (ft_strncmp(tokens[0], "SO", 3) == 0)
		return (parse_texture(&game->south_tex, tokens[1]));
	if (ft_strncmp(tokens[0], "WE", 3) == 0)
		return (parse_texture(&game->west_tex, tokens[1]));
	if (ft_strncmp(tokens[0], "EA", 3) == 0)
		return (parse_texture(&game->east_tex, tokens[1]));
	if (ft_strncmp(tokens[0], "F", 2) == 0)
		return (parse_color(&game->floor_color, tokens[1]));
	if (ft_strncmp(tokens[0], "C", 2) == 0)
		return (parse_color(&game->ceiling_color, tokens[1]));
	return (printf("Error\nUnknown identifier: %s\n", tokens[0]), 0);
}

int	parse_config_line(t_game *game, const char *line)
{
	char	**tokens;
	int		result;
	int		token_count;

	tokens = ft_split(line, ' ');
	if (!tokens)
		return (printf("Error\nMemory allocation failed.\n"), 0);
	token_count = 0;
	while (tokens[token_count])
		token_count++;
	if (token_count != 2)
	{
		free_tokens(tokens);
		return (printf("Error\nInvalid config format near: %s\n", line), 0);
	}
	result = dispatch_config(game, tokens);
	free_tokens(tokens);
	return (result);
} 