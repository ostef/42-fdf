/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soumanso <soumanso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 01:20:14 by soumanso          #+#    #+#             */
/*   Updated: 2021/11/18 01:37:07 by soumanso         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_f32	vec3f_len(t_vec3f v)
{
	return (sqrtf (v.x * v.x + v.y * v.y + v.z * v.z));
}

t_vec3f	vec3f_normalize(t_vec3f v)
{
	t_f32	len;

	len = vec3f_len (v);
	if (len == 0)
		return (vec3f_zero ());
	return (vec3f (v.x / len, v.y / len, v.z / len));
}
