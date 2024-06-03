/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cub3d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubaldo <jubaldo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 22:05:24 by jubaldo           #+#    #+#             */
/*   Updated: 2024/06/03 13:41:58 by jubaldo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	init_colors(t_cub3d *game)
{
	game->floor_color = (t_color){0, 0, 0};
	game->ceiling_color = (t_color){255, 255, 255};
}

static void	init_mlx(t_cub3d *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		error_exit(game, "Error: Error initializing mlx");
}

void	init_cub3d(t_cub3d *game)
{
	char	*texture_paths[NUM_TEXTURES];

	texture_paths[0] = PATH_NORTH;
	texture_paths[1] = PATH_SOUTH;
	texture_paths[2] = PATH_EAST;
	texture_paths[3] = PATH_WEST;
	game->mlx = NULL;
	game->win = NULL;
	game->img = NULL;
	game->img_data = NULL;
	game->win_width = WIN_WIDTH;
	game->win_height = WIN_HEIGHT;
	init_mlx(game);
	init_colors(game);
	game->map = NULL;
	game->map_width = 0;
	game->map_height = 0;
	ft_memset(&game->keys, 0, sizeof(t_keys));
}
