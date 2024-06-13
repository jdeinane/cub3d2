/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_ct.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubaldo <jubaldo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 17:30:42 by jubaldo           #+#    #+#             */
/*   Updated: 2024/06/13 17:52:04 by jubaldo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	set_parsing_map_flag(int *parsing_map, char *line)
{
	if (!*parsing_map && (line[0] == '1' || line[0] == ' '))
		*parsing_map = 1;
}

void	handle_texture_parsing(t_cub3d *game, char *line, \
			t_parse_state *state, int index)
{
	if (state->textures_parsed[index])
		error_exit2(game, "Error: Duplicate texture definition", line);
	parse_textures(game, line);
	state->textures_parsed[index] = 1;
}

void	handle_color_parsing(t_cub3d *game, char *line, \
			t_parse_state *state, int index)
{
	if (state->colors_parsed[index])
		error_exit2(game, "Error: Duplicate color definition", line);
	parse_color(game, line);
	state->colors_parsed[index] = 1;
}

void	check_missing_definitions(t_cub3d *game, t_parse_state *state)
{
	if (!(state->textures_parsed[0] && state->textures_parsed[1] \
		&& state->textures_parsed[2] && state->textures_parsed[3]))
		error_exit(game, "Error: Missing one or more texture definitions");
	if (!(state->colors_parsed[0] && state->colors_parsed[1]))
		error_exit(game, "Error: Missing floor or ceiling color definition");
	if (!state->parsing_map)
		error_exit(game, "Error: No map data found");
}
