/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perform_raycasting.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubaldo <jubaldo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 20:33:06 by jubaldo           #+#    #+#             */
/*   Updated: 2024/05/27 22:02:28 by jubaldo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	perform_raycasting(t_cub3d *game)
{
	int		x;
	t_ray	ray;

	x = 0;
	while (x < game->win_width)
	{
		init_ray(game, &ray, x);
		perform_dda(game, &ray);
		calc_perp_wall_dist(game, &ray);
		calc_line_height(game, &ray);
		draw_line(game, x, &ray);
		x++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}
