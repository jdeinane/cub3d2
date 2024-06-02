/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubaldo <jubaldo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:18:57 by jubaldo           #+#    #+#             */
/*   Updated: 2024/05/25 22:26:28 by jubaldo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	has_cub_extension(char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	if (len < 4)
		return (0);
	return (ft_strcmp(filename + len - 4, ".cub") == 0);
}

void	parse_args(int ac, char **av)
{
	if (ac != 2)
		error_exit(NULL, "Error: Wrong arguments");
	if (!has_cub_extension(av[1]))
		error_exit(NULL, "Error: Map must have a .cub extension");
}
