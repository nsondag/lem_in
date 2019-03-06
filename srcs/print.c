/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 10:16:54 by hvromman          #+#    #+#             */
/*   Updated: 2019/03/02 18:27:03 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** i = g[0]
** j = g[1]
** max = g[2]
** max_index = g[3]
** sum_diff = g[4]
*/

int		calculate_move(t_a *all, t_path **path, int nb_path)
{
	int		g[5];

	g[1] = 0;
	while (g[1] < all->nb_ant && (g[0] = -1))
	{
		g[2] = 0;
		g[3] = 0;
		g[4] = 0;
		while (++g[0] < nb_path)
			if (path[g[0]]->is_used && path[g[0]]->len_path > g[2]
				&& (g[2] = path[g[0]]->len_path))
				g[3] = g[0];
		g[0] = -1;
		while (++g[0] < nb_path)
			if (path[g[0]]->is_used && g[0] != g[3])
				g[4] += g[2] - path[g[0]]->len_path;
		if (all->nb_ant - g[1] <= g[4])
			path[g[3]]->is_used = 0;
		else if ((g[0] = -1))
			while (++g[0] < nb_path && g[1] < all->nb_ant)
				if (path[g[0]]->is_used && ++g[1])
					path[g[0]]->nb_ant_in_path++;
	}
	return (0);
}

int		moves(t_a *all, t_path **path, int nb_path)
{
	int		i;

	i = -1;
	while (++i <= nb_path)
		path[i]->is_used = 1;
	calculate_move(all, path, nb_path + 1);
	i = -1;
	while (++i <= nb_path)
	{
		ft_printf("%d %d %d\n", path[i]->chain[1], path[i]->nb_ant_in_path, path[i]->len_path);
		if (path[i]->nb_ant_in_path)
			all->nb_move[nb_path] = ft_max(all->nb_move[nb_path],
			path[i]->nb_ant_in_path + path[i]->len_path - 1);
	}
	return (0);
}

int		calculate_start(t_a *all, t_path **path, int nb_path)
{
	int		i;

	all = NULL;
	path[0]->start = 0;
	i = 0;
	while (++i < nb_path)
		path[i]->start = path[i - 1]->start + path[i - 1]->nb_ant_in_path;
	return (0);
}

int		cut_negative(int nb)
{
	return (nb > 0 ? nb : 0);
}

int		print_sol(t_a *all, t_path **path, int nb_path)
{
	int		i;
	int		j;
	int		first_ant;
	int		last_ant;
	int		first;

	i = -1;
	while (++i < all->nb_move[nb_path] && (j = -1))
	{
		first = 1;
		while (++j < nb_path + 1)
		{
			first_ant = cut_negative(i - path[j]->len_path + 1);
			last_ant = ft_min(i, path[j]->nb_ant_in_path);
			while (first_ant < last_ant)
			{
				ft_printf(first ? "L%d-%d" : " L%d-%d", path[j]->start +
						first_ant + 1, path[j]->chain[i - first_ant]);
				first = 0;
				first_ant++;
			}
		}
		ft_printf("\n");
	}
	return (0);
}
