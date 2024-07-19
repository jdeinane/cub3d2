/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubaldo <jubaldo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 17:15:48 by jubaldo           #+#    #+#             */
/*   Updated: 2024/07/19 19:02:13 by jubaldo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*trim_leading_whitespace(char *line)
{
	while (*line == ' ' || *line == '\t')
	{
		line++;
	}
	return (line);
}

void	open_file(t_cub3d *game, const char *filename, int *fd)
{
	*fd = open(filename, O_RDONLY);
	if (*fd < 0)
		error_exit(game, "Error: Error opening file");
}

void	parse_file(t_cub3d *game, const char *filename)
{
	int				fd;
	t_parse_state	state;

	state.textures_parsed[0] = 0;
	state.textures_parsed[1] = 0;
	state.textures_parsed[2] = 0;
	state.textures_parsed[3] = 0;
	state.colors_parsed[0] = 0;
	state.colors_parsed[1] = 0;
	state.parsing_map = 0;
	open_file(game, filename, &fd);
	process_file_lines(game, fd, &state);
	close(fd);
	check_missing_definitions(game, &state);
	validate_map(game);
	init_player_position(game);
}
