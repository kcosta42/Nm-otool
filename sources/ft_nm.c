/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 13:14:30 by kcosta            #+#    #+#             */
/*   Updated: 2018/08/13 15:36:00 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int	handle_32(void *ptr)
{

}

int	handle_64(void *ptr)
{

}

int	ft_nm(void *ptr)
{
	uint32_t	magic;

	magic = *(uint32_t *)ptr;
	if (magic == MH_MAGIC)
		return (handle_32(ptr));
	else if (magic == MH_MAGIC_64)
		return (handle_64(ptr));
	write(2, "The file was not recognized as a valid object file\n", 51);
	return (-1);
}

int	main(int ac, char **av)
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
