/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   archive.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 16:33:55 by kcosta            #+#    #+#             */
/*   Updated: 2018/08/20 13:14:12 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static void	print_archive_file_name(char *filename, char *symbol)
{
	write(1, filename, ft_strlen(filename));
	write(1, "(", 1);
	write(1, symbol, ft_strlen(symbol));
	write(1, "):\n", 3);
}

static void	print_archive_name(char *filename)
{
	write(1, "Archive : ", 10);
	write(1, filename, ft_strlen(filename));
	write(1, "\n", 1);
}

int			handle_archive(void *ptr, char *filename, off_t s)
{
	struct ar_hdr	*header;
	char			*str;
	size_t			len;

	print_archive_name(filename);
	ptr += SARMAG;
	header = (struct ar_hdr *)ptr;
	ptr += ft_atoi(header->ar_size) + sizeof(struct ar_hdr);
	while (ptr)
	{
		header = (struct ar_hdr *)ptr;
		if (ft_atoi(header->ar_size) <= 0)
			return (EXIT_FAILURE);
		str = ptr + sizeof(struct ar_hdr);
		if (ptr + (ft_atoi(header->ar_size) + sizeof(struct ar_hdr)) > ptr + s)
			return (EXIT_FAILURE);
		print_archive_file_name(filename, str);
		len = ft_strlen(str);
		while (!str[len++])
			;
		ft_otool(ptr + sizeof(struct ar_hdr) + len - 1, NULL, s);
		ptr += ft_atoi(header->ar_size) + sizeof(struct ar_hdr);
	}
	return (EXIT_SUCCESS);
}
