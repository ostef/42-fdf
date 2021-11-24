/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_sub_mul.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soumanso <soumanso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 20:54:15 by soumanso          #+#    #+#             */
/*   Updated: 2021/11/24 20:54:51 by soumanso         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_vec2f	vec2f_add_vec2f(t_vec2f a, t_vec2f b)
{
	return (vec2f (a.x + b.x, a.y + b.y));
}

t_vec2f	vec2f_sub_vec2f(t_vec2f a, t_vec2f b)
{
	return (vec2f (a.x - b.x, a.y - b.y));
}

t_vec2f	vec2f_mul_f32(t_vec2f a, t_f32 b)
{
	return (vec2f (a.x * b, a.y * b));
}
