/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25/ 10:00:00 by kizuna            #+#    #+#             */
/*   Updated: 2023/10/25/ 10:00:00 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Foward declarations for functions to be created
int	parse_texture(char *line, t_game *game);
int	parse_color(char *line, t_game *game);
int	parse_map(char *line, int fd, t_game *game);

int	is_all_elements_parsed(t_game *game)
{
	if (game->textures.north && game->textures.south && game->textures.west
		&& game->textures.east && game->textures.floor != -1
		&& game->textures.ceiling != -1)
		return (1);
	return (0);
}

int	parse_line(char *line, int fd, t_game *game)
{
	char	*trimmed_line;

	trimmed_line = ft_strtrim(line, " \t\v\f\r");
	if (!trimmed_line)
		return (printf("Error\n%s\n", ERR_MALLOC), 1);
	if (*trimmed_line == '\0')
	{
		free(trimmed_line);
		return (0);
	}
	if (ft_strncmp(trimmed_line, "NO ", 3) == 0
		|| ft_strncmp(trimmed_line, "SO ", 3) == 0
		|| ft_strncmp(trimmed_line, "WE ", 3) == 0
		|| ft_strncmp(trimmed_line, "EA ", 3) == 0)
		return (parse_texture(trimmed_line, game));
	if (ft_strncmp(trimmed_line, "F ", 2) == 0
		|| ft_strncmp(trimmed_line, "C ", 2) == 0)
		return (parse_color(trimmed_line, game));
	if (is_all_elements_parsed(game))
		return (parse_map(line, fd, game));
	free(trimmed_line);
	return (printf("Error\n%s\n", ERR_PARSE_ID), 1);
}

int	parse_file(const char *filename, t_game *game)
{
	int		fd;
	char	*line;
	int		ret;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (printf("Error\n%s\n", ERR_FILE_OPEN), 1);
	line = get_next_line(fd);
	while (line)
	{
		ret = parse_line(line, fd, game);
		free(line);
		if (ret != 0)
		{
			close(fd);
			return (ret);
		}
		line = get_next_line(fd);
	}
	close(fd);
	if (!is_all_elements_parsed(game))
		return (printf("Error\n%s\n", ERR_PARSE_ID), 1);
	// TODO: Add map validation after parsing
	return (0);
}
