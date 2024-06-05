/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok_r.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubaldo <jubaldo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:01:03 by jubaldo           #+#    #+#             */
/*   Updated: 2024/06/05 12:15:52 by jubaldo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static size_t ft_strspn(const char *s1, const char *s2)
{
	const char *p;
	const char *a;
	size_t count = 0;

	p = s1;
	while (*p != '\0')
	{
		a = s2;
		while (*a != '\0')
		{
			if (*p == *a)
				break;
			++a;
		}
		if (*a == '\0')
			return (count);
		else
			++count;
		++p;
	}
	return (count); 
}

static size_t ft_strcspn(const char *s1, const char *s2)
{
	const char *p;
	const char *a;

	p = s1;
	while (*p != '\0')
	{
		a = s2;
		while (*a != '\0')
		{
			if (*p == *a)
				return (p - s1);
			++a;
		}
		++p;
	}
	return (p - s1);
}

char *ft_strtok_r(char *str, const char *delim, char **saveptr)
{
	char *end;

	if (str == NULL)
		str = *saveptr;
	if (*str == '\0')
	{
		*saveptr = str;
		return (NULL);
	}
	str += ft_strspn(str, delim);
	if (*str == '\0')
	{
		*saveptr = str;
		return (NULL);
	}
	end = str + ft_strcspn(str, delim);
	if (*end == '\0')
	{
		*saveptr = end;
		return str;
	}
	*end = '\0';
	*saveptr = end + 1;
	return (str);
}
