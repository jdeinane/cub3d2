/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubaldo <jubaldo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:01:11 by jubaldo           #+#    #+#             */
/*   Updated: 2024/06/05 15:11:17 by jubaldo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void parse_color(t_color *color, char *line)
{
	char **tokens;
	int rgb_values[3];

	if (!line)
	{
		printf("Error: Null pointer provided for color line\n");
		exit(EXIT_FAILURE);
	}
	tokens = ft_split(line + 2, ',');
	int num_tokens = 0;
	while (tokens[num_tokens])
		num_tokens++;
	if (num_tokens != 3)
	{
		free_tokens(tokens);
		printf("Error: Invalid color format, must have exactly three RGB values\n");
	}
	for (int i = 0; i < 3; i++)
	{
		if (!tokens[i] || !*tokens[i])
		{
			free_tokens(tokens);
			printf("Error: Invalid color format, missing RGB values\n");
			exit(EXIT_FAILURE);
		}
		rgb_values[i] = ft_atoi(tokens[i]);
		if (rgb_values[i] < 0 || rgb_values[i] > 255)
		{
			free_tokens(tokens);
			printf("Error: RGB values out of bounds [0-255]\n");
			exit(EXIT_FAILURE);
		}
	}
	color->r = rgb_values[0];
	color->g = rgb_values[1];
	color->b = rgb_values[2];
	free_tokens(tokens);
}
