/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_walls.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubaldo <jubaldo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 12:38:07 by jubaldo           #+#    #+#             */
/*   Updated: 2024/06/09 18:11:07 by jubaldo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	check_horizontal_walls(t_cub3d *game)
{
	int x;

	for (x = 0; x < game->map_width; x++)
	{
		if (game->map[0][x] != '1' || game->map[game->map_height - 1][x] != '1')
			error_exit(game, "Error: Map is not surrounded by walls (horizontal check)");
	}
}

static void	check_vertical_walls(t_cub3d *game)
{
	int y;

	for (y = 0; y < game->map_height; y++)
	{
		if (game->map[y][0] != '1' || game->map[y][game->map_width - 1] != '1')
			error_exit(game, "Error: Map is not surrounded by walls (vertical check)");
	}
}

static void	check_map_width(t_cub3d *game)
{
	int y;
	int width;

	width = ft_strlen(game->map[0]);
	for (y = 1; y < game->map_height; y++)
	{
		if ((int)ft_strlen(game->map[y]) != width)
			error_exit(game, "Error: Map rows have inconsistent widths");
	}
	game->map_width = width;
}

static void	validate_rectangular_map(t_cub3d *game)
{
	check_map_width(game);
	check_horizontal_walls(game);
	check_vertical_walls(game);
}

static void validate_non_rectangular_map(t_cub3d *game)
{
	int y, x;
	int row_length;

	for (y = 0; y < game->map_height; y++)
	{
		row_length = ft_strlen(game->map[y]);
		for (x = 0; x < row_length; x++)
		{
			// Skip spaces inside the map
			if (game->map[y][x] == ' ')
				continue;

			// Check edges
			if ((y == 0 || y == game->map_height - 1 || x == 0 || x == row_length - 1) && game->map[y][x] != '1')
			{
				error_exit(game, "Error: Map is not surrounded by walls (non-rectangular check)");
			}

			// Check spaces that are adjacent to walls
			if (game->map[y][x] == '0' || game->map[y][x] == 'N' || game->map[y][x] == 'S' || game->map[y][x] == 'E' || game->map[y][x] == 'W')
			{
				if (x > 0 && game->map[y][x - 1] == ' ')
					error_exit(game, "Error: Map contains invalid spaces");
				if (x < row_length - 1 && game->map[y][x + 1] == ' ')
					error_exit(game, "Error: Map contains invalid spaces");
				if (y > 0 && x < (int)ft_strlen(game->map[y - 1]) && game->map[y - 1][x] == ' ')
					error_exit(game, "Error: Map contains invalid spaces");
				if (y < game->map_height - 1 && x < (int)ft_strlen(game->map[y + 1]) && game->map[y + 1][x] == ' ')
					error_exit(game, "Error: Map contains invalid spaces");

				// Ensure '0' is enclosed by '1' above and below
				if (y > 0 && game->map[y - 1][x] != '1')
					error_exit(game, "Error: '0' cell not enclosed by '1' above");
				if (y < game->map_height - 1 && game->map[y + 1][x] != '1')
					error_exit(game, "Error: '0' cell not enclosed by '1' below");
			}
		}
	}
}

static int is_rectangular_map(t_cub3d *game)
{
	int width = ft_strlen(game->map[0]);
	for (int y = 1; y < game->map_height; y++)
	{
		if ((int)ft_strlen(game->map[y]) != width)
			return 0;
	}
	return 1;
}

void validate_map(t_cub3d *game)
{
	if (is_rectangular_map(game))
		validate_rectangular_map(game);
	else
		validate_non_rectangular_map(game);
}
