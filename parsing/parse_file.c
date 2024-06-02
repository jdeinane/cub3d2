/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubaldo <jubaldo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 17:15:48 by jubaldo           #+#    #+#             */
/*   Updated: 2024/06/02 19:33:08 by jubaldo          ###   ########.fr       */
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

void parse_line(t_cub3d *game, char *line)
{
	if (line[0] == '\0')
		return; // Skip empty lines

	if (line[0] == 'N' && line[1] == 'O')
		parse_textures(game, line);
	else if (line[0] == 'S' && line[1] == 'O')
		parse_textures(game, line);
	else if (line[0] == 'W' && line[1] == 'E')
		parse_textures(game, line);
	else if (line[0] == 'E' && line[1] == 'A')
		parse_textures(game, line);
	else if (line[0] == 'F')
		parse_color(&game->floor_color, line);
	else if (line[0] == 'C')
		parse_color(&game->ceiling_color, line);
	else
		parse_map(game, line); // Treat it as a map line
}

void parse_file(t_cub3d *game, const char *filename)
{
    int fd;
    char *line;
    int ret;

    fd = open(filename, O_RDONLY);
    if (fd < 0)
        error_exit(game, "Error: Error opening file");

    while ((ret = get_next_line(fd, &line)) > 0)
    {
        parse_line(game, line);
        free(line);
    }
    if (ret >= 0 && line != NULL) // Ensure the last line is processed
    {
        parse_line(game, line);
        free(line);
    }
    close(fd);

    // Validate the map after parsing all lines
    validate_map_walls(game);

    // Initialize player position after validation
    init_player_position(game);

}
