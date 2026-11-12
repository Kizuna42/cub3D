/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_lines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 00:00:00 by kizuna            #+#    #+#             */
/*   Updated: 2026/11/12 00:00:00 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	count_lines(const char *content)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (content[i])
	{
		if (content[i] == '\n' || content[i + 1] == '\0')
			count++;
		i++;
	}
	return (count);
}

static int	line_length(const char *str)
{
	int	len;

	len = 0;
	while (str[len] && str[len] != '\n')
		len++;
	return (len);
}

/*
** Split content on '\n' while keeping empty lines, unlike ft_split.
** A trailing newline does not produce an extra empty line.
*/
char	**split_lines(const char *content)
{
	char	**lines;
	int		count;
	int		i;
	int		len;

	count = count_lines(content);
	lines = malloc(sizeof(char *) * (count + 1));
	if (!lines)
		return (NULL);
	i = 0;
	while (i < count)
	{
		len = line_length(content);
		lines[i] = ft_substr(content, 0, len);
		if (!lines[i])
			return (ft_free_split(lines), NULL);
		content += len;
		if (*content == '\n')
			content++;
		lines[++i] = NULL;
	}
	lines[count] = NULL;
	return (lines);
}
