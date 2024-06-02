/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubaldo <jubaldo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:01:11 by jubaldo           #+#    #+#             */
/*   Updated: 2024/06/02 19:35:11 by jubaldo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void parse_color(t_color *color, char *line)
{
	t_cub3d game;
	char **tokens;
	int rgb_values[3];

	if (!line)
		error_exit(&game, "Error: Null pointer provided for color line");
	tokens = ft_split(line + 2, ',');
	if (!tokens)
		error_exit(&game, "Error: Memory allocation failed for color tokens");
	for (int i = 0; i < 3; i++)
	{
		if (!tokens[i] || !*tokens[i])
		{
			free_tokens(tokens);
			error_exit(&game, "Error: Invalid color format, missing RGB values");
		}
		rgb_values[i] = ft_atoi(tokens[i]);
		if (rgb_values[i] < 0 || rgb_values[i] > 255)
		{
			free_tokens(tokens);
			error_exit(&game, "Error: RGB values out of bounds [0-255]");
		}
	}
	color->r = rgb_values[0];
	color->g = rgb_values[1];
	color->b = rgb_values[2];
	free_tokens(tokens);
}
