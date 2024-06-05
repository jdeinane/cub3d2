/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubaldo <jubaldo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 18:45:58 by jubaldo           #+#    #+#             */
/*   Updated: 2024/06/05 18:46:54 by jubaldo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int ft_isspace(char c)
{
	return (c == ' ' || (c >= '\t' && c <= '\r'));
}

static int ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

long ft_strtol(const char *str, char **endptr, int base)
{
	long result;
	int sign;

	while (ft_isspace(*str))
		str++;
	sign = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	result = 0;
	while (ft_isdigit(*str))
	{
		if (result > (LONG_MAX - (*str - '0')) / base)
		{
			result = (sign == 1) ? LONG_MAX : LONG_MIN;
			break;
		}
		result = result * base + (*str - '0');
		str++;
	}
	if (endptr)
		*endptr = (char *)str;
	return (sign * result);
}
