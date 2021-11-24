/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_sub_mul.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soumanso <soumanso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 01:17:50 by soumanso          #+#    #+#             */
/*   Updated: 2021/11/18 01:19:49 by soumanso         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_vec3f	vec3f_add_vec3f(t_vec3f a, t_vec3f b)
{
	return (vec3f (a.x + b.x, a.y + b.y, a.z + b.z));
}

t_vec3f	vec3f_sub_vec3f(t_vec3f a, t_vec3f b)
{
	return (vec3f (a.x - b.x, a.y - b.y, a.z - b.z));
}

t_vec3f	vec3f_mul_f32(t_vec3f a, t_f32 b)
{
	return (vec3f (a.x * b, a.y * b, a.z * b));
}
