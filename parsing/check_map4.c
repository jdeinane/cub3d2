/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubaldo <jubaldo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 15:55:32 by jubaldo           #+#    #+#             */
/*   Updated: 2024/07/22 16:02:58 by jubaldo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	process_section(t_cub3d *game, bool *in_section,
							int *current_section_start, int y)
{
	if (*in_section)
	{
		validate_section(game, *current_section_start, y - 1);
		*in_section = false;
	}
}

void	start_new_section(bool *in_section,
							int *current_section_start, int y)
{
	if (!*in_section)
	{
		*current_section_start = y;
		*in_section = true;
	}
}

void	check_for_multiple_sections(t_cub3d *game)
{
	int		current_section_start;
	bool	in_section;
	int		y;

	current_section_start = -1;
	in_section = false;
	y = 0;
	while (y <= game->map_height)
	{
		if (y == game->map_height || is_row_completely_empty(game->map[y]))
			process_section(game, &in_section, &current_section_start, y);
		else
			start_new_section(&in_section, &current_section_start, y);
		y++;
	}
}

void	check_left_space(t_cub3d *game, int y, int x)
{
	if (x > 0 && ft_isspace(game->map[y][x - 1]))
	{
		if (x == 1 || !is_valid_surrounding(game->map[y][x - 2]))
			error_exit(game, "Error: Unprotected space to the left of '0'.");
	}
}

void	check_right_space(t_cub3d *game, int y, int x, int length)
{
	if (x < length - 1 && ft_isspace(game->map[y][x + 1]))
	{
		if (x == length - 2 || !is_valid_surrounding(game->map[y][x + 2]))
			error_exit(game, "Error: Unprotected space to the right of '0'.");
	}
}
