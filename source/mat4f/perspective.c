/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perspective.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soumanso <soumanso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 16:09:20 by soumanso          #+#    #+#             */
/*   Updated: 2021/11/26 17:34:37 by soumanso         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_mat4f	mat4f_perspective(t_f32 fov, t_f32 aspect, t_f32 znear, t_f32 zfar)
{
	t_mat4f	res;
	t_f32	t;
	t_f32	b;
	t_f32	r;
	t_f32	l;

	t = tanf ((fov * (PI / 180)) * 0.5f) * znear;
	b = -t;
	r = aspect * t;
	l = -r;
	res = mat4f_identity ();
	res.r0c0 = 2 * znear / (r - l);
	res.r1c1 = 2 * znear / (t - b);
	res.c2 = vec4f ((r + l) / (r - l), (t + b) / (t - b), -(zfar + znear) / (zfar - znear), -1);
	res.r3c2 = -2 * zfar * znear / (zfar - znear);
	res.r3c3 = 0;
	return (res);
}
