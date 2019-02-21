/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 10:16:54 by hvromman          #+#    #+#             */
/*   Updated: 2019/02/21 10:16:56 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

int		calculate_move(t_a *all, t_path **path, int nb_path)
{
	int		i;
	int		j;
	int		max;
	int		max_index;

	i = -1;
	while (++i < nb_path)
		path[i]->is_used = 1;
	j = 0;
	max = 0;
	max_index = 0;
	while (j < all->nb_ant)
	{
		i = -1;
		while (++i < nb_path)
			if (path[i]->is_used && path[i]->len_path > max)
			{
				max = path[i]->len_path;
				max_index = i;
			}
		
	}
}

int		calculate_start(t_a *all, t_path **path, int nb_path)
{
	int		i;

	all = NULL;
	path[0]->start = 0;
	i = 0;
	while (++i < nb_path)
		path[i]->start = path[i - 1]->start + path [i - 1]->nb_ant_in_path;
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

	i = -1;
	while (++i < all->nb_move)
	{
		j = -1;
		while (++j < nb_path)
		{
			first_ant = cut_negative(i - path[j]->nb_ant_in_path);
			last_ant = ft_min(i, path[j]->nb_ant_in_path);
			while (first_ant < last_ant)
			{
				ft_printf("L%d-%d ", path[j]->start + first_ant, path[j]->chain[i + first_ant]);
				first_ant++;
			}
		}
		ft_printf("\n");
	}
	return (0);
}
