/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soumanso <soumanso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 02:57:43 by soumanso          #+#    #+#             */
/*   Updated: 2021/12/08 17:32:57 by soumanso         ###   ########lyon.fr   */
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

static t_u8	compute_out_code(t_frame *f, t_vec2f p)
{
	t_u8	code;

	code = 0;
	if (p.x < 0)
		code |= 1;
	else if (p.x > f->width)
		code |= 2;
	if (p.y < 0)
		code |= 4;
	else if (p.y > f->height)
		code |= 8;
	return (code);
}

static t_bool	clip_line(t_frame *f, t_vec2f *p1, t_vec2f *p2)
{
	t_u8	c1;
	t_u8	c2;
	t_u8	c;
	t_vec2f	p;

	c1 = compute_out_code (f, *p1);
	c2 = compute_out_code (f, *p2);
	while (TRUE)
	{
		//ft_println ("ca boucle ma gueule.");
		if (!(c1 | c2))
		{
			//ft_println ("ca return true ma gueule.");
			return (TRUE);
		}
		else if (c1 & c2)
		{
			//ft_println ("ca return false ma gueule.");
			return (FALSE);
		}
		else
		{
			c = (t_u8)ft_max (c1, c2);
			if (c & 8)
			{
				p.x = p1->x + (p2->x - p1->x) * (f->height - p1->y) / (p2->y - p1->y);
				p.y = f->height;
			}
			else if (c & 4)
			{
				p.x = p1->x + (p2->x - p1->x) * (-p1->y) / (p2->y - p1->y);
				p.y = 0;
			}
			else if (c & 2)
			{
				p.y = p1->y + (p2->y - p1->y) * (f->width - p1->x) / (p2->x - p1->x);
				p.x = f->width;
			}
			else if (c & 1)
			{
				p.y = p1->y + (p2->y - p1->y) * (-p1->x) / (p2->x - p1->x);
				p.x = 0;
			}
			if (c == c1)
			{
				p1->x = p.x;
				p1->y = p.y;
				c1 = compute_out_code (f, *p1);
			}
			else
			{
				p2->x = p.x;
				p2->y = p.y;
				c2 = compute_out_code (f, *p2);
			}
		}
	}
	return (FALSE);
}

void	draw_line(t_frame *f, t_vec2f p1, t_vec2f p2, t_rgba color)
{
	//t_s64 start_time = get_time ();
	if (!clip_line (f, &p1, &p2))
		return ;
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
	//t_s64 end_time = get_time ();
	//ft_println ("draw_line: %i ms", (t_int)(end_time - start_time));
}
