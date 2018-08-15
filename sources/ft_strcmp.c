/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 20:38:13 by kcosta            #+#    #+#             */
/*   Updated: 2018/08/15 14:11:27 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int		ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *(uint8_t*)s1 == *(uint8_t*)s2)
	{
		s1++;
		s2++;
	}
	return (*(uint8_t*)s1 - *(uint8_t*)s2);
}
