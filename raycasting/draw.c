/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubaldo <jubaldo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 20:20:05 by jubaldo           #+#    #+#             */
/*   Updated: 2024/05/27 22:12:02 by jubaldo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	get_texture_index(t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->ray_dir_x > 0)
			return (0);
		else
			return (1);
	}
	else
	{
		if (ray->ray_dir_y > 0)
			return (2);
		else
			return (3);
	}
}

void	init_draw_params(t_cub3d *game, t_ray *ray, t_draw_params *params)
{
	params->texture_index = get_texture_index(ray);
	params->wall_x = calculate_wall_x(game, ray);
	params->texture_x = calculate_texture_x(params->wall_x, ray);
	params->step = 1.0 * TEX_HEIGHT / ray->line_height;
	params->texture_pos = (ray->draw_start - game->win_height / 2 + \
		ray->line_height / 2) * params->step;
}

void	draw_line(t_cub3d *game, int x, t_ray *ray)
{
	t_draw_params	params;
	int				texture_y;
	int				y;

	init_draw_params(game, ray, &params);
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		texture_y = (int)params.texture_pos & (TEX_HEIGHT - 1);
		params.texture_pos += params.step;
		params.color = game->textures[params.texture_index].data[TEX_HEIGHT * \
					texture_y + params.texture_x];
		if (ray->side == 1)
			params.color = (params.color >> 1) & 8355711;
		game->img_data[y * game->win_width + x] = params.color;
		y++;
	}
}

void	draw_floor_and_ceiling(t_cub3d *game)
{
	int	x;
	int	y;

	y = -1;
	while (++y < game->win_height / 2)
	{
		x = -1;
		while (++x < game->win_width)
			game->img_data[y * game->win_width + x] = \
			(game->ceiling_color.r << 16) | (game->ceiling_color.g << 8) \
				| game->ceiling_color.b;
	}
	y = game->win_height / 2 - 1;
	while (++y < game->win_height)
	{
		x = -1;
		while (++x < game->win_width)
			game->img_data[y * game->win_width + x] = \
			(game->floor_color.r << 16) | (game->floor_color.g << 8) \
				| game->floor_color.b;
	}
}
