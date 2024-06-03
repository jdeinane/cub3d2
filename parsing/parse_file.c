/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubaldo <jubaldo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 17:15:48 by jubaldo           #+#    #+#             */
/*   Updated: 2024/06/03 18:59:27 by jubaldo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void set_player_position(t_cub3d *game, int x, int y, char direction)
{
	game->player.pos_x = x + 0.5;
	game->player.pos_y = y + 0.5;

	if (direction == 'N')
	{
		game->player.dir_x = 0;
		game->player.dir_y = -1;
		game->player.plane_x = 0.66;
		game->player.plane_y = 0;
	}
	else if (direction == 'S')
	{
		game->player.dir_x = 0;
		game->player.dir_y = 1;
		game->player.plane_x = -0.66;
		game->player.plane_y = 0;
	}
	else if (direction == 'W')
	{
		game->player.dir_x = -1;
		game->player.dir_y = 0;
		game->player.plane_x = 0;
		game->player.plane_y = -0.66;
	}
	else if (direction == 'E')
	{
		game->player.dir_x = 1;
		game->player.dir_y = 0;
		game->player.plane_x = 0;
		game->player.plane_y = 0.66; 
	}
	game->map[y][x] = '0';
}

static void init_player_position(t_cub3d *game)
{
	int found = 0;

	for (int y = 0; y < game->map_height; y++)
	{
		for (int x = 0; x < (int)ft_strlen(game->map[y]); x++)
		{
			char cell = game->map[y][x];
			if (cell == 'N' || cell == 'S' || cell == 'W' || cell == 'E')
			{
				set_player_position(game, x, y, cell);
				found = 1;
				break;
			}
		}
		if (found)
			break;
	}
	if (!found)
		error_exit(game, "Error: No initial player position set in the map");
}

static char *trim_leading_whitespace(char *line)
{
	while (*line == ' ' || *line == '\t')
		line++;
	return line;
}

static void parse_line(t_cub3d *game, char *line, int *textures_parsed, int *colors_parsed)
{
	line = trim_leading_whitespace(line);
	if (line[0] == '\0')
		return;

	if (line[0] == 'N' && line[1] == 'O')
	{
		if (textures_parsed[0])
			error_exit(game, "Error: Duplicate NO texture definition");
		parse_textures(game, line);
		textures_parsed[0] = 1;
	}
	else if (line[0] == 'S' && line[1] == 'O')
	{
		if (textures_parsed[1])
			error_exit(game, "Error: Duplicate SO texture definition");
		parse_textures(game, line);
		textures_parsed[1] = 1;
	}
	else if (line[0] == 'W' && line[1] == 'E')
	{
		if (textures_parsed[2])
			error_exit(game, "Error: Duplicate WE texture definition");
		parse_textures(game, line);
		textures_parsed[2] = 1;
	}
	else if (line[0] == 'E' && line[1] == 'A')
	{
		if (textures_parsed[3])
			error_exit(game, "Error: Duplicate EA texture definition");
		parse_textures(game, line);
		textures_parsed[3] = 1;
	}
	else if (line[0] == 'F')
	{
		if (colors_parsed[0])
			error_exit(game, "Error: Duplicate floor color definition");
		parse_color(&game->floor_color, line);
		colors_parsed[0] = 1;
	}
	else if (line[0] == 'C')
	{
		if (colors_parsed[1])
			error_exit(game, "Error: Duplicate ceiling color definition");
		parse_color(&game->ceiling_color, line);
		colors_parsed[1] = 1;
	}
	else
	{
		error_exit(game, "Error: Invalid map configuration");
	}
}

void parse_file(t_cub3d *game, const char *filename)
{
	int fd;
	char *line;
	int ret;
	int textures_parsed[4] = {0, 0, 0, 0}; // NO, SO, WE, EA
	int colors_parsed[2] = {0, 0};		   // F, C
	int parsing_map = 0;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_exit(game, "Error: Error opening file");

	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if (!parsing_map && (line[0] == '1' || line[0] == ' '))
		{
			parsing_map = 1;
		}

		if (parsing_map)
		{
			parse_map(game, line);
		}
		else
		{
			parse_line(game, line, textures_parsed, colors_parsed);
		}
		free(line);
	}
	if (ret >= 0 && line != NULL)
	{
		if (parsing_map)
		{
			parse_map(game, line);
		}
		else
		{
			parse_line(game, line, textures_parsed, colors_parsed);
		}
		free(line);
	}
	close(fd);

	if (!(textures_parsed[0] && textures_parsed[1] && textures_parsed[2] && textures_parsed[3]))
		error_exit(game, "Error: Missing one or more texture definitions");
	if (!(colors_parsed[0] && colors_parsed[1]))
		error_exit(game, "Error: Missing floor or ceiling color definition");
	if (!parsing_map)
		error_exit(game, "Error: No map data found");
	validate_map(game);
	init_player_position(game);
}
