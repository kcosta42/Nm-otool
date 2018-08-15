/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 13:14:30 by kcosta            #+#    #+#             */
/*   Updated: 2018/08/15 20:08:03 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

size_t text = 0;
size_t data = 0;
size_t bss = 0;

void		parse_segments_64(struct load_command *lc)
{
	struct segment_command_64	*seg;
	struct section_64			*sect;
	uint32_t					i;

	seg = (struct segment_command_64 *)lc;
	sect = (struct section_64 *)((void*)seg + sizeof(*seg));
	i = 0;
	while (i < seg->nsects)
	{
		if (!ft_strcmp((sect + i)->sectname, SECT_TEXT)
			&& !ft_strcmp((sect + i)->segname, SEG_TEXT))
			text = i + 1;
		else if (!ft_strcmp((sect + i)->sectname, SECT_DATA)
			&& !ft_strcmp((sect + i)->segname, SEG_DATA))
			data = i + 1;
		else if (!ft_strcmp((sect + i)->sectname, SECT_BSS)
			&& !ft_strcmp((sect + i)->segname, SEG_DATA))
			bss = i + 1;
		++i;
	}
}

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

void	print_unsigned(size_t addr, size_t base, size_t len)
{
	char	value;

	if (len <= 0)
		return ;
	print_unsigned(addr / base, base, len - 1);
	value = HEX_STRING[(addr % base)];
	write(1, &value, 1);
}

void	print_symbols(t_symbol symbol, size_t len)
{
	if (!ft_strcmp(symbol.name, ""))
		return ;
	if (symbol.type == N_UNDF && symbol.ext)
	{
		write(1, "                ", len);
		write(1, symbol.ext ? " U " : " U ", 3);
	}
	else
	{
		if (symbol.type == N_ABS || symbol.type == N_INDR \
		|| symbol.type == N_SECT)
		{
			// printf("sect: %d -- text: %zu, data: %zu, bss: %zu\n", symbol.sect, text, data, bss);
			print_unsigned(symbol.value, 16, len);
		}
		if (symbol.type == N_ABS)
			write(1, symbol.ext ? " A " : " a ", 3);
		else if (symbol.type == N_INDR)
			write(1, symbol.ext ? " I " : " i ", 3);
		else if (symbol.type == N_SECT)
		{
			if (symbol.sect == bss)
				write(1, symbol.ext ? " B " : " b ", 3);
			else if (symbol.sect == data)
				write(1, symbol.ext ? " D " : " d ", 3);
			else if (symbol.sect == text)
				write(1, symbol.ext ? " T " : " t ", 3);
			else
				write(1, symbol.ext ? " S " : " s ", 3);
		}
		else
			return ;
	}
	write(1, symbol.name, ft_strlen(symbol.name));
	write(1, "\n", 1);
}

void	print_nm_32(uint32_t nsyms, uint32_t symoff, uint32_t stroff, void *ptr)
{
	struct nlist	*list;
	char			*strtable;
	char			*str;
	uint32_t		i;
	t_symbol		*symbols;

	list = ptr + symoff;
	strtable = (char *)ptr + stroff;
	i = 0;
	symbols = (t_symbol*)malloc(sizeof(t_symbol) * nsyms);
	while (i < nsyms)
	{
		str = strtable + list[i].n_un.n_strx;
		ft_strncpy(symbols[i].name, str, SYMBOL_SIZE);
		symbols[i].type = list[i].n_type & N_TYPE;
		symbols[i].ext = list[i].n_type & N_EXT;
		symbols[i].sect = list[i].n_sect;
		symbols[i].value = list[i].n_value;
		++i;
	}
	symbols = sort_symbols(symbols, nsyms);
	i = 0;
	while (i < nsyms)
		print_symbols(symbols[i++], 8);
	free(symbols);
}

void	print_nm_64(uint32_t nsyms, uint32_t symoff, uint32_t stroff, void *ptr)
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
		str = strtable + list[i].n_un.n_strx;
		ft_strncpy(symbols[i].name, str, SYMBOL_SIZE);
		symbols[i].type = list[i].n_type & N_TYPE;
		symbols[i].ext = list[i].n_type & N_EXT;
		symbols[i].sect = list[i].n_sect;
		symbols[i].value = list[i].n_value;
		++i;
	}
	symbols = sort_symbols(symbols, nsyms);
	i = 0;
	while (i < nsyms)
		print_symbols(symbols[i++], 16);
	free(symbols);
}

int		handle_32(void *ptr)
{
	uint32_t				ncmds;
	struct mach_header		*header;
	struct load_command		*lc;
	struct symtab_command	*sym;

	header = (struct mach_header *)ptr;
	ncmds = header->ncmds;
	lc = ptr + sizeof(struct mach_header);
	while (ncmds--)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *)lc;
			print_nm_32(sym->nsyms, sym->symoff, sym->stroff, ptr);
			break ;
		}
		lc = (void*)lc + lc->cmdsize;
	}
	return (0);
}

int		handle_64(void *ptr)
{
	uint32_t					ncmds;
	struct mach_header_64		*header;
	struct load_command			*lc;
	struct symtab_command		*sym;

	header = (struct mach_header_64 *)ptr;
	ncmds = header->ncmds;
	lc = ptr + sizeof(struct mach_header_64);
	while (ncmds--)
	{
		if (lc->cmd == LC_SEGMENT_64)
			parse_segments_64(lc);
		if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *)lc;
			print_nm_64(sym->nsyms, sym->symoff, sym->stroff, ptr);
		}
		lc = (void*)lc + lc->cmdsize;
	}
	return (0);
}

int		ft_nm(void *ptr)
{
	uint32_t	magic;

	magic = *(uint32_t *)ptr;
	if (magic == AR_MAGIC || magic == AR_CIGAM)
		return write(1, "AR\n", 3);
	else if (magic == MH_MAGIC || magic == MH_CIGAM)
		return (handle_32(ptr));
	else if (magic == MH_MAGIC_64 || magic == MH_CIGAM_64)
		return (handle_64(ptr));
	else if (magic == FAT_MAGIC || magic == FAT_CIGAM)
		return write(1, "FAT32\n", 6);
	else if (magic == FAT_MAGIC_64 || magic == FAT_CIGAM_64)
		return write(1, "FAT64\n", 6);
	write(2, "The file was not recognized as a valid object file\n", 51);
	return (-1);
}

int		main(int ac, char **av)
{
	int			fd;
	struct stat	buf;
	void		*ptr;

	if (ac < 2)
		return (EXIT_FAILURE); // `nm` without args should become `nm a.out`
	if ((fd = open(av[1], O_RDONLY)) < 0)
	{
		write(2, av[1], ft_strlen(av[1]));
		write(2, ": No such file or directory.\n", 31);
		return (EXIT_FAILURE);
	}
	if (fstat(fd, &buf) < 0)
		return (EXIT_FAILURE);
	if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		return (EXIT_FAILURE);
	ft_nm(ptr);
	if (munmap(ptr, buf.st_size) < 0)
		return (EXIT_FAILURE);
	if (close(fd) < 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
