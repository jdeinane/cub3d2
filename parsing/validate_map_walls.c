/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_walls.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubaldo <jubaldo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 12:38:07 by jubaldo           #+#    #+#             */
/*   Updated: 2024/07/19 19:40:37 by jubaldo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static bool is_row_completely_empty(const char *row)
{
	while (*row)
	{
		if (!isspace((unsigned char)*row))
			return false;
		row++;
	}
	return true;
}

static void validate_section(t_cub3d *game, int start, int end)
{
	int max_length = 0;

	for (int y = start; y <= end; y++)
	{
		int length = ft_strlen(game->map[y]);
		if (length > max_length)
			max_length = length;
	}
	for (int y = start; y <= end; y++)
	{
		int length = ft_strlen(game->map[y]);

		if (y == start || y == end)
		{
			for (int x = 0; x < length; x++)
			{
				if (game->map[y][x] != '1' && game->map[y][x] != ' ')
					error_exit(game, "Error: Section of the map is not properly enclosed.");
			}
		}
		if (length > 0 && (game->map[y][0] != '1' && game->map[y][0] != ' '))
			error_exit(game, "Error: Section left boundary is not properly enclosed.");
		if (length > 0 && (game->map[y][length - 1] != '1' && game->map[y][length - 1] != ' '))
			error_exit(game, "Error: Section right boundary is not properly enclosed.");
	}
}

void check_for_multiple_sections(t_cub3d *game)
{
	int current_section_start = -1;
	bool in_section = false;

	for (int y = 0; y <= game->map_height; y++)
	{
		if (y == game->map_height || is_row_completely_empty(game->map[y]))
		{
			if (in_section)
			{
				validate_section(game, current_section_start, y - 1);
				in_section = false;
			}
		}
		else
		{
			if (!in_section)
			{
				current_section_start = y;
				in_section = true;
			}
		}
	}
}

void validate_map(t_cub3d *game)
{
	if (game->map_height < 2)
		error_exit(game, "Error: Map must have at least two rows");
	check_horizontal_boundaries(game);
	check_vertical_boundaries(game);
	check_zeroes_below_in_second_to_last_row(game);
	check_extended_row_enclosures(game);
	check_for_multiple_sections(game);
}
