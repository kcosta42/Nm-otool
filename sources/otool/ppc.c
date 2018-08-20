/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/17 18:21:44 by kcosta            #+#    #+#             */
/*   Updated: 2018/08/20 10:33:09 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

uint8_t			*get_ppc(void)
{
	static u_int8_t	ppc = 0;

	return (&ppc);
}

void			set_ppc(u_int8_t ppc)
{
	*get_ppc() = ppc;
}

uint32_t		ppc_32(uint32_t n)
{
	uint8_t	ppc;

	ppc = *get_ppc();
	if (ppc != 0)
		return (swap_uint32(n));
	return (n);
}

uint64_t		ppc_64(uint64_t n)
{
	uint8_t	ppc;

	ppc = *get_ppc();
	if (ppc != 0)
		return (swap_uint64(n));
	return (n);
}
