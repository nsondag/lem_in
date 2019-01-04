/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 14:19:13 by hvromman          #+#    #+#             */
/*   Updated: 2019/01/04 18:13:00 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"
//#include <stdio.h>

int	get_tube(t_a *ant)
{
	char	*room1;
	char	*room2;
	int		dash;
	int		end;
	int		i;
	int		j;
	int		len_tab;

	i = 0;
	j = 0;
	dash = ft_indexof(ant->buf, '-');
	end = ft_indexof(ant->buf, '\0');
	if (ant->buf[0] != '#' && dash != -1)
	{
		room1 = ft_strsub(ant->buf, 0, dash);
		room2 = ft_strsub(ant->buf, dash + 1, end - dash);	
	}
	while (ft_strcmp(ant->adj[i].name, room1) > 0 && i < ant->tab_size)
		i++;
	while (ft_strcmp(ant->adj[j].name, room2) && j < ant->tab_size)
		j++;
	if (i == ant->tab_size || j == ant->tab_size)
	{
		free(ant->buf);
		return (INVALID);
	}
	len_tab = ft_tablen((void**)ant->adj[i].tab);
	ant->adj[i].tab = (int*)malloc(sizeof(int) * len_tab + 1);
	ant->adj[i].tab[len_tab] = j;
	len_tab = ft_tablen((void**)ant->adj[j].tab);
	ant->adj[j].tab = (int*)malloc(sizeof(int) * len_tab + 1);
	ant->adj[j].tab[len_tab] = i;
	free(ant->buf);
	return (0);
}

int	parser(t_a *ant)
{
	if (get_tube(ant) < 0)
		return (INVALID);
	while (get_next_line(0, &ant->buf) > 0)
		if (get_tube(ant) < 0)
			return (INVALID);
	return (0);
}

int main()
{
	t_a ant;

	parser(&ant);
	return (0);
}
