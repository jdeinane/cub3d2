/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubaldo <jubaldo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 17:33:45 by jubaldo           #+#    #+#             */
/*   Updated: 2024/06/13 17:50:59 by jubaldo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	handle_parsing(t_cub3d *game, char *line, t_parse_state *state)
{
	if (state->parsing_map)
		parse_map(game, line);
	else
		parse_line(game, line, state);
}

void	process_line(t_cub3d *game, char *line, t_parse_state *state)
{
	set_parsing_map_flag(&state->parsing_map, line);
	handle_parsing(game, line, state);
}

void	process_remaining_line(t_cub3d *game, char *line, t_parse_state *state)
{
	if (line != NULL)
	{
		process_line(game, line, state);
		free(line);
	}
}

void	process_file_lines(t_cub3d *game, int fd, t_parse_state *state)
{
	char	*line;
	int		ret;

	ret = get_next_line(fd, &line);
	while (ret > 0)
	{
		process_line(game, line, state);
		free(line);
		ret = get_next_line(fd, &line);
	}
	process_remaining_line(game, line, state);
}
