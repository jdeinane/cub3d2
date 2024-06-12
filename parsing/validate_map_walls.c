/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_walls.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubaldo <jubaldo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 12:38:07 by jubaldo           #+#    #+#             */
/*   Updated: 2024/06/12 17:18:21 by jubaldo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	check_surroundings(t_cub3d *game, int x, int y)
{
	if (y > 0 && !is_valid_surrounding(game->map[y - 1][x]))
		error_exit(game, "Error: Invalid player position (above).");
	if (y < game->map_height - 1 && \
		!is_valid_surrounding(game->map[y + 1][x]))
		error_exit(game, "Error: Invalid player position (below).");
	if (x > 0 && !is_valid_surrounding(game->map[y][x - 1]))
		error_exit(game, "Error: Invalid player position (left).");
	if (x < ft_strlen(game->map[y]) - 1 && \
		!is_valid_surrounding(game->map[y][x + 1]))
		error_exit(game, "Error: Invalid player position (right).");
}

static void	check_player_position_surroundings(t_cub3d *game)
{
	int		x;
	int		y;
	int		len;
	char	ch;

	y = 0;
	while (y < game->map_height)
	{
		len = ft_strlen(game->map[y]);
		x = 0;
		while (x < len)
		{
			ch = game->map[y][x];
			if (ch == 'N' || ch == 'E' || ch == 'S' || ch == 'W')
				check_surroundings(game, x, y);
			x++;
		}
		y++;
	}
}

static void	check_horizontal_boundaries(t_cub3d *game)
{
	int	x;

	x = 0;
	while (game->map[0][x] != '\0')
	{
		if (game->map[0][x] != '1' && game->map[0][x] != ' ')
			error_exit(game, "Error: Map is not enclosed (top row)");
		x++;
	}
	while (game->map[game->map_height - 1][x] != '\0')
	{
		if (game->map[game->map_height - 1][x] != '1' && \
			game->map[game->map_height - 1][x] != ' ')
			error_exit(game, "Error: Map is not enclosed (bottom row)");
		x++;
	}
}

static void	check_vertical_boundaries(t_cub3d *game)
{
	int y, x, row_length;

	for (y = 0; y < game->map_height; y++)
	{
		row_length = ft_strlen(game->map[y]);
		for (x = 0; x < row_length; x++)
		{
			if (game->map[y][x] != ' ')
				break ;
		}
		if (game->map[y][x] == '0')
			error_exit(game, "Error: Map has '0' following spaces at the start, not properly surrounded by walls.");
		if (row_length > 0 && (game->map[y][row_length - 1] != '1' && game->map[y][row_length - 1] != ' '))
			error_exit(game, "Error: Map is not surrounded by walls (right boundary)");
		for (x = row_length - 1; x >= 0; x--)
		{
			if (game->map[y][x] != ' ')
				break ;
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
					error_exit(game, "Error: '0' in extended row section is not properly surrounded by '1' or space");
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
				if (game->map[y][x] == '0' && \
					(!is_enclosed(game->map[y - 1][x]) || !is_enclosed(game->map[y + 1][x])))
					error_exit(game, "Error: '0' in extended row section is not properly surrounded by '1' or space");
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

static void check_zeroes_above_in_second_row(t_cub3d *game)
{
	int x;
	int first_row_length = ft_strlen(game->map[0]);
	int second_row_length = ft_strlen(game->map[1]);

	for (x = 0; x < second_row_length; x++)
	{
		if (game->map[1][x] == '0')
		{
			if (x >= first_row_length || game->map[0][x] == ' ')
				error_exit(game, "Error: '0' in the second row has an invalid space directly above it.");
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
	check_zeroes_above_in_second_row(game);
	check_extended_row_enclosures(game);
	check_player_position_surroundings(game);
}
