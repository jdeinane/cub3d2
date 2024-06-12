/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubaldo <jubaldo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 20:57:09 by jubaldo           #+#    #+#             */
/*   Updated: 2024/06/12 21:03:28 by jubaldo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	check_extended_downward(t_cub3d *game, int y,
			int prev_length, int current_length)
{
	int	x;

	x = prev_length;
	while (x < current_length)
	{
		if (game->map[y][x] == '0' &&
			(!is_enclosed(game->map[y - 1][x]) || \
			(y + 1 < game->map_height && !is_enclosed(game->map[y + 1][x]))))
			error_exit(game, "Error: Map not enclosed (extended row)");
		x++;
	}
}

static void	check_extended_upward(t_cub3d *game, int y,
			int current_length, int next_length)
{
	int	x;

	x = next_length;
	while (x < current_length)
	{
		if (game->map[y][x] == '0' &&
			(!is_enclosed(game->map[y - 1][x]) || \
			!is_enclosed(game->map[y + 1][x])))
			error_exit(game, "Error: Map not enclosed (extended row)");
		x++;
	}
}

void	check_extended_row_enclosures(t_cub3d *game)
{
	int	y;
	int	prev_length;
	int	current_length;
	int	next_length;

	y = 1;
	while (y < game->map_height)
	{
		prev_length = ft_strlen(game->map[y - 1]);
		current_length = ft_strlen(game->map[y]);
		if (current_length > prev_length)
			check_extended_downward(game, y, prev_length, current_length);
		y++;
	}
	y = 0;
	while (y < game->map_height - 1)
	{
		current_length = ft_strlen(game->map[y]);
		next_length = ft_strlen(game->map[y + 1]);
		if (current_length > next_length)
			check_extended_upward(game, y, current_length, next_length);
		y++;
	}
}

void	check_zeroes_below_in_second_to_last_row(t_cub3d *game)
{
	int	x;
	int	second_to_last_row_index;
	int	last_row_length;

	second_to_last_row_index = game->map_height - 2;
	last_row_length = ft_strlen(game->map[game->map_height - 1]);
	x = 0;
	while (x < ft_strlen(game->map[second_to_last_row_index]))
	{
		if (game->map[second_to_last_row_index][x] == '0')
		{
			if (x >= last_row_length || \
			game->map[game->map_height - 1][x] != '1')
				error_exit(game, \
				"Error: Map not enclosed (in 2nd to last row)");
		}
		x++;
	}
}

void	check_horizontal_boundaries(t_cub3d *game)
{
	int	x;

	x = 0;
	while (game->map[0][x] != '\0')
	{
		if (game->map[0][x] != '1' && game->map[0][x] != ' ')
			error_exit(game, "Error: Map is not enclosed (top row)");
		x++;
	}
	x = 0;
	while (game->map[game->map_height - 1][x] != '\0')
	{
		if (game->map[game->map_height - 1][x] != '1' &&
			game->map[game->map_height - 1][x] != ' ')
			error_exit(game, "Error: Map is not enclosed (bottom row)");
		x++;
	}
}
