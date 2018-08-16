/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macho64.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/16 10:48:52 by kcosta            #+#    #+#             */
/*   Updated: 2018/08/16 18:32:50 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static void	parse_segments_64(struct load_command *lc)
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
			sections()->text = sections()->index + 1;
		else if (!ft_strcmp((sect + i)->sectname, SECT_DATA) \
			&& !ft_strcmp((sect + i)->segname, SEG_DATA))
			sections()->data = sections()->index + 1;
		else if (!ft_strcmp((sect + i)->sectname, SECT_BSS) \
			&& !ft_strcmp((sect + i)->segname, SEG_DATA))
			sections()->bss = sections()->index + 1;
		++(sections()->index);
	}
}

static void	print_nm_64(uint32_t nsyms, uint32_t symoff,
						uint32_t stroff, void *ptr)
{
	struct nlist_64		*list;
	char				*strtable;
	char				*str;
	uint32_t			i;
	t_symbol			*symbols;

	list = ptr + symoff;
	strtable = (char *)ptr + stroff;
	i = 0;
	symbols = (t_symbol*)malloc(sizeof(t_symbol) * nsyms);
	while (i < nsyms)
	{
		str = strtable + ppc_64(list[i].n_un.n_strx);
		ft_strncpy(symbols[i].name, str, SYMBOL_SIZE);
		symbols[i].type = list[i].n_type & N_TYPE;
		symbols[i].ext = list[i].n_type & N_EXT;
		symbols[i].sect = list[i].n_sect;
		symbols[i].value = ppc_64(list[i].n_value);
		++i;
	}
	symbols = sort_symbols(symbols, nsyms);
	i = 0;
	while (i < nsyms)
		print_symbols(symbols[i++], 16);
	free(symbols);
}

int			handle_macho64(void *ptr, char *filename)
{
	uint32_t					ncmds;
	struct mach_header_64		*header;
	struct load_command			*lc;
	struct symtab_command		*sym;

	filename ? write(1, "\n", 1) : 0;
	filename ? write(1, filename, ft_strlen(filename)) : 0;
	filename ? write(1, ":\n", 2) : 0;
	header = (struct mach_header_64 *)ptr;
	set_ppc(swap_uint64(header->cputype) == CPU_TYPE_POWERPC64);
	ncmds = ppc_64(header->ncmds);
	lc = ptr + sizeof(struct mach_header_64);
	while (ncmds--)
	{
		if (ppc_64(lc->cmd) == LC_SEGMENT_64)
			parse_segments_64(lc);
		if (ppc_64(lc->cmd) == LC_SYMTAB)
		{
			sym = (struct symtab_command *)lc;
			print_nm_64(ppc_64(sym->nsyms), ppc_64(sym->symoff),
						ppc_64(sym->stroff), ptr);
		}
		lc = (void*)lc + ppc_64(lc->cmdsize);
	}
	return (0);
}
