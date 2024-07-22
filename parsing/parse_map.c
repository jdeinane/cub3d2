/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubaldo <jubaldo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 15:58:20 by jubaldo           #+#    #+#             */
/*   Updated: 2024/07/22 15:58:34 by jubaldo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	parse_map(t_cub3d *game, char *line)
{
	static t_map_info	map_info = {NULL, 0, 0, false};

	initialize_static_variables(&map_info);
	handle_map_line(game, line, &map_info);
}
