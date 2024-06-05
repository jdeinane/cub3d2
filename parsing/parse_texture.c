/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubaldo <jubaldo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 17:30:14 by jubaldo           #+#    #+#             */
/*   Updated: 2024/06/05 11:52:59 by jubaldo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int get_texture_index(char *id)
{
	if (ft_strncmp(id, "NO", 2) == 0)
		return 0;
	else if (ft_strncmp(id, "SO", 2) == 0)
		return 1;
	else if (ft_strncmp(id, "WE", 2) == 0)
		return 2;
	else if (ft_strncmp(id, "EA", 2) == 0)
		return 3;
	return -1;
}

static void load_texture(t_cub3d *game, char *path, int index, char *line)
{
	game->textures[index].img = mlx_xpm_file_to_image(game->mlx, path, \
	&game->textures[index].width, &game->textures[index].height);
	if (!game->textures[index].img)
	{
		printf("Failed to load texture: %s\n", path);
		perror("mlx_xpm_file_to_image");
		error_exit2(game, "Error: Texture not loaded", line);
	}
	game->textures[index].data = (int *)mlx_get_data_addr(game->textures[index].img, \
	&game->textures[index].bpp, &game->textures[index].size_line, &game->textures[index].endian);
	if (!game->textures[index].data)
	{
		perror("mlx_get_data_addr");
		error_exit2(game, "Error: Failed to get texture data", line);
	}
}

void parse_textures(t_cub3d *game, char *line)
{
	char	**tokens;
	int		texture_index;

	tokens = ft_split(line, ' ');
	if (!tokens || !tokens[1])
	{
		free_tokens(tokens);
		error_exit2(game, "Error: Invalid texture path", line);
	}
	texture_index = get_texture_index(tokens[0]);
	if (texture_index == -1)
	{
		free_tokens(tokens);
		error_exit2(game, "Error: Unknown texture identifier", line);
	}
	load_texture(game, tokens[1], texture_index, line);
	free_tokens(tokens);
}
