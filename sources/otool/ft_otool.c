/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/16 18:57:55 by kcosta            #+#    #+#             */
/*   Updated: 2018/08/16 22:34:21 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"


int		ft_nm(void *ptr, char *filename)
{
	uint32_t	magic;

	magic = *(uint32_t *)ptr;
	reset_sections();
	if (magic == AR_MAGIC || magic == AR_CIGAM)
		return (handle_archive(ptr, filename));
	else if (magic == MH_MAGIC || magic == MH_CIGAM)
		return (handle_macho32(ptr, filename));
	else if (magic == MH_MAGIC_64 || magic == MH_CIGAM_64)
		return (handle_macho64(ptr, filename));
	else if (magic == FAT_MAGIC || magic == FAT_CIGAM)
		return (handle_fat32(ptr, filename));
	else if (magic == FAT_MAGIC_64 || magic == FAT_CIGAM_64)
		return (handle_fat64(ptr, filename));
	ft_error(filename, NOT_OBJ_STRING, EXIT_FAILURE);
	return (-1);
}

int		proceed_file(char *filename)
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
	ft_otool(ptr, filename);
	if (munmap(ptr, buf.st_size) < 0)
		return (EXIT_FAILURE);
	if (close(fd) < 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int		main(int ac, char **av)
{
	int		i;
	char	*filename;

	if (ac < 2)
		return (ft_error("", "File is missing.", EXIT_FAILURE));
	i = 1;
	while(i < ac)
	{
		filename = av[i];
		proceed_file(filename);
		++i;
	}
	return (EXIT_SUCCESS);
}
