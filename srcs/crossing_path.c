/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crossing_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 15:58:39 by nsondag           #+#    #+#             */
/*   Updated: 2019/02/20 14:47:31 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

int crossing_path(t_path ***path, int f)
{
	int p1;
	int p2;
	int cross;
	int count;
	int	index1;
	int index2;
	t_path **path1;
	t_path **path2;

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
	index1 = p1;
	index2 = p2;
	count = 0;
	while (path[f][0]->chain[p1] == path[f][1]->chain[p2])
	{
		p1--;
		p2++;
		count++;
	}
	ft_printf("i1 %d i2 %d\n", index1, index2);
	ft_printf("count %d\n", count);
	int size1;
	int size2;
	size1 = index1 - index2 + path[f][1]->len_path - (2 * count) + 2;
	size2 = index2 - index1 + path[f][0]->len_path;
	ft_printf("size1 %d\n", size1);
	ft_printf("size2 %d\n", size2);
	if (!(path1 = malloc(sizeof(t_path**) * size1)))
		return (MERROR);
	if (!(path2 = malloc(sizeof(t_path**) * size2)))
		return (MERROR);
	if (count == 1)
		return (INVALID);
	return (VALID);
}
