/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 00:00:00 by kizuna            #+#    #+#             */
/*   Updated: 2025/06/21 19:15:48 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parser.h"

// Prototypes for static functions in this file
static int	parse_config_line(t_game *game, char **tokens);
static int	process_line(t_game *game, char *line);

int	parse_map_file(t_game *game, const char *filename)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return (0);
	}
	line = get_next_line(fd);
	while (line)
	{
		if (!process_line(game, line))
		{
			free(line);
			close(fd);
			return (0);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (1);
}

static int	process_line(t_game *game, char *line)
{
	char	**tokens;
	char	*trimmed_line;
	int		ret;

	ret = 1;
	trimmed_line = ft_strtrim(line, " \t\n\v\f\r");
	if (!trimmed_line || *trimmed_line == '\0')
	{
		free(trimmed_line);
		return (1);
	}
	tokens = ft_split(trimmed_line, ' ');
	free(trimmed_line);
	if (!tokens || !tokens[0])
	{
		free_tokens(tokens);
		return (1);
	}
	ret = parse_config_line(game, tokens);
	free_tokens(tokens);
	return (ret);
}

static int	parse_config_line(t_game *game, char **tokens)
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
	ft_putendl_fd("Info: Map line or unknown identifier.", 1);
	return (1);
}
