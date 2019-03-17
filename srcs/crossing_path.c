/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crossing_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 15:58:39 by nsondag           #+#    #+#             */
/*   Updated: 2019/03/17 20:25:54 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	*find_crossing(t_path **path, int p1, int p2)
{
	int *i;
	int found;

	found = 0;
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
			break ;
		i[0]--;
	}
	return (i);
}

static int	count_crossing_len(t_path **path, int *i, int p1, int p2)
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

static int	*copy_path1(t_path **path, int count, int *index, int g[2])
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

static int	*copy_path2(t_path **path, int *index, int p1, int p2)
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

int			crossing_path(t_path ***p, int g[3])
{
	int *index;
	int c[2];
	int *path1;
	int *path2;

	index = find_crossing(p[g[2]], g[1], g[0]);
	c[0] = count_crossing_len(p[g[2]], index, g[1], g[0]);
	if (c[0] > 1)
	{
		c[1] = p[g[2]][g[1]]->len_path;
		p[g[2]][g[1]]->len_path = index[0] - index[1] +
		p[g[2]][g[0]]->len_path - (2 * c[0]) + 2;
		p[g[2]][g[0]]->len_path = index[1] - index[0] + c[1];
		path1 = copy_path1(p[g[2]], c[0], index, g);
		path2 = copy_path2(p[g[2]], index, g[1], g[0]);
		if (!(p[g[2]][g[1]]->chain = malloc(4 * p[g[2]][g[1]]->len_path)) ||
				!(p[g[2]][g[0]]->chain = malloc(4 * p[g[2]][g[0]]->len_path)))
			return (MERROR);
		ft_memcpy(p[g[2]][g[1]]->chain, path1, 4 * p[g[2]][g[1]]->len_path);
		ft_memcpy(p[g[2]][g[0]]->chain, path2, 4 * p[g[2]][g[0]]->len_path);
		free(path1);
		free(path2);
	}
	free(index);
	return (c[0] > 1 ? crossing_path(p, g) : c[0]);
}
