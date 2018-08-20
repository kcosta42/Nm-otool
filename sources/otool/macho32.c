/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macho32.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/17 15:18:38 by kcosta            #+#    #+#             */
/*   Updated: 2018/08/20 12:46:27 by kcosta           ###   ########.fr       */
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
			print_unsigned(start + i, 16, 8);
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

static void	parse_segments_32(struct load_command *lc, void *ptr, off_t size)
{
	struct segment_command	*seg;
	struct section			*sect;
	uint32_t				i;

	seg = (struct segment_command *)lc;
	sect = (struct section *)((void*)seg + sizeof(*seg));
	i = -1;
	while (++i < ppc_32(seg->nsects))
	{
		if (!ft_strcmp((sect + i)->sectname, SECT_TEXT) \
			&& !ft_strcmp((sect + i)->segname, SEG_TEXT))
		{
			write(1, "Contents of (__TEXT,__text) section\n", 36);
			print_otool(ptr + ppc_32((sect + i)->offset), size, \
				ppc_32((sect + i)->size), ppc_32((sect + i)->addr));
		}
	}
}

int			handle_macho32(void *ptr, char *filename, off_t size)
{
	uint32_t			ncmds;
	struct mach_header	*header;
	struct load_command	*lc;

	filename ? write(1, filename, ft_strlen(filename)) : 0;
	filename ? write(1, ":\n", 2) : 0;
	header = (struct mach_header *)ptr;
	set_ppc(swap_uint32(header->cputype) == CPU_TYPE_POWERPC);
	if (header->cputype != CPU_TYPE_I386 && !*get_ppc())
		return (EXIT_FAILURE);
	ncmds = ppc_32(header->ncmds);
	lc = ptr + sizeof(struct mach_header);
	while (ncmds--)
	{
		if (ppc_32(lc->cmd) == LC_SEGMENT)
			parse_segments_32(lc, ptr, size);
		lc = (void*)lc + ppc_32(lc->cmdsize);
	}
	return (EXIT_SUCCESS);
}
