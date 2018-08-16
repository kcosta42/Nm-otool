/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/16 10:57:04 by kcosta            #+#    #+#             */
/*   Updated: 2018/08/16 18:33:15 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

t_symbol	*sort_symbols(t_symbol *symbols, uint32_t size)
{
	int			ret;
	uint32_t	i;
	uint32_t	j;
	t_symbol	tmp;

	i = 0;
	while (i < size - 1)
	{
		j = i + 1;
		while (j < size)
		{
			ret = ft_strcmp(symbols[i].name, symbols[j].name);
			if (ret > 0 || (ret == 0 && symbols[i].value > symbols[j].value))
			{
				tmp = symbols[i];
				symbols[i] = symbols[j];
				symbols[j] = tmp;
			}
			++j;
		}
		++i;
	}
	return (symbols);
}

int			ft_error(char *filename, char* msg, int errnum)
{
	write(2, "./ft_nm: ", 9);
	write(2, filename, ft_strlen(filename));
	write(2, ": ", 2);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	return errnum;
}

void		print_unsigned(size_t addr, size_t base, size_t len)
{
	char	value;

	if (len <= 0)
		return ;
	print_unsigned(addr / base, base, len - 1);
	value = HEX_STRING[(addr % base)];
	write(1, &value, 1);
}

uint32_t	swap_uint32(uint32_t n)
{
	n = ((n << 8) & 0xFF00FF00) | ((n >> 8) & 0xFF00FF);
	return ((n << 16) | (n >> 16));
}

uint64_t	swap_uint64(uint64_t n)
{
	n = ((n << 8) & 0xFF00FF00FF00FF00ULL) \
		| ((n >> 8) & 0x00FF00FF00FF00FFULL);
	n = ((n << 16) & 0xFFFF0000FFFF0000ULL) \
		| ((n >> 16) & 0x0000FFFF0000FFFFULL);
	return ((n << 32) | (n >> 32));
}
