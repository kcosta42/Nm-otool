/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macho64.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/17 15:23:14 by kcosta            #+#    #+#             */
/*   Updated: 2018/08/20 12:46:29 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static void	print_otool(void *ptr, off_t m_size, uint64_t size, uint64_t start)
{
	size_t	i;

	i = 0;
	if (ptr + m_size < ptr + size)
		return ;
	while (i < size + ((size % 16) ? (16 - size % 16) : 0))
	{
		if (i % 16 == 0)
		{
			print_unsigned(start + i, 16, 16);
			write(1, "\t", 1);
		}
		if (i < size)
			print_unsigned(0xff & ((char *)ptr)[i], 16, 2);
		if (!*get_ppc() && i < size)
			write(1, " ", 1);
		if (*get_ppc() && (i % 4 == 3) && i < size)
			write(1, " ", 1);
		if (i % 16 == 15)
			write(1, "\n", 1);
		i++;
	}
}

static void	parse_segments_64(struct load_command *lc, void *ptr, off_t size)
{
	struct segment_command_64	*seg;
	struct section_64			*sect;
	uint32_t					i;

	seg = (struct segment_command_64 *)lc;
	sect = (struct section_64 *)((void*)seg + sizeof(*seg));
	i = -1;
	while (++i < ppc_64(seg->nsects))
	{
		if (!ft_strcmp((sect + i)->sectname, SECT_TEXT) \
			&& !ft_strcmp((sect + i)->segname, SEG_TEXT))
		{
			write(1, "Contents of (__TEXT,__text) section\n", 36);
			print_otool(ptr + ppc_64((sect + i)->offset), size, \
				ppc_64((sect + i)->size), ppc_64((sect + i)->addr));
		}
	}
}

int			handle_macho64(void *ptr, char *filename, off_t size)
{
	uint32_t					ncmds;
	struct mach_header_64		*header;
	struct load_command			*lc;

	filename ? write(1, filename, ft_strlen(filename)) : 0;
	filename ? write(1, ":\n", 2) : 0;
	header = (struct mach_header_64 *)ptr;
	set_ppc(swap_uint64(header->cputype) == CPU_TYPE_POWERPC64);
	if (header->cputype != CPU_TYPE_X86_64 && !*get_ppc())
		return (EXIT_FAILURE);
	ncmds = ppc_64(header->ncmds);
	lc = ptr + sizeof(struct mach_header_64);
	while (ncmds--)
	{
		if (ppc_64(lc->cmd) == LC_SEGMENT_64)
			parse_segments_64(lc, ptr, size);
		lc = (void*)lc + ppc_64(lc->cmdsize);
	}
	return (EXIT_SUCCESS);
}
