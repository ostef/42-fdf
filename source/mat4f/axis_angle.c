/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   axis_angle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soumanso <soumanso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 01:14:50 by soumanso          #+#    #+#             */
/*   Updated: 2021/11/26 15:24:55 by soumanso         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_mat4f	mat4f_axis_angle(t_vec3f axis, t_f32 angle)
{
	t_mat4f	res;
	t_f32	s;
	t_f32	c;

	axis = vec3f_normalize (axis);
	s = sinf (angle);
	c = cosf (angle);
	res = mat4f_identity ();
	res.c0r0 = (axis.x * axis.x * (1 - c)) + c;
	res.c0r1 = (axis.x * axis.y * (1 - c)) + (axis.z * s);
	res.c0r2 = (axis.x * axis.z * (1 - c)) - (axis.y * s);
	res.c1r0 = (axis.y * axis.x * (1 - c)) - (axis.z * s);
	res.c1r1 = (axis.y * axis.y * (1 - c)) + c;
	res.c1r2 = (axis.y * axis.z * (1 - c)) + (axis.x * s);
	res.c2r0 = (axis.z * axis.x * (1 - c)) + (axis.y * s);
	res.c2r1 = (axis.z * axis.y * (1 - c)) - (axis.x * s);
	res.c2r2 = (axis.z * axis.z * (1 - c)) + c;
	return (res);
}

t_mat4f	mat4f_rotate_euler(t_vec3f euler)
{
	t_mat4f	x;
	t_mat4f	y;
	t_mat4f	z;
	t_mat4f	res;

	x = mat4f_axis_angle (vec3f (1, 0, 0), euler.x);
	y = mat4f_axis_angle (vec3f (0, 1, 0), euler.y);
	z = mat4f_axis_angle (vec3f (0, 0, 1), euler.z);
	res = mat4f_mul_mat4f (x, y);
	res = mat4f_mul_mat4f (res, z);
	return (res);
}
