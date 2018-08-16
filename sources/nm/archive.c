/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   archive.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/16 11:39:17 by kcosta            #+#    #+#             */
/*   Updated: 2018/08/16 15:00:02 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static void	print_archive_file_name(char *filename, char* symbol)
{
	write(1, "\n", 1);
	write(1, filename, ft_strlen(filename));
	write(1, "(", 1);
	write(1, symbol, ft_strlen(symbol));
	write(1, "):\n", 3);
}

int			handle_archive(void *ptr, char *filename)
{
	struct ar_hdr	*header;
	char			*str;
	size_t			len;

	ptr += SARMAG;
	header = (struct ar_hdr *)ptr;
	ptr += ft_atoi(header->ar_size) + sizeof(struct ar_hdr);
	while (ptr)
	{
		header = (struct ar_hdr *)ptr;
		if (ft_atoi(header->ar_size) <= 0)
			return (EXIT_FAILURE);
		str = ptr + sizeof(struct ar_hdr);
		print_archive_file_name(filename, str);
		len = ft_strlen(str);
		while (!str[len++])
			;
		ft_nm(ptr + sizeof(struct ar_hdr) + len - 1, filename, 0);
		ptr += ft_atoi(header->ar_size) + sizeof(struct ar_hdr);
	}
	return (EXIT_SUCCESS);
}
