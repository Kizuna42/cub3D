/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by KIZUNA            #+#    #+#             */
/*   Updated: 2025/06/21 23:32:31 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

char	*get_next_line(int fd)
{
	static char	*buffer = NULL;
	char		*line;
	char		*temp;
	int			bytes_read;
	char		read_buffer[1024];

	if (fd < 0)
		return (NULL);
	if (!buffer)
		buffer = ft_strdup("");
	bytes_read = read(fd, read_buffer, 1023);
	if (bytes_read <= 0)
	{
		if (buffer && ft_strlen(buffer) > 0)
		{
			line = buffer;
			buffer = NULL;
			return (line);
		}
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	read_buffer[bytes_read] = '\0';
	temp = ft_strjoin(buffer, read_buffer);
	free(buffer);
	buffer = temp;
	if (ft_strchr(buffer, '\n'))
	{
		line = ft_substr(buffer, 0, ft_strchr(buffer, '\n') - buffer + 1);
		temp = ft_strdup(ft_strchr(buffer, '\n') + 1);
		free(buffer);
		buffer = temp;
		return (line);
	}
	return (get_next_line(fd));
} 