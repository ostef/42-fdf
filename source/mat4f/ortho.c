/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ortho.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soumanso <soumanso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 01:10:30 by soumanso          #+#    #+#             */
/*   Updated: 2021/11/18 01:14:18 by soumanso         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_mat4f	mat4f_ortho(t_f32 width, t_f32 height)
{
	t_mat4f	res;

	res = mat4f_identity ();
	res.c0r0 = 2 / width;
	res.c1r1 = 2 / height;
	res.c2r2 = -2;
	res.c3r0 = -1;
	res.c3r1 = -1;
	res.c3r2 = -1;
	return (res);
}
