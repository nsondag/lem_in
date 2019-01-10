/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supp_mult_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 17:20:36 by hvromman          #+#    #+#             */
/*   Updated: 2019/01/09 17:20:38 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

int		supp_room_from_other(int index_to_supp, t_adj *other)
{
	int		i;

	i = 0;
	while (other->tab[i] != index_to_supp)
		i++;
	other->len_tab--;
	other->tab[i] = other->tab[other->len_tab];
	return (0);
}

int		free_one_room(t_a *all, int index)
{
	free(all->adj[index].tab);
	free(all->adj[index].name);
	bzero(&(all->adj[index]), sizeof(t_adj) * index);
	return (0);
}

int		supp_2comp_room(t_adj *adj, int index)
{
	int		to_return;

	ft_printf("-- room deleted with 2 companions : %d\n", index);
	if (adj[adj[index].tab[0]].len_tab == 2)
		to_return = adj[index].tab[0];
	else
		to_return = adj[index].tab[1];
	supp_room_from_other(index, &(adj[adj[index].tab[0]]));
	supp_room_from_other(index, &(adj[adj[index].tab[1]]));
	adj[index].len_tab = 0;
	return (to_return);
}

int		supp_1comp_room(t_adj *adj, int index)
{
	int		to_return;

	ft_printf("-- room deleted with 1 companion : %d\n", index);
	to_return = adj[index].tab[0];
	supp_room_from_other(index, &(adj[adj[index].tab[0]]));
	adj[index].len_tab = 0;
	return (to_return);
}

int		supp_chained(t_adj *adj, int index)
{
	int		next;

	if (adj[index].len_tab == 2)
		next = supp_2comp_room(adj, index);
	else
		next = index;
	while (next > 1 && adj[next].len_tab == 1)
		next = supp_1comp_room(adj, next);
	return (0);
}

int		search_for_side(t_adj *adj, int index, int *direction, int *size)
{
	int		refer;

	refer = adj[index].tab[*direction];
	if (refer < 2 || adj[refer].len_tab != 2)
	{
		*direction = index;
		return (refer);
	}
	(*size)++;
	*direction = adj[refer].tab[0] == index;
	return (search_for_side(adj, refer, direction, size));
}

int		search_for_deadend(t_adj *adj, int tab_size)
{
	int		i;

	i = 2;
	while (i < tab_size)
	{
		if (adj[i].len_tab == 1)
		{
			supp_chained(adj, i);
			i = 1;
		}
		i++;
	}
	return (0);
}

int		search_for_mult_path(t_a *all, int start)
{
	int		i;
	int		size_of_path;
	int		first_side;
	int		second_side;
	int		adj_first_side;
	int		j;
	int		k;
	int		tmp_path_size;
	int		l;

	i = start;
	while (i < all->tab_size && all->adj[i].len_tab != 2)
		i++;
	if (i == all->tab_size)
		return (NONE_LEFT);
	size_of_path = 1;
	adj_first_side = 0;
	second_side = search_for_side(all->adj, i, &adj_first_side, &size_of_path);
	adj_first_side = 1;
	first_side = search_for_side(all->adj, i, &adj_first_side, &size_of_path);
	if (first_side + second_side == 1)
		return (search_for_mult_path(all, i + 1));
	j = 0;
	while (j < all->adj[first_side].len_tab)
	{
		k = all->adj[first_side].tab[j];
		if (k == second_side)
		{
			supp_chained(all->adj, adj_first_side);
			return (search_for_mult_path(all, 2));
		}
		else if (k != adj_first_side && all->adj[k].len_tab == 2)
		{
			tmp_path_size = 1;
			l = all->adj[k].tab[0] == j ? 1 : 0;
			if (search_for_side(all->adj, k, &l, &tmp_path_size) == second_side)
			{
				supp_chained(all->adj, size_of_path < tmp_path_size ? k : adj_first_side);

			}
		}
		j++;
	}
	return (search_for_mult_path(all, i + 1));
}
