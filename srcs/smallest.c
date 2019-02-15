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
			if (ant->room[i].dist == dist)// && i != !(ant->start_room))
			{
				j = 0;
				while (j < ant->room[i].nb_tubes)
				{
					k = ant->room[i].tubes[j].dest;
					if (ant->room[k].dist < 0)
					{
						ant->room[k].dist = ant->room[i].dist + 1;
						ant->room[i].tubes[j].tree = 1;
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
	ant->escape = ant->room[!(ant->start_room)].dist + 1;
	for (int m = 0; m < ant->nb_room; m++)
		ft_printf("-- d1 %d: %d\n", m, ant->room[m].dist);
	return (VALID);
}

int		smallest2(t_a *ant)
{
	int		i;
	int		j;
	int		k;
	int		len;
	int		dist;

	i = 0;
	while (i < ant->nb_room)
	{
		j = -1;
		while (++j < ant->room[i].nb_tubes)
			ant->room[i].tubes[j].tree = 0;
		ant->room[i].dist = 2000000;
		i++;
	}
	ant->room[ant->start_room].dist = 0;
	ant->room[ant->start_room].space = 0;
	dist = -1;
	while (dist < 1000 && ant->room[!(ant->start_room)].dist == 2000000)
	{
		dist++;
		i = 0;
		while (i < ant->nb_room)
		{
			j = 0;
			while (j < ant->room[i].nb_tubes)
			{
				len = ant->room[i].tubes[j].len;
				k = ant->room[i].tubes[j].dest;
				if (ant->room[i].dist != 2000000 && ant->room[i].dist + len < dist && ant->room[k].dist == 2000000)
				{
					ant->room[k].dist = ant->room[i].dist + len;
					ant->room[k].space = ant->room[i].space + 1;
					ant->room[i].tubes[j].tree = 1;
					if (!len)
						i = -1;
				}
				j++;
			}
			i++;
		}
	}
	if (ant->room[!(ant->start_room)].dist == 2000000)
		return (INVALID);
	ant->escape = ant->room[!(ant->start_room)].space + 1;
	for (int m = 0; m < ant->nb_room; m++)
		ft_printf("-- d1 %d: %d: %d\n", m, ant->room[m].dist, ant->room[m].space);
	return (VALID);
}
