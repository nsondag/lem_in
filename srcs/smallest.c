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

int	smallest(t_a *ant)
{
	int j;
	int	k;

	ant->adj[0].dist = 0;
	while (ant->adj)
	{
		ant->adj->dist = -1;
		ant->adj++;
	}
	while (ant->adj)
	{
		j = 0;
		while (ant->adj->tab[j])
		{	
			k = ant->adj->tab[j];
			if (ant->adj[k].dist < 0)
				ant->adj[k].dist = ant->adj->dist + 1;
			j++;
		}
		ant->adj++;
	}
	return (0);
}
