/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/17 18:33:24 by kcosta            #+#    #+#             */
/*   Updated: 2018/08/19 11:47:29 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (*(str++))
		len++;
	return (len);
}

int		ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *(uint8_t*)s1 == *(uint8_t*)s2)
	{
		s1++;
		s2++;
	}
	return (*(uint8_t*)s1 - *(uint8_t*)s2);
}

int		ft_atoi(const char *str)
{
	int		result;
	int		sign;

	result = 0;
	while ((*str == ' ') | (*str == '\n') | (*str == '\t') \
	| (*str == '\v') | (*str == '\f') | (*str == '\r'))
		str++;
	sign = (*str == '-') ? -1 : 1;
	if (*str == '+' || *str == '-')
		str++;
	while (*str && (*str >= '0' && *str <= '9'))
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}
