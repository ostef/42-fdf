/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3f.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soumanso <soumanso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 01:21:44 by soumanso          #+#    #+#             */
/*   Updated: 2021/11/18 02:52:08 by soumanso         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_vec3f	vec3f(t_f32 x, t_f32 y, t_f32 z)
{
	t_vec3f	res;

	res.x = x;
	res.y = y;
	res.z = z;
	return (res);
}

t_vec3f	vec3f_zero(void)
{
	return (vec3f (0, 0, 0));
}

t_vec3f	vec3f_neg(t_vec3f v)
{
	t_vec3f	res;

	res.x = -v.x;
	res.y = -v.y;
	res.z = -v.z;
	return (res);
}
