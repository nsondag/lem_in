/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smallest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 15:35:57 by nsondag           #+#    #+#             */
/*   Updated: 2019/01/08 12:46:36 by nsondag          ###   ########.fr       */
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
	while (i < ant->nb_room)
	{
		ant->room[i].dist = -1;
		i++;
	}
	ant->room[ant->start_room].dist = 0;
	dist = -1;
	room_discovered = 1;
	while (room_discovered)
	{
		dist++;
		i = 0;
		room_discovered = 0;
		while (i < ant->nb_room)
		{
			if (ant->room[i].dist == dist && i != !(ant->start_room))
			{
				j = 0;
				while (j < ant->room[i].nb_tubes)
				{
					k = ant->room[i].tubes[j].dest;
					if (ant->room[k].dist < 0)
					{
						ant->room[k].dist = ant->room[i].dist + 1;
						room_discovered = 1;
					}
					j++;
				}
			}
			i++;
		}
	}
	if (ant->room[!(ant->start_room)].dist == -1)
		return (INVALID);
	for (int m = 0; m < ant->nb_room; m++)
		ft_printf("-- d1 %d: %d\n", m, ant->room[m].dist);
	return (VALID);
}

int		smallest2(t_a *ant)
{
	int		i;
	int		j;
	int		k;
	int		dist;
	int		room_discovered;

	i = 0;
	while (i < ant->nb_room)
	{
		ant->room[i].dist2 = -1;
		i++;
	}
	ant->room[!(ant->start_room)].dist2 = 0;
	dist = -1;
	room_discovered = 1;
	while (room_discovered)
	{
		dist++;
		i = 0;
		room_discovered = 0;
		while (i < ant->nb_room)
		{
			if (ant->room[i].dist2 == dist && i != ant->start_room)
			{
				j = 0;
				while (j < ant->room[i].nb_tubes)
				{
					k = ant->room[i].tubes[j].dest;
					if (ant->room[k].dist2 < 0)
					{
						ant->room[k].dist2 = ant->room[i].dist2 + 1;
						room_discovered = 1;
					}
					j++;
				}
			}
			i++;
		}
	}
	for (int m = 0; m < ant->nb_room; m++)
		ft_printf("-- d2 %d: %d\n", m, ant->room[m].dist2);
	return (VALID);
}
