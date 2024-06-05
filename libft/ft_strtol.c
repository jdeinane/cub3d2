/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubaldo <jubaldo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 18:45:58 by jubaldo           #+#    #+#             */
/*   Updated: 2024/06/05 18:50:53 by jubaldo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int ft_isspace(char c)
{
	return (c == ' ' || (c >= '\t' && c <= '\r'));
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
	while ((*str >= '0' && *str <= '9') ||
		   (*str >= 'a' && *str <= 'z') ||
		   (*str >= 'A' && *str <= 'Z'))
	{
		int digit;
		if (*str >= '0' && *str <= '9')
			digit = *str - '0';
		else if (*str >= 'a' && *str <= 'z')
			digit = *str - 'a' + 10;
		else
			digit = *str - 'A' + 10;
		if (digit >= base)
			break;
		if (result > (LONG_MAX - digit) / base)
			return (sign == 1 ? LONG_MAX : LONG_MIN);
		result = result * base + digit;
		str++;
	}
	if (endptr != 0)
		*endptr = (char *)str;
	return (sign * result);
}