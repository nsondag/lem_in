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

	next = -1;
	while (ant->path[i][j] > 1 && ant->adj[ant->path[i][j]].len_tab == 2)
	{
		if (next != -1)
			ant->adj[next].is_passed = i;
		if (ant->adj[ant->path[i][j]].tab[0] == ant->start_room)
			next = ant->adj[ant->path[i][j]].tab[1];
		else if (ant->adj[ant->path[i][j]].tab[1] == ant->start_room)
			next = ant->adj[ant->path[i][j]].tab[0];
		else
			next = ant->adj[ant->adj[ant->path[i][j]].tab[0]].dist2 < ant->adj[ant->adj[ant->path[i][j]].tab[1]].dist2 ? ant->adj[ant->path[i][j]].tab[0] : ant->adj[ant->path[i][j]].tab[1];
		ant->path[i][++j] = next;
		ft_printf("path %d next %d\n", ant->path[i][0], next);
		ant->len_path[i]++;
	}
	return (next);
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
			min = -1;
			if (path[i][ant->len_path[i]] == !(ant->start_room))
			{
				i++;
				continue;
			}
			j = 0;
			//ft_printf("%d %d\n", i, path[i][0]);
			while (j < ant->adj[path[i][ant->len_path[i]]].len_tab)
			{
				if (ant->adj[ant->adj[path[i][ant->len_path[i]]].tab[j]].is_passed == -1)
				{
					if (min == -1 || ant->adj[min].dist2 > ant->adj[ant->adj[path[i][ant->len_path[i]]].tab[j]].dist2)
						min = ant->adj[path[i][ant->len_path[i]]].tab[j];
				}
				j++;
			}
			ft_printf("min %d\n", min);
			if (min == -1)
			{
				j = 0;
				while (j < ant->adj[path[i][ant->len_path[i]]].len_tab)
				{
					if (ant->adj[path[i][ant->len_path[i]]].tab[j] != ant->start_room && (min == -1 || ant->adj[min].dist2 > ant->adj[ant->adj[path[i][ant->len_path[i]]].tab[j]].dist2))
					{
						int l = 0;
						while (path[ant->adj[ant->adj[path[i][ant->len_path[i]]].tab[j]].is_passed][l] != ant->adj[path[i][ant->len_path[i]]].tab[j])
							l++;
						if (l > ant->len_path[i])
							min = ant->adj[path[i][ant->len_path[i]]].tab[j];
					}
					j++;
				}
			}
			ft_printf("i %d min %d\n", path[i][ant->len_path[i]], min);
			if (min == -1)
			{
				i++;
				continue;
			}
			ant->len_path[i]++;
			path[i][ant->len_path[i]] = min;
			//min = chained_path(ant, i, ant->len_path[i]);
			ft_printf("==%d %d %d==\n", path[i][0], path[i][1], path[i][2]);
			ft_printf("%d %d %d\n", path[i][0], path[i][ant->len_path[i] - 1], path[i][ant->len_path[i]]);
			if (ant->adj[min].is_passed != -1)
			{
				ft_printf("ici\n");
				if (ant->adj[min].is_passed == i)
				{
					ft_printf("fuck off %d %d\n", i, min);
					ant->len_path[i]--;
					i++;
					continue;
				}
				else
				{
					j = 0;
					while (path[ant->adj[min].is_passed][j] != min)
						j++;
					ft_printf("%d %d\n", min, ant->adj[min].is_passed);
					if (j > ant->len_path[i])
					{
						int tmp = j - 1;
						ft_printf("%d deleted, new_size %d\n", ant->adj[min].is_passed, j - 1);
						while (++j < ant->len_path[ant->adj[min].is_passed])
						{
							ant->len_path[i]++;
							path[i][ant->len_path[i]] = path[ant->adj[min].is_passed][j];
						}
						ft_printf("new_path end %d\n", path[i][ant->len_path[i]]);
						ant->len_path[ant->adj[min].is_passed] = tmp;
					}
				}
			}
//			int current_room = ant->adj[path[i][ant->len_path[i]]].tab[j];
//			for (int l = 0; l < ant->nb_path; l++)
//			{
//				if (l != i)
//				{
//					for (int m = ant->len_path[l] - 1; m >= 0; m--)
//					{
//						if (path[l][m] == current_room)
//						{
//
//						}
//					}
//				}
//			}
			found = 1;
			//ft_printf("--%d %d\n", i, min);
			if (min != !(ant->start_room))
				ant->adj[min].is_passed = i;
			for (int l = 0; l < ant->tab_size; l++)
				ft_printf("- %d %d\n", l, ant->adj[l].is_passed);
			//ant->longest_path = ft_max(ant->longest_path, ant->len_path[i]);
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
	ant->adj[ant->start_room].is_passed = -2;
	ant->adj[!(ant->start_room)].is_passed = -1;
	while (i < ant->adj[ant->start_room].len_tab)
	{
		if (!(ant->path[i] = malloc(sizeof(int) * ant->adj[ant->start_room].dist2 * 100))) // a modifier
			return (MERROR);
		ant->path[i][ant->len_path[i]] = ant->adj[ant->start_room].tab[i];
		ant->adj[ant->adj[ant->start_room].tab[i]].is_passed = i;
		int ret = chained_path(ant, i, ant->len_path[i]);
		if (ret != !(ant->start_room))
			ant->adj[ret].is_passed = i;
		ant->nb_path++;
		//ant->longest_path = ft_max(ant->longest_path, ant->len_path[i]);
		i++;
	}
	search_path(ant, ant->path);
	return (VALID);
}
