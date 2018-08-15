/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 13:11:36 by kcosta            #+#    #+#             */
/*   Updated: 2018/08/15 16:59:45 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
# define FT_NM_H

# include <stdio.h>

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# include <sys/mman.h>
# include <sys/stat.h>

# include <mach-o/fat.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>

# define HEX_STRING "0123456789abcdef"

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

size_t	ft_strlen(const char *str);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strcpy(char *dst, const char *src);
char	*ft_strncpy(char *dst, const char *src, size_t len);
char	*ft_strdup(const char *s1);

#endif
