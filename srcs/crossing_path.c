/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crossing_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 15:58:39 by nsondag           #+#    #+#             */
/*   Updated: 2019/02/17 19:16:23 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

int crossing_path(t_path ***path, int f)
{
	int p1;
	int p2;
	int cross;
	int count;

	cross = -1;
	p1 = 1;
	p2 = path[f][1]->len_path - 2;
	while (path[f][0]->chain[p1] != 1 && cross == -1)
	{
		while (p2 && cross == -1)
		{
			if (path[f][0]->chain[p1] == path[f][1]->chain[p2])
				break ;	
			p2--;
		}
		if (cross != -1)
			break ;
		p1++;
	}
	p1--;
	count = 0;
	while (path[f][0]->chain[p1] == path[f][1]->chain[p2])
	{
		p1--;
		p2++;
		count++;
	}
	if (count == 1)
		return (INVALID);
	return (VALID);
}
