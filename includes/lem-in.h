/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 14:15:16 by hvromman          #+#    #+#             */
/*   Updated: 2019/01/04 16:10:57 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

#include "libft.h"
#include <stdlib.h>

typedef	struct	s_adj
{
	int		index;
	char	*name;
	int		*tab;
}				t_adj;

typedef struct	s_a
{
	int		nb_ant;
	int		tab_size;
	char	*start;
	char	*end;
	t_adj	*adj;
}				t_a;

#endif
