/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubaldo <jubaldo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 04:00:46 by jubaldo           #+#    #+#             */
/*   Updated: 2024/05/31 14:04:13 by jubaldo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static char *handle_end_of_line(char *buffer, int depth, int *ret)
{
    char *line;

    line = malloc(sizeof(char) * (depth + 1));
    if (!line)
    {
        *ret = -1;
        return (NULL);
    }
    for (int i = 0; i < depth; i++)
        line[i] = buffer[i];
    line[depth] = '\0';
    return (line);
}

int get_next_line(int fd, char **line)
{
    char buffer[1024];
    int depth = 0;
    int ret;

    *line = NULL;
    while ((ret = read(fd, &buffer[depth], 1)) > 0)
    {
        if (buffer[depth] == '\n')
            break;
        depth++;
        if (depth >= (int)sizeof(buffer))
        {
            buffer[depth] = '\0';
            return (-1); // Line too long
        }
    }
    if (ret == -1 || (ret == 0 && depth == 0))
        return (ret);

    *line = handle_end_of_line(buffer, depth, &ret);
    if (ret > 0)
        return 1;
    return ret;
}
