/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubaldo <jubaldo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 17:30:14 by jubaldo           #+#    #+#             */
/*   Updated: 2024/06/02 19:35:59 by jubaldo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	get_texture_index(char *id)
{
	if (ft_strncmp(id, "NO", 2) == 0)
		return (0);
	else if (ft_strncmp(id, "SO", 2) == 0)
		return (1);
	else if (ft_strncmp(id, "WE", 2) == 0)
		return (2);
	else if (ft_strncmp(id, "EA", 2) == 0)
		return (3);
	return (-1);
}

void parse_textures(t_cub3d *game, char *line)
{
	char **tokens;
	int texture_index;

	tokens = ft_split(line, ' ');
	if (!tokens || !tokens[1])
	{
		free_tokens(tokens);
		error_exit(game, "Error: Invalid texture path");
	}

	texture_index = get_texture_index(tokens[0]);
	if (texture_index == -1)
	{
		free_tokens(tokens);
		error_exit(game, "Error: Unknown texture identifier");
	}
	game->textures[texture_index].img = mlx_xpm_file_to_image(game->mlx, tokens[1],
															  &game->textures[texture_index].width, &game->textures[texture_index].height);
	if (!game->textures[texture_index].img)
	{
		free_tokens(tokens);
		error_exit(game, "Error: Failed to load texture");
	}

	game->textures[texture_index].data = (int *)mlx_get_data_addr(
		game->textures[texture_index].img, &game->textures[texture_index].bpp,
		&game->textures[texture_index].size_line, &game->textures[texture_index].endian);
	if (!game->textures[texture_index].data)
	{
		free_tokens(tokens);
		error_exit(game, "Error: Failed to get texture data");
	}
	free_tokens(tokens);
}
