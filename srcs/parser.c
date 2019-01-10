/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 14:19:13 by hvromman          #+#    #+#             */
/*   Updated: 2019/01/08 14:14:25 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"
# include <stdio.h>

int		realloc_tab(t_adj *adj)
{
	int		*tmp;

	tmp = adj->tab;
	adj->len_tab++;
	adj->tab = (int*)malloc(sizeof(int) * (adj->len_tab));
	memcpy(adj->tab, tmp, sizeof(int) * (adj->len_tab - 1));
	free(tmp);
	return (0);
}

int		get_tube(t_a *ant)
{
	char	*room1;
	char	*room2;
	int		dash;
	int		end;
	int		i;
	int		j;

	i = 0;
	j = 0;
	dash = ft_indexof(ant->buf, '-');
	end = ft_indexof(ant->buf, '\0');
	if (ant->buf[0] != '#' && dash != -1)
	{
		room1 = ft_strsub(ant->buf, 0, dash);
		room2 = ft_strsub(ant->buf, dash + 1, end - dash);	
	}
	else
		return (ant->buf[0] == '#' ? VALID : INVALID);
	while (i < ant->tab_size && ft_strcmp(ant->adj[i].name, room1))
		i++;
	while (j < ant->tab_size && ft_strcmp(ant->adj[j].name, room2))
		j++;
	if (i == ant->tab_size || j == ant->tab_size)
		return (INVALID);
	ft_printf("-- i %d | j %d\n", i, j);
	realloc_tab(&(ant->adj[i]));
	ant->adj[i].tab[ant->adj[i].len_tab - 1] = j;
	realloc_tab(&(ant->adj[j]));
	ant->adj[j].tab[ant->adj[j].len_tab - 1] = i;
	ft_strdel(&(ant->buf));
	return (0);
}

int	parse(t_a *ant)
{
	if (get_tube(ant) < 0)
		return (INVALID);
	while (get_next_line(0, &ant->buf) > 0)
	{
		ft_printf("%s\n", ant->buf); // pas retirer
		if (get_tube(ant) < 0)
			return (INVALID);
	}
	ft_printf("\n");
	for (int m = 0; m < ant->tab_size; m++)
	{
		ft_printf("-- len_tab %d : %d --\n", m, ant->adj[m].len_tab);
		for (int l = 0; l < ant->adj[m].len_tab; l++)
			ft_printf("-- %d: %d: %d\n", m, l, ant->adj[m].tab[l]);
		ft_printf("\n");
	}
	return (0);
}
