/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiply.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soumanso <soumanso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 00:54:18 by soumanso          #+#    #+#             */
/*   Updated: 2021/11/24 20:40:31 by soumanso         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_vec4f	mat4f_mul_vec4f(t_mat4f m, t_vec4f v)
{
	t_vec4f	res;
	t_f32	sum;
	t_s64	i;
	t_s64	j;

	j = 0;
	while (j < 4)
	{
		sum = 0;
		i = 0;
		while (i < 4)
		{
			sum += m.n[i][j] * v.n[i];
			i += 1;
		}
		res.n[j] = sum;
		j += 1;
	}
	return (res);
}

t_mat4f	mat4f_mul_mat4f(t_mat4f a, t_mat4f b)
{
	t_mat4f	res;

	res.c0 = mat4f_mul_vec4f (a, b.c0);
	res.c1 = mat4f_mul_vec4f (a, b.c1);
	res.c2 = mat4f_mul_vec4f (a, b.c2);
	res.c3 = mat4f_mul_vec4f (a, b.c3);
	return (res);
}
