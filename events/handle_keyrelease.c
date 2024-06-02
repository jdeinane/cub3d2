/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keyrelease.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubaldo <jubaldo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 17:12:07 by jubaldo           #+#    #+#             */
/*   Updated: 2024/05/24 21:41:04 by jubaldo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	handle_keyrelease(int keycode, t_cub3d *game)
{
	if (keycode == KEY_W)
		game->keys.w = false;
	if (keycode == KEY_A)
		game->keys.a = false;
	if (keycode == KEY_S)
		game->keys.s = false;
	if (keycode == KEY_D)
		game->keys.d = false;
	if (keycode == KEY_LEFT)
		game->keys.left = false;
	if (keycode == KEY_RIGHT)
		game->keys.right = false;
	return (0);
}
