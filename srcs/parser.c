/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 14:19:13 by hvromman          #+#    #+#             */
/*   Updated: 2019/01/10 14:52:36 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"
# include <stdio.h>

int		realloc_tab(t_adj *adj)
{
	int		*tmp;

	tmp = adj->tab;
	adj->len_tab++;
	if (!(adj->tab = (int*)malloc(sizeof(int) * (adj->len_tab))))
	{
		free(tmp);
		return (MERROR);
	}
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
	int		k;

	dash = ft_indexof(ant->buf, '-');
	end = ft_indexof(ant->buf, '\0');
	if (ant->buf[0] != '#' && dash != -1)
	{
		room1 = ft_strsub(ant->buf, 0, dash);
		room2 = ft_strsub(ant->buf, dash + 1, end - dash);	
	}
	else
		return (ant->buf[0] == '#' ? VALID : INVALID);
	i = 0;
	while (i < ant->tab_size && ft_strcmp(ant->adj[i].name, room1))
		i++;
	j = 0;
	while (j < ant->tab_size && ft_strcmp(ant->adj[j].name, room2))
		j++;
	if (i == ant->tab_size || j == ant->tab_size)
		return (INVALID);
	if (i == j)
		return (0);
	k = -1;
	while (++k < ant->adj[i].len_tab)
		if (j == ant->adj[i].tab[k])
			return (0);
	if (realloc_tab(&(ant->adj[i])))
		return (MERROR);
	ant->adj[i].tab[ant->adj[i].len_tab - 1] = j;
	if (realloc_tab(&(ant->adj[j])))
		return (MERROR);
	ant->adj[j].tab[ant->adj[j].len_tab - 1] = i;
	return (0);
}

int		parse(t_a *ant)
{
	int		ret;

	if (get_tube(ant) < 0)
		return (INVALID);
	while ((ret = get_next_line(0, &ant->buf)) > 0)
	{
		ft_printf("%s\n", ant->buf); //a remettre a la fin
		if ((ret = get_tube(ant)) < 0)
			return (ret);
		ft_strdel(&(ant->buf));
	}
	return (ret == -1 ? MERROR : VALID);
}
