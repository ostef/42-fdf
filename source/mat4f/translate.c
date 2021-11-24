/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soumanso <soumanso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 01:27:58 by soumanso          #+#    #+#             */
/*   Updated: 2021/11/18 01:29:30 by soumanso         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_mat4f	mat4f_translate(t_vec3f t)
{
	t_mat4f	res;

	res = mat4f_identity ();
	res.c3r0 = t.x;
	res.c3r1 = t.y;
	res.c3r2 = t.z;
	return (res);
}
