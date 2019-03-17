/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crossing_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 15:58:39 by nsondag           #+#    #+#             */
/*   Updated: 2019/03/16 02:57:07 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		*find_crossing(t_path **path, int p1, int p2)
{
	int *i;
	int found = 0;
	
	if (!(i = (int*)malloc(sizeof(int) * 2)))
		return (NULL);
	i[0] = path[p1]->len_path - 2;
	while (i[0])
	{
		i[1] = 1;
		while (path[p2]->chain[i[1]] != 1)
		{
			if (path[p1]->chain[i[0]] == path[p2]->chain[i[1]])
			{
				found = 1;
				break ;
			}
			i[1]++;
		}
		if (found)
			break;
		i[0]--;
	}
	return (i);
}

int		count_crossing_len(t_path **path, int *i, int p1, int p2)
{
	int count;
	int	i1;
	int i2;
	
	i1 = i[0];
	i2 = i[1];
	count = 0;
	while (path[p1]->chain[i1] == path[p2]->chain[i2])
	{
		i1--;
		i2++;
		count++;
	}
	return (count);
}

int		*copy_path1(t_path **path, int count, int *index, int g[2])
{
	int i;
	int j;
	int p1;
	int p2;
	int	*new_path;
	
	p1 = g[1];
	p2 = g[0];
	if (!(new_path = malloc(sizeof(int) * path[p1]->len_path)))
		return (NULL);
	i = -1;
	while (++i < index[0] - count + 2)
		new_path[i] = path[p1]->chain[i];
	j = 0;
	while (i < path[p1]->len_path)
		new_path[i++] = path[p2]->chain[index[1] + j++ + count];
	return (new_path);
}

int		*copy_path2(t_path **path, int *index, int p1, int p2)
{
	int i;
	int j;
	int	*new_path;
	
	if (!(new_path = malloc(sizeof(int) * path[p2]->len_path)))
		return (NULL);
	i = -1;
	while (++i < index[1])
		new_path[i] = path[p2]->chain[i];
	j = 0;
	while (i < path[p2]->len_path)
		new_path[i++] = path[p1]->chain[index[0] + j++];
	free(path[p1]->chain);
	free(path[p2]->chain);
	return (new_path);
}

/*
 ** g[0] = r;
 ** g[1] = k;
 ** g[2] = f;
 ** g[3] = i;
 ** g[4] = min;
 */

int		crossing_path(t_path ***path, int g[3])
{
	int *index;
	int count;
	int *path1;
	int *path2;
	int tmp;
	
	index = find_crossing(path[g[2]], g[1], g[0]);
	count = count_crossing_len(path[g[2]], index, g[1], g[0]);
	if (count > 1)
	{
		tmp = path[g[2]][g[1]]->len_path;
		path[g[2]][g[1]]->len_path = index[0] - index[1] +
		path[g[2]][g[0]]->len_path - (2 * count) + 2;
		path[g[2]][g[0]]->len_path = index[1] - index[0] + tmp;
		path1 = copy_path1(path[g[2]], count, index, g);
		path2 = copy_path2(path[g[2]], index, g[1], g[0]);
		if (!(path[g[2]][g[1]]->chain = malloc(sizeof(int) * path[g[2]][g[1]]->len_path)))
			return (MERROR);
		if (!(path[g[2]][g[0]]->chain = malloc(sizeof(int) * path[g[2]][g[0]]->len_path)))
			return (MERROR);
		ft_memcpy(path[g[2]][g[1]]->chain, path1, 4 * path[g[2]][g[1]]->len_path);
		ft_memcpy(path[g[2]][g[0]]->chain, path2, 4 * path[g[2]][g[0]]->len_path);
		free(path1);
		free(path2);
	}
	free(index);
	if (count > 1)
		return (crossing_path(path, g));
	return (count == 1 ? INVALID : VALID);
}
