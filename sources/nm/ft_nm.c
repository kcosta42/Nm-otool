/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 13:14:30 by kcosta            #+#    #+#             */
/*   Updated: 2018/08/20 10:34:47 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static int	print_sections_symbols(t_symbol symbol, size_t len)
{
	if (symbol.type == N_ABS || symbol.type == N_SECT)
		print_unsigned(symbol.value, 16, len);
	if (symbol.type == N_ABS)
		write(1, symbol.ext ? " A " : " a ", 3);
	else if (symbol.type == N_INDR)
		write(1, symbol.ext ? " I " : " i ", 3);
	else if (symbol.type == N_SECT)
	{
		if (symbol.sect == sections()->bss)
			write(1, symbol.ext ? " B " : " b ", 3);
		else if (symbol.sect == sections()->data)
			write(1, symbol.ext ? " D " : " d ", 3);
		else if (symbol.sect == sections()->text)
			write(1, symbol.ext ? " T " : " t ", 3);
		else
			write(1, symbol.ext ? " S " : " s ", 3);
	}
	else
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void		print_symbols(t_symbol symbol, size_t len)
{
	if (!ft_strcmp(symbol.name, ""))
		return ;
	if ((symbol.type == N_UNDF || symbol.type == N_INDR) && symbol.ext)
		write(1, "                ", len);
	if (symbol.type == N_UNDF && symbol.ext)
		write(1, symbol.ext ? " U " : " U ", 3);
	else if (print_sections_symbols(symbol, len) == EXIT_FAILURE)
		return ;
	write(1, symbol.name, ft_strlen(symbol.name));
	if (symbol.type == N_INDR)
	{
		write(1, " (indirect for ", 15);
		write(1, symbol.name, ft_strlen(symbol.name));
		write(1, ")", 1);
	}
	write(1, "\n", 1);
}

int			ft_nm(void *ptr, char *filename, uint8_t multi)
{
	uint32_t	magic;

	magic = *(uint32_t *)ptr;
	reset_sections();
	if (magic == AR_MAGIC || magic == AR_CIGAM)
		return (handle_archive(ptr, filename));
	else if (magic == MH_MAGIC || magic == MH_CIGAM)
		return (handle_macho32(ptr, multi ? filename : NULL));
	else if (magic == MH_MAGIC_64 || magic == MH_CIGAM_64)
		return (handle_macho64(ptr, multi ? filename : NULL));
	else if (magic == FAT_MAGIC || magic == FAT_CIGAM)
		return (handle_fat32(ptr, filename));
	else if (magic == FAT_MAGIC_64 || magic == FAT_CIGAM_64)
		return (handle_fat64(ptr, filename));
	ft_error(filename, INV_OBJ_STRING, EXIT_FAILURE);
	return (-1);
}

int			proceed_file(char *filename, uint8_t multi)
{
	int			fd;
	struct stat	buf;
	void		*ptr;

	fd = open(filename, O_RDONLY);
	if (fd == -1 && errno == EACCES)
		return (ft_error(filename, "Permission denied.", 1));
	else if (fd == -1)
		return (ft_error(filename, "No such file or directory.", 2));
	if (fstat(fd, &buf) < 0)
		return (ft_error(filename, "Permission denied.", 3));
	if (S_ISDIR(buf.st_mode))
		return (ft_error(filename, "Is a directory.", 4));
	ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	if (ptr == MAP_FAILED)
		return (EXIT_FAILURE);
	ft_nm(ptr, filename, multi);
	if (munmap(ptr, buf.st_size) < 0)
		return (EXIT_FAILURE);
	if (close(fd) < 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int			main(int ac, char **av)
{
	int		i;
	char	*filename;

	if (ac < 2)
		return (proceed_file("a.out", 0));
	i = 1;
	while (i < ac)
	{
		filename = av[i];
		proceed_file(filename, ac > 2);
		++i;
	}
	return (EXIT_SUCCESS);
}
