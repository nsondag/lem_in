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

	while (ant->path[i][j] > 1 && ant->adj[ant->path[i][j]].len_tab == 2)
	{
		next = ant->adj[ant->adj[ant->path[i][j]].tab[0]].dist2 < ant->adj[ant->adj[ant->path[i][j]].tab[1]].dist2 ? ant->adj[ant->path[i][j]].tab[0] : ant->adj[ant->path[i][j]].tab[1];
		ant->path[i][++j] = next;
		ant->len_path[i]++;
	}
	return (0);
}

int		search_path(t_a *ant, int **path)
{
	int		i;
	int		j;
	int		min;
	int		found;

	found = 1;
	while (found)
	{
		found = 0;
		i = 0;
		while (i < ant->nb_path)
		{
			min = 0;
			if (path[i][ant->len_path[i]] == 1)
			{
				i++;
				continue;
			}
			j = 1;
			ft_printf("%d %d\n", i, path[i][0]);
			while (j < ant->adj[path[i][ant->len_path[i]]].len_tab)
			{
				if (!(ant->adj[ant->adj[path[i][ant->len_path[i]]].tab[j]].is_passed) && (found = 1) && ant->adj[ant->adj[path[i][ant->len_path[i]]].tab[min]].dist2 > ant->adj[ant->adj[path[i][ant->len_path[i]]].tab[j]].dist2)
				{
					min = j;
				}
				j++;
			}
			if (!found)
			{
				
			}
			ft_printf("--%d %d\n", i, ant->adj[path[i][ant->len_path[i]]].tab[min]);
			if (ant->adj[path[i][ant->len_path[i]]].tab[min] != 1)
				ant->adj[ant->adj[path[i][ant->len_path[i]]].tab[min]].is_passed = 1;
			path[i][ant->len_path[i] + 1] = ant->adj[path[i][ant->len_path[i]]].tab[min];
			ant->len_path[i]++;
			i++;
		}
	}
	return (VALID);
}

int		path(t_a *ant)
{
	int		i;

	if (!(ant->path = malloc(sizeof(int*) * ant->adj[ant->start_room].len_tab)))
		return (MERROR);
	if (!(ant->len_path = ft_memalloc(sizeof(int) * ant->adj[ant->start_room].len_tab)))
		return (MERROR);
	i = 0;
	ant->adj[ant->start_room].is_passed = 1;
	while (i < ant->adj[ant->start_room].len_tab)
	{
		if (!(ant->path[i] = malloc(sizeof(int) * ant->adj[!(ant->start_room)].dist)))
			return (MERROR);
		ant->path[i][ant->len_path[i]] = ant->adj[ant->start_room].tab[i];
		ant->adj[ant->adj[ant->start_room].tab[i]].is_passed = 1;
		chained_path(ant, i, ant->len_path[i]);
		i++;
		ant->nb_path++;
	}
	search_path(ant, ant->path);
	return (VALID);
}
