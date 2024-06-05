/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubaldo <jubaldo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:01:11 by jubaldo           #+#    #+#             */
/*   Updated: 2024/06/05 18:11:14 by jubaldo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int validate_rgb_component(char *component)
{
	int value;
	char *endptr;

	if (*component == '\0')
		return -1;

	value = strtol(component, &endptr, 10);
	if (*endptr != '\0' || value < 0 || value > 255)
		return -1;

	return value;
}

void parse_color(t_cub3d *game, char *line)
{
	char **rgb;
	int r, g, b;

	if (!line || (line[0] != 'F' && line[0] != 'C'))
		error_exit(game, "Error: Invalid color line format");
	rgb = ft_split(line + 1, ',');
	if (!rgb)
		error_exit(game, "Error: Memory allocation failed");
	if (!rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
	{
		free_tokens(rgb);
		error_exit2(game, "Error: Incorrect number of RGB components", line);
	}
	r = validate_rgb_component(rgb[0]);
	g = validate_rgb_component(rgb[1]);
	b = validate_rgb_component(rgb[2]);
	if (r == -1 || g == -1 || b == -1) 
	{
		free_tokens(rgb);
		error_exit2(game, "Error: Invalid RGB values", line);
	}
	if (line[0] == 'F')
		game->floor_color = (t_color){r, g, b};
	else
		game->ceiling_color = (t_color){r, g, b};
	free_tokens(rgb);
}
