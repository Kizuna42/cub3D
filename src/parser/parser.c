/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 00:00:00 by kizuna            #+#    #+#             */
/*   Updated: 2025/06/21 22:05:21 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_tokens(char **tokens)
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

static int	all_configs_loaded(t_game *game)
{
	if (game->north_tex.path
		&& game->south_tex.path
		&& game->west_tex.path
		&& game->east_tex.path
		&& game->floor_color.trgb != 0
		&& game->ceiling_color.trgb != 0)
		return (1);
	return (0);
}

static int	parse_config_line(t_game *game, const char *line)
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

static int	process_line_in_config(t_game *game, char *line,
	char **line_after_config)
{
	char	*trimmed;
	int		status;

	trimmed = ft_strtrim(line, " \t\n\v\f\r");
	if (trimmed && *trimmed != '\0')
	{
		if (all_configs_loaded(game))
		{
			*line_after_config = line;
			free(trimmed);
			return (2);
		}
		status = parse_config_line(game, trimmed);
		free(trimmed);
		if (!status)
		{
			free(line);
			return (0);
		}
	}
	free(line);
	return (1);
}

static int	parse_config_section(t_game *game, int fd, char **line_after_config)
{
	char	*line;
	int		status;

	*line_after_config = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		status = process_line_in_config(game, line, line_after_config);
		if (status == 0)
			return (0);
		if (status == 2)
			return (1);
	}
	return (1);
}

static int	parse_map_grid_section(t_game *game, int fd, char *first_line)
{
	t_list	*map_lines;
	char	*line;
	char	*trimmed_line;
	int		ret;

	map_lines = NULL;
	line = first_line;
	while (line)
	{
		trimmed_line = ft_strtrim(line, "\n");
		if (!trimmed_line)
			return (ft_lstclear(&map_lines, free), 0);
		ft_lstadd_back(&map_lines, ft_lstnew(trimmed_line));
		free(line);
		line = get_next_line(fd);
	}
	if (!map_lines)
		return (printf("Error\nMap is empty.\n"), 0);
	ret = convert_list_to_grid(game, map_lines);
	ft_lstclear(&map_lines, free);
	return (ret);
}

int	parse_map_file(t_game *game, const char *filename)
{
	int		fd;
	char	*line_after_config;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (printf("Error\nCannot open file: %s\n", filename), 0);
	if (!parse_config_section(game, fd, &line_after_config))
	{
		close(fd);
		return (0);
	}
	if (!all_configs_loaded(game))
	{
		free(line_after_config);
		close(fd);
		return (printf("Error\nIncomplete configuration.\n"), 0);
	}
	if (!parse_map_grid_section(game, fd, line_after_config))
	{
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}
