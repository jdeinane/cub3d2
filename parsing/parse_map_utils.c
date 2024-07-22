/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubaldo <jubaldo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:04:56 by jubaldo           #+#    #+#             */
/*   Updated: 2024/07/22 16:14:27 by jubaldo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	add_line_to_map(t_cub3d *game, char **map_lines,
							char *line, int map_height)
{
	map_lines[map_height] = ft_strdup(line);
	if (!map_lines[map_height])
		error_exit(game, "Error: Memory allocation failed");
}

char	**allocate_new_map_lines(t_cub3d *game, char **map_lines,
									int map_height)
{
	char	**new_map_lines;
	int		i;

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

bool	is_valid_map_line(const char *line, int *player_count)
{
	bool	valid;

	valid = true;
	while (*line)
	{
		if (!ft_strchr("01NSEW ", *line))
		{
			valid = false;
			break ;
		}
		if (ft_strchr("NSEW", *line))
			(*player_count)++;
		line++;
	}
	if (*player_count > 1)
		valid = false;
	return (valid && (*player_count <= 1));
}

void	initialize_static_variables(t_map_info *map_info)
{
	if (!map_info->map_lines)
		map_info->map_lines = NULL;
	if (!map_info->map_height)
		map_info->map_height = 0;
	if (!map_info->player_count)
		map_info->player_count = 0;
}

void	handle_map_line(t_cub3d *game, char *line, t_map_info *map_info)
{
	char	**new_map_lines;
	int		line_length;

	if (line[0] == '\0')
	{
		if (map_info->map_height > 0)
			map_info->map_ended = true;
		return ;
	}
	if (map_info->map_ended && line[0] != '\0')
		error_exit2(game, "Error: Discontinuous map/Wrong config", line);
	if (!is_valid_map_line(line, &map_info->player_count))
		error_exit2(game, "Error: Invalid map/config", line);
	new_map_lines = allocate_new_map_lines(game,
			map_info->map_lines, map_info->map_height);
	add_line_to_map(game, new_map_lines, line, map_info->map_height);
	map_info->map_lines = new_map_lines;
	map_info->map_height++;
	game->map = map_info->map_lines;
	game->map_height = map_info->map_height;
	line_length = ft_strlen(line);
	if (line_length > game->map_width)
		game->map_width = line_length;
}
