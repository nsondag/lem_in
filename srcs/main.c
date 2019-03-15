/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 15:22:31 by hvromman          #+#    #+#             */
/*   Updated: 2019/03/15 21:03:37 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		find(t_a *all)
{
	int f;
	int i;
	int min;
	int k;

	f = 0;
	while (f < all->room[0].nb_tubes &&
			(all->path[f] = start_searching(all, all->path, f)))
	{
		change_all_len(all, all->room, all->path[f], f + 1);
		k = f;
		while (--k > -1)
			cross(all->path[f][f], all->path[f][k]);
		moves(all, all->path[f], f);
		smallest2(all);
		f++;
	}
	i = 0;
	min = 0;
	while (++i < f)
		(all->nb_move[min] > all->nb_move[i]) ? min = i : 0;
	all->nb_used = min;
	return (0);
}

int		main(void)
{
	t_a		ant;
	int		ret;

	ft_bzero(&ant, sizeof(ant));
	read_room(&ant);
	if (!(ant.room) || !(ant.room + 1) || !(ant.buf))
		exit_func(INVALID, &ant);
	(ret = parse(&ant)) ? exit_func(ret, &ant) : 0;
	search_for_deadend(ant.room, ant.nb_room);
	search_for_mult_path(&ant, 2);
	ant.start_room = 0;
	(smallest(&ant) && ant.direct != 1) ? exit_func(INVALID, &ant) : 0;
	ret = -1;
	while (++ret < ant.nb_data)
		ft_printf("%s\n", ant.data[ret]);
	if (ant.direct == 1)
		exit_func(print_all(ant.nb_ant, ant.room[1].name), &ant);
	modify_tubes_first(&ant);
	ant.path = ft_memalloc(sizeof(t_path**) *
			ant.room[ant.start_room].nb_tubes);
	ant.nb_move = ft_memalloc(sizeof(int) * ant.room[ant.start_room].nb_tubes);
	find(&ant);
	calculate_start(&ant, ant.path[ant.nb_used], ant.nb_used + 1);
	print_sol(&ant, ant.path[ant.nb_used], ant.nb_used);
	exit_func(0, &ant);
}
