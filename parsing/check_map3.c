/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubaldo <jubaldo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 15:52:27 by jubaldo           #+#    #+#             */
/*   Updated: 2024/07/22 16:08:29 by jubaldo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool	is_row_completely_empty(const char *row)
{
	while (*row)
	{
		if (!ft_isspace((unsigned char)*row))
			return (false);
		row++;
	}
	return (true);
}

void	check_left_boundary2(t_cub3d *game, int y)
{
	int	len;

	len = ft_strlen(game->map[y]);
	if (len > 0 && (game->map[y][0] != '1' && game->map[y][0] != ' '))
		error_exit(game, "Error: Section left boundary not enclosed.");
}

void	check_right_boundary2(t_cub3d *game, int y)
{
	int	len;

	len = ft_strlen(game->map[y]);
	if (len > 0 && (game->map[y][len - 1] != '1' && \
			game->map[y][len - 1] != ' '))
		error_exit(game, "Error: Section right boundary not enclosed.");
}

void	check_top_bottom_boundary2(t_cub3d *game, int y, int len)
{
	int	x;

	x = 0;
	while (x < len)
	{
		if (game->map[y][x] != '1' && game->map[y][x] != ' ')
			error_exit(game, "Error: Section of the map \
			is not properly enclosed.");
		x++;
	}
}

void	validate_section(t_cub3d *game, int start, int end)
{
	int	y;
	int	len;

	y = start;
	while (y <= end)
	{
		len = ft_strlen(game->map[y]);
		if (y == start || y == end)
			check_top_bottom_boundary2(game, y, len);
		check_left_boundary2(game, y);
		check_right_boundary2(game, y);
		y++;
	}
}
