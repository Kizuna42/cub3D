/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 00:00:00 by kizuna            #+#    #+#             */
/*   Updated: 2025/06/21 19:10:41 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse_map_file(t_game *game, const char *filename)
{
	int		fd;
	char	*line;

	(void)game; // Temporarily unused
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return (0); // Return 0 for failure
	}
	line = get_next_line(fd);
	while (line)
	{
		// TODO: Process each line
		ft_putstr_fd("Read line: ", 1);
		ft_putstr_fd(line, 1);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (1); // Return 1 for success
}
