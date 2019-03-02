/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crossing_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 15:58:39 by nsondag           #+#    #+#             */
/*   Updated: 2019/03/02 20:02:52 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int crossing_path(t_path ***path, int f)
{
	int i;
	int j;
	int p1;
	int p2;
	int count;
	int	index1;
	int index2;
	int *path1;
	int *path2;
	int	size1;
	int	size2;

	p1 = 1;
	while (path[f][0]->chain[p1] != 1)
	{
		p2 = path[f][1]->len_path - 2;
		while (p2)
		{
			if (path[f][0]->chain[p1] == path[f][1]->chain[p2])
				break ;	
			p2--;
		}
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
	if (count == 0)
		return (VALID);
	ft_printf("------------new_path----------------\n");
	size1 = index1 - index2 + path[f][1]->len_path - (2 * count) + 2;
	size2 = index2 - index1 + path[f][0]->len_path;
	if (!(path1 = malloc(sizeof(int) * size1)))
		return (MERROR);
	if (!(path2 = malloc(sizeof(int) * size2)))
		return (MERROR);
	i = -1;
	while (++i < index1 - count + 2)
		path1[i] = path[f][0]->chain[i];
	j = 0;
	while (i < size1)
		path1[i++] = path[f][1]->chain[index2 + j++ + count];
	i = -1;
	while (++i < index2)
		path2[i] = path[f][1]->chain[i];
	j = 0;
	while (i < size2)
		path2[i++] = path[f][0]->chain[index1 + j++];
	path[f][0]->len_path = size1;
	path[f][1]->len_path = size2;
	free(path[f][0]->chain);
	free(path[f][1]->chain);
	if (!(path[f][0]->chain = malloc(sizeof(int) * size1)))
		return (MERROR);
	if (!(path[f][1]->chain = malloc(sizeof(int) * size2)))
		return (MERROR);
	ft_memcpy(path[f][0]->chain, path1, 4 * size1);	
	ft_memcpy(path[f][1]->chain, path2, 4 * size2);	
	//print new paths
	i = 0;
	while (i < size1)
		ft_printf("--- %d\n", path[f][0]->chain[i++]);
	i = 0;
	ft_printf("\n");
	while (i < size2)
		ft_printf("--- %d\n", path[f][1]->chain[i++]);
	return (VALID);
}
