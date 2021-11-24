/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soumanso <soumanso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 01:20:14 by soumanso          #+#    #+#             */
/*   Updated: 2021/11/24 20:56:22 by soumanso         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_f32	vec2f_len(t_vec2f v)
{
	return (sqrtf (v.x * v.x + v.y * v.y));
}

t_vec2f	vec2f_normalize(t_vec2f v)
{
	t_f32	len;

	len = vec2f_len (v);
	if (len == 0)
		return (vec2f_zero ());
	return (vec2f (v.x / len, v.y / len));
}
