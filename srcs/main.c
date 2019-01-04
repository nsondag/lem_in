/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 15:22:31 by hvromman          #+#    #+#             */
/*   Updated: 2019/01/04 17:48:36 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

int main()
{
	t_a		ant;

	bzero(&ant, sizeof(ant));
	read_room(&ant);
	ft_printf("%d\n", ant.nb_ant);
	ft_printf("%s\n", ant.adj[0].name);
	ft_printf("%s\n", ant.adj[1].name);
	ft_printf("%s\n", ant.adj[2].name);
	ft_printf("%ld\n", ant.adj[3]);
	ft_printf("%d\n", ant.tab_size);
	ft_printf("%s\n", ant.buf);
	parse(&ant);
	ft_printf("%d\n", ant.adj[0].tab[0]);
	return (0);
}
