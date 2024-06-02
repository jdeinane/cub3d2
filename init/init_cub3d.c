/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cub3d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubaldo <jubaldo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 22:05:24 by jubaldo           #+#    #+#             */
/*   Updated: 2024/05/31 14:37:23 by jubaldo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	init_textures(t_cub3d *game, char *texture_paths[])
{
	int	i;

	i = 0;
	while (i < NUM_TEXTURES)
	{
		game->textures[i].img = mlx_xpm_file_to_image(game->mlx, \
			texture_paths[i], &game->textures[i].width, \
			&game->textures[i].height);
		if (game->textures[i].img == NULL)
		{
			printf("Failed to load texture: %s\n", texture_paths[i]);
			perror("mlx_xpm_file_to_image");
			error_exit(game, "Error: Texture not loaded");
		}
		game->textures[i].data = (int *)mlx_get_data_addr \
			(game->textures[i].img, &game->textures[i].bpp, \
			&game->textures[i].size_line, \
			&game->textures[i].endian);
		if (game->textures[i].data == NULL)
		{
			perror("mlx_get_data_addr");
			error_exit(game, "Error: Failed to get texture data");
		}
		i++;
	}
}

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
	init_textures(game, texture_paths);
	init_colors(game);
	game->map = NULL;
	game->map_width = 0;
	game->map_height = 0;
	ft_memset(&game->keys, 0, sizeof(t_keys));
}
