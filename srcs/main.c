/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 15:22:31 by hvromman          #+#    #+#             */
/*   Updated: 2019/03/11 14:06:11 by nsondag          ###   ########.fr       */
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
	while (f < all->room[0].nb_tubes && (all->path[f] = start_searching(all, all->path, f)))
	{
//		for (int l = 0; ft_printf("\n") && l <= f; l++)
//			for (int m = 0; m < all->path[f][l]->len_path; m++)
//				ft_printf("%d ", all->path[f][l]->chain[m]);
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
	{
		if (all->nb_move[min] > all->nb_move[i])
			min = i;
	}
	all->nb_used = min;
	//ft_printf("__ move:%d\n", all->nb_move[all->nb_used]);
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
	clock_t g = clock();
	ft_printf("parse %f\n%>", (g-f) / (double) CLOCKS_PER_SEC, 2);
	for (int l = 0; l < ant.nb_data; l++)
		ft_printf("%s\n", ant.data[l]);
	if (ant.direct == 1)
		exit_func(print_all(ant.nb_ant, ant.room[1].name), &ant);
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
	print_sol(&ant, ant.path[ant.nb_used], ant.nb_used);
	exit_func(0, &ant);
}
