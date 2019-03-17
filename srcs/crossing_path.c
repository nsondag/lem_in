/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crossing_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 15:58:39 by nsondag           #+#    #+#             */
/*   Updated: 2019/03/17 16:43:49 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		*find_crossing(t_path **path, int p1, int p2)
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

int		*copy_path1(t_path **path, int count, int *index, int *p)
{
	int i;
	int j;
	int	*new_path;
	int	p1;
	int	p2;

	p1 = p[0];
	p2 = p[1];
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

int		crossing_path(t_path ***p, int *g)
{
	int *i;
	int c;
	int *path1;
	int *path2;
	int tmp;

	i = find_crossing(p[g[0]], g[1], g[0]);
	c = count_crossing_len(p[g[0]], i, g[1], g[0]);
	if (c > 1)
	{
		tmp = p[g[0]][g[1]]->len_path;
		p[g[2]][g[1]]->len_path = i[0] - i[1] +
			p[g[2]][g[0]]->len_path - (2 * c) + 2;
		p[g[2]][g[0]]->len_path = i[1] - i[0] + tmp;
		path1 = copy_path1(p[g[2]], c, i, g);
		path2 = copy_path2(p[g[2]], i, g[1], g[0]);
		if ((p[g[2]][g[1]]->chain =
					malloc(sizeof(int) * p[g[2]][g[1]]->len_path)))
			return (MERROR);
		if (!(p[g[2]][g[0]]->chain =
					malloc(sizeof(int) * p[g[2]][g[0]]->len_path)))
			return (MERROR);
		ft_memcpy(p[g[2]][g[1]]->chain, path1, 4 * p[g[2]][g[0]]->len_path);
		ft_memcpy(p[g[2]][g[0]]->chain, path2, 4 * p[g[2]][g[0]]->len_path);
		free(path1);
		free(path2);
	}
	free(i);
	if (c > 1)
		return (crossing_path(p, g));
	return (c == 1 ? INVALID : VALID);
}
