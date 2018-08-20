/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 13:11:36 by kcosta            #+#    #+#             */
/*   Updated: 2018/08/20 13:16:45 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
# define FT_NM_H

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

# define INV_OBJ_STRING "The file was not recognized as a valid object file\n"

# define PPC_STRING " (for architecture ppc):\n"
# define PPC64_STRING " (for architecture ppc64):\n"
# define I386_STRING " (for architecture i386):\n"
# define X86_64_STRING " (for architecture x86_64):\n"

# define AR_MAGIC 0x72613c21
# define AR_CIGAM 0x213c6172

# define SYMBOL_SIZE 512

typedef struct	s_symbol
{
	char		name[SYMBOL_SIZE];
	uint8_t		type;
	uint8_t		ext;
	uint8_t		sect;
	uint64_t	value;
}				t_symbol;

typedef struct	s_section
{
	uint32_t	index;
	uint32_t	text;
	uint32_t	data;
	uint32_t	bss;
}				t_section;

int				ft_nm(void *ptr, char *filename, uint8_t multi, off_t size);

int				handle_archive(void *ptr, char *filename, off_t size);
int				handle_macho32(void *ptr, char *filename);
int				handle_macho64(void *ptr, char *filename);
int				handle_fat32(void *ptr, char *filename, off_t size);
int				handle_fat64(void *ptr, char *filename, off_t size);

t_symbol		*sort_symbols(t_symbol *symbols, uint32_t size);

void			set_ppc(u_int8_t ppc);
uint32_t		ppc_32(uint32_t n);
uint64_t		ppc_64(uint64_t n);

t_section		*sections(void);
void			reset_sections(void);

int				ft_error(char *filename, char *msg, int errnum);

void			print_symbols(t_symbol symbol, size_t len);
void			print_unsigned(size_t addr, size_t base, size_t len);

uint32_t		swap_uint32(uint32_t n);
uint64_t		swap_uint64(uint64_t n);

int				ft_atoi(const char *str);

size_t			ft_strlen(const char *str);
int				ft_strcmp(const char *s1, const char *s2);
char			*ft_strncpy(char *dst, const char *src, size_t len);

#endif
