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

#include "lem-in.h"

int		dead_ends(t_a *ant)
{
	int i;
	int j;
	int	k;

	i = 2;
	while (i < ant->tab_size)
	{
		if (ant->adj[i].len_tab < 2)
			ant->adj[i] = ant->adj[ant->tab_size - 1];
		j = 0;
		while (j < ant->tab_size)
		{
			k = 0;
			while (k < ant->adj[j].len_tab)
			{
				if (ant->adj[j].tab[k] == ant->tab_size - 1)
				{
					ant->adj[j].tab[k] = i;
				}
				k++;
			}
			j++;
		}
		i++;
		ant->tab_size--;
	}
	return (VALID);
}
