/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 21:46:14 by nsondag           #+#    #+#             */
/*   Updated: 2019/01/11 16:26:28 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

int		chained_path(t_a *ant, int  i, int j)
{
	int		next;

	while (ant->adj[ant->path[i][j]].len_tab == 2)
	{
		next = ant->adj[ant->adj[ant->path[i][j]].tab[0]].dist2 < ant->adj[ant->adj[ant->path[i][j]].tab[1]].dist2 ? ant->adj[ant->path[i][j]].tab[0] : ant->adj[ant->path[i][j]].tab[1];
		ant->path[i][++j] = next;
		ant->len_path[i]++;
	}
	return (0);
}

int		path(t_a *ant)
{
	int		i;
	int		j;

	if (!(ant->path = malloc(sizeof(int*) * ant->adj[ant->start_room].len_tab)))
		return (MERROR);
	if (!(ant->len_path = ft_memalloc(sizeof(int) * ant->adj[ant->start_room].len_tab)))
		return (MERROR);
	i = 0;
	while (i < ant->adj[ant->start_room].len_tab)
	{
		j = 0;
		if (!(ant->path[i] = malloc(sizeof(int) * ant->adj[!(ant->start_room)].dist)))
			return (MERROR);
		ant->path[i][j] = ant->adj[ant->start_room].tab[i];
		ant->len_path[i]++;
		chained_path(ant, i, j);
		i++;
		ant->nb_path++;
	}
	return (VALID);
}
