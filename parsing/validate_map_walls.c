/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_walls.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubaldo <jubaldo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 12:38:07 by jubaldo           #+#    #+#             */
/*   Updated: 2024/07/22 15:57:55 by jubaldo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	check_vertical_spaces(t_cub3d *game, int y, int x)
{
	if (y > 0 && x < ft_strlen(game->map[y - 1]) && \
		ft_isspace(game->map[y - 1][x]))
	{
		if (y == 1 || !is_valid_surrounding(game->map[y - 2][x]))
			error_exit(game, "Error: Unprotected space above '0'.");
	}
	if (y < game->map_height - 1 && x < ft_strlen(game->map[y + 1]) && \
		ft_isspace(game->map[y + 1][x]))
	{
		if (y == game->map_height - 2 || \
			!is_valid_surrounding(game->map[y + 2][x]))
			error_exit(game, "Error: Unprotected space below '0'.");
	}
}

static void	check_unprotected_spaces(t_cub3d *game)
{
	int	y;
	int	x;
	int	len;

	y = 0;
	while (y < game->map_height)
	{
		len = ft_strlen(game->map[y]);
		x = 0;
		while (x < len)
		{
			if (game->map[y][x] == '0')
			{
				check_left_space(game, y, x);
				check_right_space(game, y, x, len);
				check_vertical_spaces(game, y, x);
			}
			x++;
		}
		y++;
	}
}

void	validate_map(t_cub3d *game)
{
	if (game->map_height < 2)
		error_exit(game, "Error: Map must have at least two rows");
	check_horizontal_boundaries(game);
	check_vertical_boundaries(game);
	check_zeroes_below_in_second_to_last_row(game);
	check_extended_row_enclosures(game);
	check_for_multiple_sections(game);
	check_unprotected_spaces(game);
}
