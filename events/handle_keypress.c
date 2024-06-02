/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keypress.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubaldo <jubaldo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 16:57:42 by jubaldo           #+#    #+#             */
/*   Updated: 2024/05/25 21:40:33 by jubaldo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	handle_keypress(int keycode, t_cub3d *game)
{
	if (keycode == KEY_ESC)
		clean_exit(game);
	if (keycode == KEY_W)
		game->keys.w = true;
	if (keycode == KEY_A)
		game->keys.a = true;
	if (keycode == KEY_S)
		game->keys.s = true;
	if (keycode == KEY_D)
		game->keys.d = true;
	if (keycode == KEY_LEFT)
		game->keys.left = true;
	if (keycode == KEY_RIGHT)
		game->keys.right = true;
	return (0);
}
