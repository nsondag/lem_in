/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smallest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 15:35:57 by nsondag           #+#    #+#             */
/*   Updated: 2019/04/02 16:31:56 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** i = g[0]
** j = g[1]
** k = g[2]
** dist = g[3]
** room_discovered = g[4]
*/

int			smallest(t_a *ant)
{
	int		g[5];

	g[0] = -1;
	while (++g[0] < ant->nb_room)
		ant->room[g[0]].dist = -1;
	ant->room[0].dist = 0;
	g[3] = -1;
	g[4] = 1;
	while (g[4] && (g[0] = -1)
		&& !(g[4] = 0) && (g[3]++ || 1))
		while (++g[0] < ant->nb_room)
			if (ant->room[g[0]].dist == g[3] && (g[1] = -1))
				while (++g[1] < ant->room[g[0]].nb_tubes)
				{
					g[2] = ant->room[g[0]].tubes[g[1]].dest;
					if (ant->room[g[2]].dist < 0)
					{
						ant->room[g[2]].dist = ant->room[g[0]].dist + 1;
						ant->room[g[0]].tubes[g[1]].tree = 1;
						g[4] = 1;
					}
				}
	ant->escape = ant->room[1].dist + 1;
	return (ant->room[1].dist == -1 ? INVALID : VALID);
}

static int	instanciate_smallest(t_a *ant)
{
	int		i;
	int		j;

	i = 0;
	while (i < ant->nb_room)
	{
		j = -1;
		while (++j < ant->room[i].nb_tubes)
			ant->room[i].tubes[j].tree = 0;
		ant->room[i].dist = -1;
		ant->room[i].coming_from = -1;
		i++;
	}
	ant->room[0].dist = 0;
	ant->room[0].space = 0;
	return (0);
}

/*
** i = g[1]
** j = g[2]
** dest = g[3]
** len = g[4]
** dist = g[5]
** discovered = g[6]
*/

static int	block_central(t_a *ant, int g[8])
{
	g[4] = ant->room[g[1]].tubes[g[2]].len;
	g[3] = ant->room[g[1]].tubes[g[2]].dest;
	if (ant->room[g[3]].dist == -1 && ant->room[g[1]].dist + g[4] < g[5] &&
		(ant->room[g[1]].is_passed == ant->room[g[3]].is_passed
	|| ant->room[g[1]].is_passed == ant->room[g[1]].coming_from))
	{
		ant->room[g[3]].dist = ant->room[g[1]].dist + g[4];
		ant->room[g[3]].space = ant->room[g[1]].space + 1;
		ant->room[g[1]].tubes[g[2]].tree = 1;
		ant->room[g[3]].coming_from = ant->room[g[1]].is_passed;
		g[6] = 1;
	}
	return (0);
}

int			smallest2(t_a *ant)
{
	int		g[7];

	instanciate_smallest(ant);
	g[5] = -1;
	while (g[5] < 1000 && ant->room[!(ant->start_room)].dist == -1)
	{
		g[6] = 0;
		g[5]++;
		g[1] = -1;
		while (++g[1] < ant->nb_room)
			if (ant->room[g[1]].dist != -1 && (g[2] = -1))
				while (++g[2] < ant->room[g[1]].nb_tubes)
					block_central(ant, g);
		if (g[6])
			g[5]--;
	}
	ant->escape = ant->room[1].space + 1;
	return (VALID);
}
