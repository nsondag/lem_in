/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 15:22:31 by hvromman          #+#    #+#             */
/*   Updated: 2019/03/06 15:34:37 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
# include <time.h>

int		find(t_a *all)
{
	int f;
	int i;
	int min;
	int k;

	f = 0;
	ft_printf("__ %d\n", all->room[0].nb_tubes);
	while (f < all->room[0].nb_tubes && (all->path[f] = start_searching(all, all->path, f)))
	{
		for (int l = 0; ft_printf("\n") && l <= f; l++)
			for (int m = 0; m < all->path[f][l]->len_path; m++)
				ft_printf("%d ", all->path[f][l]->chain[m]);
		change_all_len(all, all->room, all->path[f], f + 1);
		k = f;
		while (--k > -1)
			crossing_path(all->path, f, k);
		moves(all, all->path[f], f);
		smallest2(all);
		f++;
	}
	i = 0;
	min = 0;
	ft_printf("move[%d] : %d\n", 0, all->nb_move[0]);
	while (++i < f)
	{
		if (all->nb_move[min] > all->nb_move[i])
			min = i;
		ft_printf("move[%d] : %d\n", i, all->nb_move[i]);
	}
	ft_printf("move : %d, nb_path : %d\n", all->nb_move[min], min + 1);
	all->nb_used = min;
	return (0);
}

int		main(void)
{
	t_a		ant;
	int		ret;

	ft_bzero(&ant, sizeof(ant));
	clock_t e = clock();
	read_room(&ant);
	if (!(ant.room) || !(ant.room + 1) || !(ant.buf))
		exit_func(INVALID, &ant);
	clock_t f = clock();
	ft_printf("read_room %f\n%>", (f-e) / (double) CLOCKS_PER_SEC, 2);
	if ((ret = parse(&ant)))
		exit_func(ret, &ant);
	if (ant.direct == 1)
	{
		print_all(ant.nb_ant);
		return (0);
	}
	clock_t g = clock();
	ft_printf("parse %f\n%>", (g-f) / (double) CLOCKS_PER_SEC, 2);
	search_for_deadend(ant.room, ant.nb_room);
	search_for_mult_path(&ant, 2);
	ant.start_room = 0;
	if (smallest(&ant))
		exit_func(INVALID, &ant);
	modify_tubes_first(&ant);
	ant.path = malloc(sizeof(t_path**) * ant.room[ant.start_room].nb_tubes);
	ant.nb_move = ft_memalloc(sizeof(int) * ant.room[ant.start_room].nb_tubes);
	clock_t u = clock();
	find(&ant);
	clock_t v = clock();
	ft_printf("find %f\n%>", (v-u) / (double) CLOCKS_PER_SEC, 2);
	calculate_start(&ant, ant.path[ant.nb_used], ant.nb_used + 1);
	ft_printf("-----\n%s\n-----\n", ant.data);
	print_sol(&ant, ant.path[ant.nb_used], ant.nb_used);
	exit_func(0, &ant);
}
