/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_player.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubaldo <jubaldo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 17:22:58 by jubaldo           #+#    #+#             */
/*   Updated: 2024/06/13 17:51:14 by jubaldo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	set_north_direction(t_cub3d *game)
{
	game->player.dir_x = 0;
	game->player.dir_y = -1;
	game->player.plane_x = 0.66;
	game->player.plane_y = 0;
}

void	set_south_direction(t_cub3d *game)
{
	game->player.dir_x = 0;
	game->player.dir_y = 1;
	game->player.plane_x = -0.66;
	game->player.plane_y = 0;
}

void	set_west_direction(t_cub3d *game)
{
	game->player.dir_x = -1;
	game->player.dir_y = 0;
	game->player.plane_x = 0;
	game->player.plane_y = -0.66;
}

void	set_east_direction(t_cub3d *game)
{
	game->player.dir_x = 1;
	game->player.dir_y = 0;
	game->player.plane_x = 0;
	game->player.plane_y = 0.66;
}

void	set_player_direction(t_cub3d *game, char direction)
{
	if (direction == 'N')
		set_north_direction(game);
	else if (direction == 'S')
		set_south_direction(game);
	else if (direction == 'W')
		set_west_direction(game);
	else if (direction == 'E')
		set_east_direction(game);
}
