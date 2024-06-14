/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubaldo <jubaldo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 16:11:51 by jubaldo           #+#    #+#             */
/*   Updated: 2024/06/14 15:59:51 by jubaldo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	error_exit(t_cub3d *game, const char *msg)
{
	write(STDERR_FILENO, msg, ft_strlen(msg));
	write(STDERR_FILENO, "\n", 1);
	if (game)
		free_resources(game);
	exit(EXIT_FAILURE);
}

void	error_exit2(t_cub3d *game, const char *msg, char *line_to_free)
{
	if (line_to_free)
		free(line_to_free);
	if (game)
		free_resources(game);
	write(STDERR_FILENO, msg, ft_strlen(msg));
	write(STDERR_FILENO, "\n", 1);
	exit(EXIT_FAILURE);
}

void	clean_exit(t_cub3d *game)
{
	free_resources(game);
	write(1, "cub3d: successfully exited.\n", 28);
	exit(0);
}

int	handle_exit(t_cub3d *game)
{
	clean_exit(game);
	return (0);
}
