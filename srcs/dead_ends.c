/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead_ends.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 12:56:48 by nsondag           #+#    #+#             */
/*   Updated: 2019/01/08 14:58:10 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		dead_ends(t_a *ant)
{
	int i;
	int j;
	int	k;

	i = 2;
	while (i < ant->nb_room)
	{
		if (ant->room[i].nb_tubes < 2)
			ant->room[i] = ant->room[ant->nb_room - 1];
		j = 0;
		while (j < ant->nb_room)
		{
			k = 0;
			while (k < ant->room[j].nb_tubes)
			{
				if (ant->room[j].tubes[k].dest == ant->nb_room - 1)
					ant->room[j].tubes[k].dest = i;
				k++;
			}
			j++;
		}
		i++;
		ant->nb_room--;
	}
	return (VALID);
}
