/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crossing_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 15:58:39 by nsondag           #+#    #+#             */
/*   Updated: 2019/03/11 17:12:22 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		*find_crossing(t_path **path, int p1, int p2)
{
	int *i;

	if (!(i = (int*)malloc(sizeof(int) * 2)))
		return (NULL);
	i[0] = 1;
	while (path[p1]->chain[i[0]] != 1)
	{
		i[1] = path[p2]->len_path - 2;
		while (i[1])
		{
			if (path[p1]->chain[i[0]] == path[p2]->chain[i[1]])
				break ;
			i[1]--;
		}
		i[0]++;
	}
	i[0]--;
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

int		*copy_path1(t_path **path, int count, int *index, int p1, int p2)
{
	int i;
	int j;
	int	*new_path;

	if (!(new_path = malloc(sizeof(int) * path[p1]->len_path)))
		return (NULL);
	i = -1;
	while (++i < index[0] - count + 2)
		new_path[i] = path[p1]->chain[i];
	j = 0;
	while (i < path[0]->len_path)
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

int		crossing_path(t_path ***path, int p2, int p1)
{
	int *index;
	int count;
	int *path1;
	int *path2;
	int tmp;

	index = find_crossing(path[p2], p1, p2);
	count = count_crossing_len(path[p2], index, p1, p2);
	if (count > 1)
	{
		tmp = path[p2][p1]->len_path;
		path[p2][p1]->len_path = index[0] - index[1] +
			path[p2][p2]->len_path - (2 * count) + 2;
		path[p2][p2]->len_path = index[1] - index[0] + tmp;
		path1 = copy_path1(path[p2], count, index, p1, p2);
		path2 = copy_path2(path[p2], index, p1, p2);
		if (!(path[p2][p1]->chain = malloc(sizeof(int) * path[p2][p1]->len_path)))
			return (MERROR);
		if (!(path[p2][p2]->chain = malloc(sizeof(int) * path[p2][p2]->len_path)))
			return (MERROR);
		ft_memcpy(path[p2][p1]->chain, path1, 4 * path[p2][p1]->len_path);
		ft_memcpy(path[p2][p2]->chain, path2, 4 * path[p2][p2]->len_path);
	}
	if (count > 1)
		return (crossing_path(path, p2, p1));
	return (count == 1 ? INVALID : VALID);
}
