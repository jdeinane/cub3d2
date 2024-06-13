/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_position.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubaldo <jubaldo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 17:25:27 by jubaldo           #+#    #+#             */
/*   Updated: 2024/06/13 17:50:02 by jubaldo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	set_player_position(t_cub3d *game, int x, int y, char direction)
{
	game->player.pos_x = x + 0.5;
	game->player.pos_y = y + 0.5;
	set_player_direction(game, direction);
	game->map[y][x] = '0';
}

int	find_initial_position(t_cub3d *game, int *x, int *y)
{
	char	cell;

	*y = 0;
	while (*y < game->map_height)
	{
		*x = 0;
		while (*x < (int)ft_strlen(game->map[*y]))
		{
			cell = game->map[*y][*x];
			if (cell == 'N' || cell == 'S' || cell == 'W' || cell == 'E')
			{
				return (1);
			}
			(*x)++;
		}
		(*y)++;
	}
	return (0);
}

void	init_player_position(t_cub3d *game)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	if (find_initial_position(game, &x, &y))
		set_player_position(game, x, y, game->map[y][x]);
	else
		error_exit(game, "Error: No initial player position set in the map");
}

void	parse_line(t_cub3d *game, char *line, t_parse_state *state)
{
	line = trim_leading_whitespace(line);
	if (line[0] == '\0')
		return ;
	if (line[0] == 'N' && line[1] == 'O')
		handle_texture_parsing(game, line, state, 0);
	else if (line[0] == 'S' && line[1] == 'O')
		handle_texture_parsing(game, line, state, 1);
	else if (line[0] == 'W' && line[1] == 'E')
		handle_texture_parsing(game, line, state, 2);
	else if (line[0] == 'E' && line[1] == 'A')
		handle_texture_parsing(game, line, state, 3);
	else if (line[0] == 'F')
		handle_color_parsing(game, line, state, 0);
	else if (line[0] == 'C')
		handle_color_parsing(game, line, state, 1);
	else
		error_exit2(game, "Error: Invalid map configuration", line);
}
