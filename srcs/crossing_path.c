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

int		*find_crossing(t_path **path)
{	
		int *i;

		if (!(i = (int*)malloc(sizeof(int) * 2)))
				return(NULL);
		i[0] = 1;
		while (path[0]->chain[i[0]] != 1)
		{
				i[1] = path[1]->len_path - 2;
				while (i[1])
				{
						if (path[0]->chain[i[0]] == path[1]->chain[i[1]])
								break ;	
						i[1]--;
				}
				i[0]++;
		}
		i[0]--;
		return (i);
}

int count_crossing_len(t_path **path, int i1, int i2)
{
		int count;

		count = 0;
		while (path[0]->chain[i1] == path[1]->chain[i2])
		{
				i1--;
				i2++;
				count++;
		}
		return (count);
}

int *copy_path1(t_path **path, int count, int *index)
{
		int i;
		int j;
		int	*new_path;

		if (!(new_path = malloc(sizeof(int) * path[0]->len_path)))
				return (NULL);
		i = -1;
		while (++i < index[0] - count + 2)
				new_path[i] = path[0]->chain[i];
		j = 0;
		while (i < path[0]->len_path)
				new_path[i++] = path[1]->chain[index[1] + j++ + count];
		free(path[0]->chain);
		return (new_path);
}

int *copy_path2(t_path **path, int *index)
{
		int i;
		int j;
		int	*new_path;

		if (!(new_path = malloc(sizeof(int) * path[1]->len_path)))
				return (NULL);
		i = -1;
		while (++i < index[1])
				new_path[i] = path[1]->chain[i];
		j = 0;
		while (i < path[1]->len_path)
				new_path[i++] = path[0]->chain[index[0] + j++];
		free(path[1]->chain);
		return (new_path);
}

int crossing_path(t_path ***path, int f)
{
		int *index;
		int count;
		int *path1;
		int *path2;
		int tmp;

		index = find_crossing(path[f]);
		count = count_crossing_len(path[f], index[0], index[1]);
		if (count > 1)
		{
			tmp = path[f][0]->len_path;
			path[f][0]->len_path = index[0] - index[1] +
				path[f][1]->len_path - (2 * count) + 2;
			path[f][1]->len_path = index[1] - index[0] + tmp;
		path1 = copy_path1(path[f], count, index);
		path2 = copy_path2(path[f], index);
		if (!(path[f][0]->chain = malloc(sizeof(int) * path[f][0]->len_path)))
				return (MERROR);
		if (!(path[f][1]->chain = malloc(sizeof(int) * path[f][1]->len_path)))
				return (MERROR);
		ft_memcpy(path[f][0]->chain, path1, 4 * path[f][0]->len_path);	
		ft_memcpy(path[f][1]->chain, path2, 4 * path[f][1]->len_path);	
		}
		return (count == 1 ? INVALID : VALID);
}
