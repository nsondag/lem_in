/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 15:22:31 by hvromman          #+#    #+#             */
/*   Updated: 2019/01/27 21:10:16 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

int		find(t_a *all)
{
	int f;
	int i;
	int min;

	f = 0;
	while ((all->path[f] = start_searching(all, all->path, f)))
	{
		ft_printf("path[%d] ok\n", f);
		change_all_len(all, all->room, all->path[f], f);
		ft_printf("1\n");
		crossing_path(all->path, f);
		ft_printf("2\n");
		moves(all, all->path[f], f);
		ft_printf("3\n");
		if (smallest2(all))
			exit_func(INVALID, all);
		ft_printf("4\n");
		f++;
	}
	i = 0;
	min = 0;
	while (++i < f)
	{
		if (all->nb_move[min] > all->nb_move[i])
			min = i;
	}
	ft_printf("move : %d, nb_path : %d\n", all->nb_move[min], min + 1);
	all->nb_used = min;
	return (0);
}

int		main()
{
	t_a		ant;
	int		ret;

	ft_bzero(&ant, sizeof(ant));
	read_room(&ant);
	if (!(ant.room) || !(ant.room + 1) || !(ant.buf))
		exit_func(INVALID, &ant);
	if ((ret = parse(&ant)))
		exit_func(ret, &ant);
	ft_printf("-----\n%s\n-----\n", ant.data);
	search_for_deadend(ant.room, ant.nb_room);
	search_for_mult_path(&ant, 2);
	ant.start_room = 0;
	if (smallest(&ant))
		exit_func(INVALID, &ant);
	int c = 0;
	for (int m = 0; m < ant.nb_room; m++)
		if (ant.room[m].nb_tubes > 2)
			c++;
	modify_tubes_first(&ant);
	int m = 0;
	for (int l = 0; l < ant.nb_room; l++)
		if (ant.room[l].dist != -1)
			m++;
	ft_printf("nb start_room connection(s) : %d\n", ant.room[ant.start_room].nb_tubes);
	ft_printf("nb not tube room(s) : %d\n", c);
	ft_printf("nb room(s) connected : %d / %d\n", m, ant.nb_room);

	ant.path = malloc(sizeof(t_path**) * ant.room[ant.start_room].nb_tubes);
	ant.nb_move = ft_memalloc(sizeof(int) * ant.room[ant.start_room].nb_tubes);
	find(&ant);
	calculate_start(&ant, ant.path[ant.nb_used], ant.nb_used + 1);
	print_sol(&ant, ant.path[ant.nb_used], ant.nb_used + 1);
	return (0);
}
