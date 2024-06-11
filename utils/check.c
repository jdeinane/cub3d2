/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubaldo <jubaldo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 22:19:42 by jubaldo           #+#    #+#             */
/*   Updated: 2024/06/11 13:11:46 by jubaldo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_within_bounds(t_cub3d *game, double x, double y)
{
	return (x >= 0 && x < game->map_width && y >= 0 && y < game->map_height);
}

bool	is_enclosed(char c)
{
	return c == '1' || c == ' ';
}

bool	is_valid_surrounding(char c)
{
	return c == '0' || c == '1';
}
