/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubaldo <jubaldo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 19:16:22 by jubaldo           #+#    #+#             */
/*   Updated: 2024/05/31 20:07:53 by jubaldo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	game_loop(t_cub3d *game)
{
	update_player(game);
	draw_floor_and_ceiling(game);
	perform_raycasting(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}

int	main(int ac, char **av)
{
	t_cub3d	game;

	ft_memset(&game, 0, sizeof(t_cub3d));
	parse_args(ac, av);
	init_cub3d(&game);
	init_game(&game);
	parse_file(&game, av[1]);
	mlx_hook(game.win, 2, 1L << 0, handle_keypress, &game);
	mlx_hook(game.win, 3, 1L << 1, handle_keyrelease, &game);
	mlx_hook(game.win, 17, 0L, handle_exit, &game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
	free_resources(&game);
	return (0);
}
