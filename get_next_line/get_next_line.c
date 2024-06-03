/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubaldo <jubaldo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 04:00:46 by jubaldo           #+#    #+#             */
/*   Updated: 2024/06/03 13:00:18 by jubaldo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static char	*handle_end_of_line(char *buffer, int depth, int *ret)
{
	char	*line;
	int		i;

	line = malloc(sizeof(char) * (depth + 1));
	if (!line)
	{
		*ret = -1;
		return (NULL);
	}
	i = 0;
	while (i < depth)
	{
		line[i] = buffer[i];
		i++;
	}
	line[depth] = '\0';
	return (line);
}

int	get_next_line(int fd, char **line)
{
	char	buffer[1024];
	int		depth;
	int		ret;

	*line = NULL;
	depth = 0;
	while ((ret = read(fd, &buffer[depth], 1)) > 0)
	{
		if (buffer[depth] == '\n')
			break ;
		depth++;
		if (depth >= (int) sizeof(buffer))
		{
			buffer[depth] = '\0';
			return (-1);
		}
	}
	if (ret == -1 || (ret == 0 && depth == 0))
		return (ret);
	*line = handle_end_of_line(buffer, depth, &ret);
	if (ret > 0)
		return (1);
	return (ret);
}
