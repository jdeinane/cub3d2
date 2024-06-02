/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubaldo <jubaldo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 22:19:42 by jubaldo           #+#    #+#             */
/*   Updated: 2024/05/24 22:20:12 by jubaldo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_within_bounds(t_cub3d *game, double x, double y)
{
	return (x >= 0 && x < game->map_width && y >= 0 && y < game->map_height);
}
