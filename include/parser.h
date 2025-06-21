/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 00:00:00 by kizuna            #+#    #+#             */
/*   Updated: 2025/06/21 19:15:32 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

// Forward declaration to avoid circular dependency
struct s_game;

// Main parsing function
int	parse_map_file(struct s_game *game, const char *filename);

// Parser utils
int		parse_texture(t_texture *texture, char *path);
int		parse_color(t_color *color, char *rgb_str);
void	free_tokens(char **tokens);

#endif 