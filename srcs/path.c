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

int		**path(t_a *ant)
{
	int	**path;
	int	i;
	int	j;

	i = 0;
	if (!(path = malloc(sizeof(int*) * ant->adj[ant->start_room].len_tab)))
		return (MERROR);
	while (i < ant->adj[ant->start_room].len_tab)
	{
		j = 0;
		if (!(path[i] = malloc(sizeof(int) * ant->adj[!(ant->start_room)].dist)))
			return (MERROR);
		path[i][j++] = ant->adj[start_room].tab[i];
		while (ant->adj[path[i][j - 1]].len_tab == 2)
		{
			if (ant->adj[path[i][j]].tab[0] != path[i][j - 1])
				path[i][j] = ant->adj[path[i][j]];
		}
		
	}
}
