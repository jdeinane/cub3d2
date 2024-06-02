/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubaldo <jubaldo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 21:21:45 by jubaldo           #+#    #+#             */
/*   Updated: 2024/05/31 14:28:45 by jubaldo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_tokens(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

static void	free_images(t_cub3d *game)
{
	int	i;

	i = 0;
	if (game->img)
		mlx_destroy_image(game->mlx, game->img);
	while (i < NUM_TEXTURES)
	{
		if (game->textures[i].img)
			mlx_destroy_image(game->mlx, game->textures[i].img);
		i++;
	}
}

void	free_resources(t_cub3d *game)
{
	int	i;

	i = 0;
	free_images(game);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->map)
	{
		while (i < game->map_height)
		{
			if (game->map[i])
				free(game->map[i]);
			i++;
		}
		free(game->map);
	}
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
}
