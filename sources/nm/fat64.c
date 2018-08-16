/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat64.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/16 14:52:16 by kcosta            #+#    #+#             */
/*   Updated: 2018/08/16 18:41:36 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int		handle_fat64(void *ptr, char *filename)
{
	uint32_t			nfat_arch;
	uint32_t			i;
	struct fat_header	*header;
	struct fat_arch_64	*arch;

	header = (struct fat_header *)ptr;
	nfat_arch = swap_uint64(header->nfat_arch);
	arch = (struct fat_arch_64 *)(header + 1);
	i = 0;
	while (i < nfat_arch)
	{
		if (nfat_arch > 1)
		{
			write(1, "\n", 1);
			write(1, filename, ft_strlen(filename));
			if (i == 0)
				write(1, PPC64_STRING, ft_strlen(PPC64_STRING));
			else if (i == 1)
				write(1, X86_64_STRING, ft_strlen(X86_64_STRING));
		}
		ft_nm(ptr + swap_uint64(arch[i].offset), filename, 0);
		++i;
	}
	return (EXIT_SUCCESS);
}
