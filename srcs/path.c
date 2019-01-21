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
	int		other_path;
	int		last_index;
	int		next_index;
	int		redirection;

	found = 1;
	while (found)
	{
		found = 0;
		i = 0;
		while (i < ant->nb_path)
		{
			last_index = path[i][ant->len_path[i]];
			ft_printf("i %d last_index %d\n", i , last_index);
			if (last_index == !(ant->start_room))
			{
				i++;
				continue;
			}
			min = -1;
			j = 0;
			while (j < ant->adj[last_index].len_tab)
			{
				next_index = ant->adj[last_index].tab[j];
				if (ant->adj[next_index].is_passed == -1)
				{
					if (min == -1 || ant->adj[min].dist2 > ant->adj[next_index].dist2)
						min = next_index;
				}
				j++;
			}
			other_path = -1;
			redirection = -1;
			ft_printf("min %d\n", min);
//			if (min == -1)
//			{
//				j = 0;
////				while (j < ant->adj[last_index].len_tab)
////				{
////					next_index = ant->adj[last_index].tab[j];
////					if (min == -1 || ant->adj[min].dist2 > ant->adj[next_index].dist2)
////					{
////						other_path = ant->adj[next_index].is_passed;
////						int l = 0;
////						while (path[other_path][l] != next_index)
////							l++;
////						if (l > ant->len_path[i])
////							min = next_index;
////					}
////					j++;
////				}
////				if (min != -1)
////					ant->len_path[other_path]--;
////			}
////			ft_printf("min %d\n", min);
//				while (j < ant->adj[last_index].len_tab)
//				{
//					next_index = ant->adj[last_index].tab[j];
//					if (next_index != ant->start_room && (min == -1 || ant->adj[min].dist2 > ant->adj[next_index].dist2))
//					{
//						other_path = ant->adj[next_index].is_passed;
//						int l = 0;
//						ft_printf("pas ici 0\n");
//						while (path[other_path][l] != next_index)
//						{
//							ft_printf("next ind %d l %d other path %d ind %d\n", next_index, l, other_path, path[other_path][l]);
//							l++;
//						}
//						ft_printf("l %d other path %d ind %d\n", l, other_path, path[other_path][l]);
//						int ok = 0;
//						ft_printf("pas ici 1\n");
//						while (--l >= 0 && !ok)
//						{
//							int tmp = path[other_path][l];
//							for (int m = 0; m < ant->adj[tmp].len_tab && !ok; m++)
//							{
//								if (ant->adj[ant->adj[tmp].tab[m]].is_passed == -1)
//								{
//									ok = 1;
//									redirection = tmp;
//								}
//							}
//						}
//						if (ok)
//							min = next_index;
//					}
//					j++;
//					ft_printf("pas ici 2\n");
//				}
//			}
			ft_printf("i %d min %d\n", last_index, min);
			if (min == -1)
			{
				if (ant->len_path[i])
					ant->len_path[i]--;
				ft_printf("victim\n");
				i++;
				continue;
			}
			ant->len_path[i]++;
			path[i][ant->len_path[i]] = min;
			//min = chained_path(ant, i, ant->len_path[i]);
			//ft_printf("==%d %d %d==\n", path[i][0], path[i][1], path[i][2]);
			ft_printf("%d %d %d\n", path[i][0], last_index, path[i][ant->len_path[i]]);
//			other_path = ant->adj[min].is_passed;
//			if (other_path != -1)
//			{
//				ft_printf("ici\n");
//				if (other_path == i)
//				{
//					ft_printf("fuck off %d %d\n", i, min);
//					ant->len_path[i]--;
//					i++;
//					continue;
//				}
//				else
//				{
//					j = 0;
//					while (path[other_path][j] != min)
//						j++;
//					ft_printf("%d %d\n", min, ant->adj[min].is_passed);
//					int tmp = j - 1;
//					ft_printf("%d deleted, new_size %d\n", other_path, j - 1);
//					while (++j <= ant->len_path[other_path])
//					{
//						ant->len_path[i]++;
//						path[i][ant->len_path[i]] = path[other_path][j];
//						ant->adj[path[other_path][j]].is_passed = i;
//					}
//					ft_printf("new_path end %d\n", path[i][ant->len_path[i]]);
//					ant->len_path[other_path] = tmp;
//					int ok = 0;
//					while (tmp > 0 && !ok)
//					{
//						int tmp2 = path[other_path][tmp];
//						for (int m = 0; m < ant->adj[tmp2].len_tab && !ok; m++)
//						{
//							if (ant->adj[ant->adj[tmp2].tab[m]].is_passed == -1 && path[other_path][tmp + 1] != ant->adj[tmp2].tab[m])
//							{
//								ok = 1;
//								ant->adj[path[other_path][tmp]].is_passed = -1;
//								path[other_path][tmp] = ant->adj[tmp2].tab[m];
//								ant->adj[ant->adj[tmp2].tab[m]].is_passed = other_path;
//							}
//						}
//						if (!ok)
//						{
//							ant->adj[path[other_path][tmp]].is_passed = -1;
//							ant->len_path[other_path]--;
//						}
//						tmp--;
//					}
//					ft_printf("other %d other end %d size %d\n", path[other_path][0], path[other_path][ant->len_path[other_path]], ant->len_path[other_path]);
//				}
//			}
			found = 1;
			if (min != !(ant->start_room))
				ant->adj[min].is_passed = i;
//			for (int l = 0; l < ant->nb_path; l++)
//				ft_printf("- %d %d\n", l, ant->adj[path[l][ant->len_path[l]]].dist2);
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
		i++;
	}
	search_path(ant, ant->path);
	return (VALID);
}
