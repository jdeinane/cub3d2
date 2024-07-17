/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubaldo <jubaldo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:01:11 by jubaldo           #+#    #+#             */
/*   Updated: 2024/07/17 15:41:13 by jubaldo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	validate_rgb_component(char *component)
{
	int		value;
	char	*endptr;

	if (*component == '\0')
		return (-1);
	value = ft_strtol(component, &endptr, 10);
	if (*endptr != '\0' || value < 0 || value > 255)
		return (-1);
	return (value);
}

static void	check_rgb_components(char **rgb, char *line, t_cub3d *game)
{
	if (!rgb[0] || !rgb[1] || !rgb[2])
	{
		free_tokens(rgb);
		error_exit2(game, "Error: Incorrect number of RGB components", line);
	}
}

void	parse_color(t_cub3d *game, char *line)
{
	char	**rgb;
	int		r;
	int		g;
	int		b;

	if (!line || (line[0] != 'F' && line[0] != 'C'))
		error_exit(game, "Error: Invalid color line format");
	rgb = ft_split(line + 1, ',');
	if (!rgb)
		error_exit(game, "Error: Memory allocation failed");
	check_rgb_components(rgb, line, game);
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
