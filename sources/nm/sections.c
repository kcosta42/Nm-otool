/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sections.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/16 11:20:49 by kcosta            #+#    #+#             */
/*   Updated: 2018/08/16 16:46:42 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

t_section	*sections(void)
{
	static t_section	sections = {0, 0, 0, 0};

	return (&sections);
}

void		reset_sections(void)
{
	sections()->index = 0;
	sections()->text = 0;
	sections()->data = 0;
	sections()->bss = 0;
}
