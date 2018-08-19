/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/16 18:58:36 by kcosta            #+#    #+#             */
/*   Updated: 2018/08/18 17:00:32 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_OTOOL_H
# define FT_OTOOL_H

#include <stdio.h>

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# include <sys/mman.h>
# include <sys/stat.h>

# include <mach-o/fat.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <ar.h>

# include <errno.h>

# define HEX_STRING "0123456789abcdef"

# define NOT_OBJ_STRING "is not an object file\n"

# define PPC_STRING " (architecture ppc):\n"
# define PPC64_STRING " (architecture ppc64):\n"
# define I386_STRING " (architecture i386):\n"
# define X86_64_STRING " (architecture x86_64):\n"

# define AR_MAGIC 0x72613c21
# define AR_CIGAM 0x213c6172

# define SYMBOL_SIZE 512

int			ft_otool(void *ptr, char *filename);

int			handle_archive(void *ptr, char *filename);
int			handle_macho32(void *ptr, char *filename);
int			handle_macho64(void *ptr, char *filename);
int			handle_fat32(void *ptr, char *filename);
int			handle_fat64(void *ptr, char *filename);

int			ft_error(char *filename, char* msg, int errnum);

void		print_unsigned(size_t addr, size_t base, size_t len);

uint8_t		*get_ppc(void);
void		set_ppc(u_int8_t ppc);
uint32_t	ppc_32(uint32_t n);
uint64_t	ppc_64(uint64_t n);

uint32_t	swap_uint32(uint32_t n);
uint64_t	swap_uint64(uint64_t n);

size_t		ft_strlen(const char *str);
int			ft_strcmp(const char *s1, const char *s2);

int			ft_atoi(const char *str);

#endif
