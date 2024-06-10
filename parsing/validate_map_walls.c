/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_walls.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubaldo <jubaldo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 12:38:07 by jubaldo           #+#    #+#             */
/*   Updated: 2024/06/10 19:57:51 by jubaldo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

		IL FAUT GERER LE CAS OU NSEW EST SUR LE BORD !!! 

static bool is_enclosed(char c)
{
	return c == '1' || c == ' ';
}

// static void check_vertical_boundaries_and_row_lengths(t_cub3d *game)
// {
// 	int y;
// 	int first_row_length = ft_strlen(game->map[0]);

// 	for (y = 1; y < game->map_height - 1; y++)
// 	{
// 		int current_row_length = ft_strlen(game->map[y]);
// 		if (current_row_length < first_row_length)
// 		{
// 			if (game->map[y][0] != '1' || game->map[y][current_row_length - 1] != '1')
// 				error_exit(game, "Error: Short row is not properly enclosed by walls");
// 		}
// 		else if (current_row_length > first_row_length)
// 			error_exit(game, "Error: Row is longer than the first row without proper enclosure");
// 	}
// }

static void check_horizontal_boundaries(t_cub3d *game)
{
	int x;

	for (x = 0; game->map[0][x] != '\0'; x++)
	{
		if (game->map[0][x] != '1' && game->map[0][x] != ' ')
			error_exit(game, "Error: Map is not surrounded by walls (top row)");
	}
	for (x = 0; game->map[game->map_height - 1][x] != '\0'; x++)
	{
		if (game->map[game->map_height - 1][x] != '1' && game->map[game->map_height - 1][x] != ' ')
			error_exit(game, "Error: Map is not surrounded by walls (bottom row)");
	}
}

static void check_vertical_boundaries(t_cub3d *game)
{
	int y, x, row_length;

	for (y = 0; y < game->map_height; y++)
	{
		row_length = ft_strlen(game->map[y]);
		for (x = 0; x < row_length; x++)
		{
			if (game->map[y][x] != ' ')
				break;
		}
		if (game->map[y][x] == '0')
			error_exit(game, "Error: Map has '0' following spaces at the start, not properly surrounded by walls.");
		if (row_length > 0 && (game->map[y][row_length - 1] != '1' && game->map[y][row_length - 1] != ' '))
		{
			error_exit(game, "Error: Map is not surrounded by walls (right boundary)");
		}
		for (x = row_length - 1; x >= 0; x--)
		{
			if (game->map[y][x] != ' ')
				break;
		}
		if (game->map[y][x] == '0')
			error_exit(game, "Error: Map has '0' before spaces at the end, not properly surrounded by walls.");
	}
}

static void check_long_row_zeroes(t_cub3d *game)
{
	int x, y;

	for (y = 1; y < game->map_height - 1; y++)
	{
		for (x = ft_strlen(game->map[0]); x < ft_strlen(game->map[y]); x++)
		{
			if (game->map[y][x] == '0' && (game->map[y - 1][x] != '1' || game->map[y + 1][x] != '1'))
				error_exit(game, "Error: '0' in extended row must have '1' or space both above and below");
		}
	}
}

static void check_extended_row_enclosures(t_cub3d *game)
{
	for (int y = 1; y < game->map_height; y++)
	{
		int prev_length = ft_strlen(game->map[y - 1]);
		int current_length = ft_strlen(game->map[y]);

		int start_index = prev_length;
		if (current_length > prev_length)
		{
			for (int x = start_index; x < current_length; x++)
			{
				if (game->map[y][x] == '0' &&
					(!is_enclosed(game->map[y - 1][x]) || (y + 1 < game->map_height && !is_enclosed(game->map[y + 1][x]))))
				{
					error_exit(game, "Error: '0' in extended row section is not properly surrounded by '1' or space");
				}
			}
		}
	}
	for (int y = 0; y < game->map_height - 1; y++)
	{
		int current_length = ft_strlen(game->map[y]);
		int next_length = ft_strlen(game->map[y + 1]);

		int start_index = next_length;
		if (current_length > next_length)
		{
			for (int x = start_index; x < current_length; x++)
			{
				if (game->map[y][x] == '0' &&
					(!is_enclosed(game->map[y - 1][x]) || !is_enclosed(game->map[y + 1][x])))
				{
					error_exit(game, "Error: '0' in extended row section is not properly surrounded by '1' or space");
				}
			}
		}
	}
}

static void check_zeroes_below_in_second_to_last_row(t_cub3d *game)
{
	int x;
	int second_to_last_row_index = game->map_height - 2;
	int last_row_length = ft_strlen(game->map[game->map_height - 1]);

	for (x = 0; x < ft_strlen(game->map[second_to_last_row_index]); x++)
	{
		if (game->map[second_to_last_row_index][x] == '0')
		{
			if (x >= last_row_length || game->map[game->map_height - 1][x] != '1')
				error_exit(game, "Error: '0' in the second-to-last row is not supported by '1' directly below it in the last row");
		}
	}
}



void validate_map(t_cub3d *game)
{
	if (game->map_height < 2)
		error_exit(game, "Error: Map must have at least two rows");
	check_horizontal_boundaries(game);
	// check_vertical_boundaries_and_row_lengths(game);
	check_vertical_boundaries(game);
	check_long_row_zeroes(game);
	check_zeroes_below_in_second_to_last_row(game);
	check_extended_row_enclosures(game);
}
