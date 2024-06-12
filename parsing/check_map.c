/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubaldo <jubaldo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 20:47:43 by jubaldo           #+#    #+#             */
/*   Updated: 2024/06/12 21:03:14 by jubaldo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	check_left_boundary(t_cub3d *game, int y)
{
	int	x;
	int	row_length;

	x = 0;
	row_length = ft_strlen(game->map[y]);
	while (x < row_length && game->map[y][x] == ' ')
		x++;
	if (x < row_length && game->map[y][x] == '0')
		error_exit(game, "Error: Map not enclosed at the start.");
}

static void	check_right_boundary(t_cub3d *game, int y)
{
	int	x;
	int	row_length;

	row_length = ft_strlen(game->map[y]);
	x = row_length - 1;
	while (x >= 0 && game->map[y][x] == ' ')
		x--;
	if (x >= 0 && game->map[y][x] == '0')
		error_exit(game, "Error: Map not enclosed in the end.");
	if (row_length > 0 && (game->map[y][row_length - 1] != '1' \
		&& game->map[y][row_length - 1] != ' '))
		error_exit(game, "Error: Map not enclosed (right boundary)");
}

void	check_vertical_boundaries(t_cub3d *game)
{
	int	y;

	y = 0;
	while (y < game->map_height)
	{
		check_left_boundary(game, y);
		check_right_boundary(game, y);
		y++;
	}
}

static void	check_surrounding_positions(t_cub3d *game, int y, int x)
{
	if (y == 0 || y == game->map_height - 1 || x == 0 || \
		x == ft_strlen(game->map[y]) - 1)
		error_exit(game, "Error: Player position on map boundary.");
	if (y > 0 && !is_valid_surrounding(game->map[y - 1][x]))
		error_exit(game, "Error: Invalid player starting position (above).");
	if (y < game->map_height - 1 && !is_valid_surrounding(game->map[y + 1][x]))
		error_exit(game, "Error: Invalid player starting position (below).");
	if (x > 0 && !is_valid_surrounding(game->map[y][x - 1]))
		error_exit(game, "Error: Invalid player starting position (left).");
	if (x < ft_strlen(game->map[y]) - 1 && \
		!is_valid_surrounding(game->map[y][x + 1]))
		error_exit(game, "Error: Invalid player starting position (right).");
}

void	check_player_position_surroundings(t_cub3d *game)
{
	int		x;
	int		y;
	char	ch;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < ft_strlen(game->map[y]))
		{
			ch = game->map[y][x];
			if (ch == 'N' || ch == 'E' || ch == 'S' || ch == 'W')
				check_surrounding_positions(game, y, x);
			x++;
		}
		y++;
	}
}
