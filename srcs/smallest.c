/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smallest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 15:35:57 by nsondag           #+#    #+#             */
/*   Updated: 2019/01/05 19:26:59 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

int		smallest(t_a *ant)
{
	int		i;
	int		j;
	int		k;
	int		dist;
	int		room_discovered;

	i = 0;
	while (i < ant->tab_size)
	{
		ant->adj[i].dist = -1;
		i++;
	}
	ant->adj[ant->start_room].dist = 0;
	dist = -1;
	while (ant->adj[!(ant->start_room)].dist == -1)
	{
		dist++;
		i = 0;
		room_discovered = 0;
		while (i < ant->tab_size)
		{
			if (ant->adj[i].dist == dist)
			{
				ft_printf("i %d\n", i);
				j = 0;
				while (j < ant->adj[i].len_tab)
				{
					ft_printf("j %d\n", j);
					k = ant->adj[i].tab[j];
					ft_printf("k %d\n", k);
					//ant->adj[k].is_passed = 1;
					if (ant->adj[k].dist < 0)
					{
						ant->adj[k].dist = ant->adj[i].dist + 1;
						room_discovered = 1;
					}
					j++;
				}
			}
			i++;
		}
		if (!room_discovered)
			return (INVALID);
	}
	for (int m = 0; m < ant->tab_size; m++)
		ft_printf("%d: %d\n", m, ant->adj[m].dist);
	return (VALID);
}
