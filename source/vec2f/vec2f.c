/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2f.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soumanso <soumanso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 01:21:44 by soumanso          #+#    #+#             */
/*   Updated: 2021/11/24 20:56:43 by soumanso         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_vec2f	vec2f(t_f32 x, t_f32 y)
{
	t_vec2f	res;

	res.x = x;
	res.y = y;
	return (res);
}

t_vec2f	vec2f_zero(void)
{
	return (vec2f (0, 0));
}

t_vec2f	vec2f_neg(t_vec2f v)
{
	t_vec2f	res;

	res.x = -v.x;
	res.y = -v.y;
	return (res);
}
