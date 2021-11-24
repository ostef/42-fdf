/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transpose.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soumanso <soumanso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 01:07:44 by soumanso          #+#    #+#             */
/*   Updated: 2021/11/18 01:08:54 by soumanso         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_mat4f	mat4f_transpose(t_mat4f	m)
{
	t_mat4f	res;
	t_s64	i;
	t_s64	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			res.n[i][j] = m.n[j][i];
			j += 1;
		}
		i += 1;
	}
	return (res);
}
