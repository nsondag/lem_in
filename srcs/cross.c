/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cross.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 16:35:19 by hvromman          #+#    #+#             */
/*   Updated: 2019/03/16 02:05:18 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		delete(t_path *path1, int i, t_path *path2, int j)
{
	int		offset;
	int		*tmp1;
	int		*tmp2;
	int		len1;
	int		len2;

	offset = 0;
	while (path1->chain[i + offset + 1] == path2->chain[j - offset + 1])
		offset++;
	if (offset == 0) // a supprimer
		return (INVALID);
	len1 = path1->len_path;
	len2 = path2->len_path;
	tmp1 = malloc(sizeof(int) * (i + len2 - j));
	tmp2 = malloc(sizeof(int) * (j + len1 - i - 2 * offset));
	memcpy(tmp1, path1->chain, sizeof(int) * i);
	memcpy(&tmp1[i], &path2->chain[j], sizeof(int) * (len2 - j));
	memcpy(tmp2, path2->chain, sizeof(int) * (j - offset));
	memcpy(&tmp2[j - offset], &path1->chain[i + offset],
			sizeof(int) * (len1 - i - offset));
	path1->len_path = i + len2 - j;
	path2->len_path = j + len1 - i - 2 * offset;
	free(path1->chain);
	free(path2->chain);
	path1->chain = tmp1;
	path2->chain = tmp2;
	return (cross(path1, path2));
}

int		cross(t_path *path1, t_path *path2)
{
	int		i;
	int		j;

	i = 0;
	while (++i < path1->len_path - 1)
	{
		j = path2->len_path - 1;
		while (--j > 0)
		{
			if (path1->chain[i] == path2->chain[j])
				return (delete(path1, i, path2, j));
		}
	}
	return (0);
}
