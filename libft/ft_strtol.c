/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubaldo <jubaldo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 18:45:58 by jubaldo           #+#    #+#             */
/*   Updated: 2024/07/22 16:07:32 by jubaldo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_isspace(char c)
{
	return (c == ' ' || (c >= '\t' && c <= '\r'));
}

static int	ft_is_valid_digit(char c, int base)
{
	if (base <= 10)
		return (c >= '0' && c < '0' + base);
	return ((c >= '0' && c <= '9') || \
	(c >= 'a' && c < 'a' + base - 10) \
	|| (c >= 'A' && c < 'A' + base - 10));
}

static int	ft_get_digit_value(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	if (c >= 'a' && c <= 'z')
		return (c - 'a' + 10);
	return (c - 'A' + 10);
}

static long	ft_handle_overflow(int sign)
{
	if (sign == 1)
		return (LONG_MAX);
	return (LONG_MIN);
}

long	ft_strtol(const char *str, char **endptr, int base)
{
	long	result;
	int		sign;
	int		digit;

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
	while (ft_is_valid_digit(*str, base))
	{
		digit = ft_get_digit_value(*str);
		if (result > (LONG_MAX - digit) / base)
			return (ft_handle_overflow(sign));
		result = result * base + digit;
		str++;
	}
	if (endptr != 0)
		*endptr = (char *)str;
	return (sign * result);
}
