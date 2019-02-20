/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crossing_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 15:58:39 by nsondag           #+#    #+#             */
/*   Updated: 2019/02/20 15:47:27 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

int crossing_path(t_path ***path, int f)
{
	int i;
	int j;
	int p1;
	int p2;
	int cross;
	int count;
	int	index1;
	int index2;
	t_path *path1;
	t_path *path2;

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
	if (count == 1)
		return (INVALID);
	ft_printf("------------new_path----------------\n");
	int size1;
	int size2;
	size1 = index1 - index2 + path[f][1]->len_path - (2 * count) + 2;
	size2 = index2 - index1 + path[f][0]->len_path;
	if (!(path1 = malloc(sizeof(t_path))))
		return (MERROR);
	if (!(path2 = malloc(sizeof(t_path))))
		return (MERROR);
	if (!(path1->chain = malloc(sizeof(int) * size1)))
		return (MERROR);
	if (!(path2->chain = malloc(sizeof(int) * size2)))
		return (MERROR);
	i = -1;
	while (++i < index1 - count + 2)
		path1->chain[i] = path[f][0]->chain[i];
	j = 0;
	i--;
	while (++i < size1)
		path1->chain[i] = path[f][1]->chain[index2 + j++ + count];
	i = -1;
	while (++i < index2)
		path2->chain[i] = path[f][1]->chain[i];
	j = 0;
	i--;
	while (++i < size2)
		path2->chain[i] = path[f][0]->chain[index1 + j++];
	//print new paths
	i = 0;
	while (i < size1)
		ft_printf("--- %d\n", path1->chain[i++]);
	i = 0;
	ft_printf("\n");
	while (i < size2)
		ft_printf("--- %d\n", path2->chain[i++]);
	return (VALID);
}
