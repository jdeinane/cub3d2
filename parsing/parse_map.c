/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubaldo <jubaldo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:04:56 by jubaldo           #+#    #+#             */
/*   Updated: 2024/06/02 19:43:52 by jubaldo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void add_line_to_map(t_cub3d *game, char **map_lines, char *line, int map_height)
{
    map_lines[map_height] = ft_strdup(line);
    if (!map_lines[map_height])
        error_exit(game, "Error: Memory allocation failed");
}

static char **allocate_new_map_lines(t_cub3d *game, char **map_lines, int map_height)
{
    char **new_map_lines;
    int i;

    new_map_lines = malloc(sizeof(char *) * (map_height + 1));
    if (!new_map_lines)
        error_exit(game, "Error: Memory allocation failed");
    i = 0;
    while (i < map_height)
    {
        new_map_lines[i] = map_lines[i];
        i++;
    }
    if (map_lines)
        free(map_lines);
    return (new_map_lines);
}
static bool is_valid_map_line(const char *line, int *player_count)
{
	bool valid = true;

	while (*line)
	{
		if (!ft_strchr("01NSEW ", *line)) // Allow space as a valid character
		{ 
			valid = false;
			break;
		}
		if (ft_strchr("NSEW", *line))
			(*player_count)++;
		line++;
	}

	if (*player_count > 1)
		valid = false;
	return valid && (*player_count <= 1);
}
void parse_map(t_cub3d *game, char *line)
{
    static char **map_lines = NULL;
    static int map_height = 0;
    char **new_map_lines;
    static int player_count = 0;

    if (line[0] == '\0')
    {
        return;
    }
    if (!is_valid_map_line(line, &player_count))
    {
        error_exit(game, "Error: Invalid map characters or multiple player start positions");
    }
    new_map_lines = allocate_new_map_lines(game, map_lines, map_height);
    add_line_to_map(game, new_map_lines, line, map_height);
    map_lines = new_map_lines;
    map_height++;
    game->map = map_lines;
    game->map_height = map_height;
    game->map_width = ft_strlen(line);
}