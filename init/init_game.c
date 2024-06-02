/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubaldo <jubaldo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 16:10:23 by jubaldo           #+#    #+#             */
/*   Updated: 2024/05/30 00:50:22 by jubaldo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	init_window(t_cub3d *game)
{
	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
	if (!game->win)
		error_exit(game, "Error: Error creating window");
}

void	init_game(t_cub3d *game)
{
	init_window(game);
	game->img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!game->img)
		error_exit(game, "Error: Error creating image");
	game->img_data = (int *)mlx_get_data_addr(game->img, &game->bpp, \
					&game->size_line, &game->endian);
	if (!game->img_data)
		error_exit(game, "Error: Error getting image data");
	init_player(game);
}
