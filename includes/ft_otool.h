/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/16 18:58:36 by kcosta            #+#    #+#             */
/*   Updated: 2018/08/16 22:34:07 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_OTOOL_H
# define FT_OTOOL_H

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

# define AR_MAGIC 0x72613c21
# define AR_CIGAM 0x213c6172

int		ft_error(char *filename, char* msg, int errnum);

#endif
