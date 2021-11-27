/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soumanso <soumanso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 02:57:43 by soumanso          #+#    #+#             */
/*   Updated: 2021/11/26 17:58:53 by soumanso         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"

t_rgba	rgba(t_u8 r, t_u8 g, t_u8 b, t_u8 a)
{
	t_rgba	res;

	res.r = r;
	res.g = g;
	res.b = b;
	res.a = a;
	return (res);
}

t_rgba	rgb(t_u8 r, t_u8 g, t_u8 b)
{
	return (rgba (r, g, b, 255));
}

t_u32	rgba_to_trgb(t_rgba rgba)
{
	return ((255 - rgba.a) << 24 | rgba.r << 16 | rgba.g << 8 | rgba.b);
}

void	clear_frame(t_frame *f, t_rgba color)
{
	t_s64	x;
	t_s64	y;

	x = 0;
	while (x < f->width)
	{
		y = 0;
		while (y < f->height)
		{
			draw_pt (f, vec2f (x, y), color);
			y += 1;
		}
		x += 1;
	}
}

void	draw_pt(t_frame *f, t_vec2f pt, t_rgba color)
{
	t_s64	off;

	if (ft_is_nan (pt.x) || ft_is_nan (pt.y))
		return ;
	if (pt.x < 0 || pt.x >= f->width || pt.y < 0 || pt.y >= f->height)
		return ;
	off = ((t_s64)pt.y * f->line_length + (t_s64)pt.x * (f->bits_per_px / 8));
	*(t_u32 *)(f->pixel_data + off) = rgba_to_trgb (color);
}

void	draw_circle(t_frame *f, t_vec2f pt, t_f32 radius, t_rgba color)
{
	t_s64	i;
	t_s64	j;

	i = (t_s64)(pt.x - radius);
	while (i < (t_s64)(pt.x + radius))
	{
		j = (t_s64)(pt.y - radius);
		while (j < (t_s64)(pt.y + radius))
		{
			if (vec2f_len (vec2f_sub_vec2f (vec2f (i, j), pt)) <= radius)
				draw_pt (f, vec2f (i, j), color);
			j += 1;
		}
		i += 1;
	}
}

static void	draw_line_low(t_frame *f, t_vec2f p1, t_vec2f p2, t_rgba color)
{
	t_f32	dx;
	t_f32	dy;
	t_f32	d;
	t_s64	x;
	t_s64	y;

	dx = p2.x - p1.x;
	dy = p2.y - p1.y;
	d = 2 * ft_absf (dy) - dx;
	x = (t_s64)p1.x;
	y = (t_s64)p1.y;
	while (x < (t_s64)p2.x)
	{
		draw_pt (f, vec2f (x, y), color);
		if (d > 0)
		{
			y += (t_s64)ft_signf (dy);
			d += 2 * (ft_absf (dy) - dx);
		}
		else
			d += 2 * ft_absf (dy);
		x += (t_s64)ft_signf (dx);
	}
}

static void	draw_line_high(t_frame *f, t_vec2f p1, t_vec2f p2, t_rgba color)
{
	t_f32	dx;
	t_f32	dy;
	t_f32	d;
	t_s64	x;
	t_s64	y;

	dx = p2.x - p1.x;
	dy = p2.y - p1.y;
	d = 2 * ft_absf (dx) - dy;
	x = (t_s64)p1.x;
	y = (t_s64)p1.y;
	while (y != (t_s64)p2.y)
	{
		draw_pt (f, vec2f (x, y), color);
		if (d > 0)
		{
			x += ft_signf (dx);
			d += 2 * (ft_absf (dx) - dy);
		}
		else
			d += 2 * ft_absf (dx);
		y += (t_s64)ft_signf (dy);
	}
}

void	draw_line(t_frame *f, t_vec2f p1, t_vec2f p2, t_rgba color)
{
	if (ft_absf (p2.y - p1.y) < ft_absf (p2.x - p1.x))
	{
		if (p1.x > p2.x)
			draw_line_low (f, p2, p1, color);
		else
			draw_line_low (f, p1, p2, color);
	}
	else
	{
		if (p1.y > p2.y)
			draw_line_high (f, p2, p1, color);
		else
			draw_line_high (f, p1, p2, color);
	}
}
