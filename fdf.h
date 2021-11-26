/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soumanso <soumanso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 00:41:04 by soumanso          #+#    #+#             */
/*   Updated: 2021/11/26 17:13:13 by soumanso         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft/libft.h"
# include <math.h>

t_s64	get_time(void);

/* Math */

typedef union u_vec2f
{
	t_f32		n[2];
	struct
	{
		t_f32	x;
		t_f32	y;
	};
}	t_vec2f;

t_vec2f	vec2f(t_f32 x, t_f32 y);
t_vec2f	vec2f_zero(void);
t_vec2f	vec2f_add_vec2f(t_vec2f a, t_vec2f b);
t_vec2f	vec2f_sub_vec2f(t_vec2f a, t_vec2f b);
t_vec2f	vec2f_mul_f32(t_vec2f a, t_f32 b);
t_vec2f	vec2f_neg(t_vec2f v);
t_f32	vec2f_len(t_vec2f v);
t_vec2f	vec2f_normalize(t_vec2f v);

typedef union u_vec3f
{
	t_f32		n[3];
	struct
	{
		t_f32	x;
		t_f32	y;
		t_f32	z;
	};
}	t_vec3f;

t_vec3f	vec3f(t_f32 x, t_f32 y, t_f32 z);
t_vec3f	vec3f_zero(void);
t_vec3f	vec3f_add_vec3f(t_vec3f a, t_vec3f b);
t_vec3f	vec3f_sub_vec3f(t_vec3f a, t_vec3f b);
t_vec3f	vec3f_mul_f32(t_vec3f a, t_f32 b);
t_vec3f	vec3f_neg(t_vec3f v);
t_f32	vec3f_len(t_vec3f v);
t_vec3f	vec3f_normalize(t_vec3f v);

typedef union u_vec4f
{
	t_f32		n[4];
	struct
	{
		t_f32	x;
		t_f32	y;
		t_f32	z;
		t_f32	w;
	};
}	t_vec4f;

t_vec4f	vec4f(t_f32 x, t_f32 y, t_f32 z, t_f32 w);
t_vec4f	vec4f_zero(void);

/* Matrices are column-major in memory! */

typedef union u_mat4f
{
	t_f32		n[4][4];
	struct
	{
		t_f32	c0r0;
		t_f32	c0r1;
		t_f32	c0r2;
		t_f32	c0r3;
		t_f32	c1r0;
		t_f32	c1r1;
		t_f32	c1r2;
		t_f32	c1r3;
		t_f32	c2r0;
		t_f32	c2r1;
		t_f32	c2r2;
		t_f32	c2r3;
		t_f32	c3r0;
		t_f32	c3r1;
		t_f32	c3r2;
		t_f32	c3r3;
	};
	struct
	{
		t_f32	r0c0;
		t_f32	r1c0;
		t_f32	r2c0;
		t_f32	r3c0;
		t_f32	r0c1;
		t_f32	r1c1;
		t_f32	r2c1;
		t_f32	r3c1;
		t_f32	r0c2;
		t_f32	r1c2;
		t_f32	r2c2;
		t_f32	r3c2;
		t_f32	r0c3;
		t_f32	r1c3;
		t_f32	r2c3;
		t_f32	r3c3;
	};
	struct
	{
		t_vec4f	c0;
		t_vec4f	c1;
		t_vec4f	c2;
		t_vec4f	c3;
	};
}	t_mat4f;

t_mat4f	mat4f_identity(void);
t_vec4f	mat4f_mul_vec4f(t_mat4f m, t_vec4f v);
t_mat4f	mat4f_mul_mat4f(t_mat4f a, t_mat4f b);
t_mat4f	mat4f_transpose(t_mat4f m);
/* t_mat4f mat4f_inverse(t_mat4f m); */
t_mat4f	mat4f_ortho(t_f32 width, t_f32 height);
t_mat4f	mat4f_perspective(t_f32 fov, t_f32 aspect, t_f32 znear, t_f32 zfar);
t_mat4f	mat4f_axis_angle(t_vec3f axis, t_f32 angle);
t_mat4f	mat4f_rotate_euler(t_vec3f euler);
t_mat4f	mat4f_translate(t_vec3f t);

/* Graphics */

typedef union u_rgba
{
	t_u32	value;
	struct
	{
		t_u8	r;
		t_u8	g;
		t_u8	b;
		t_u8	a;
	};
}	t_rgba;

t_rgba	rgba(t_u8 r, t_u8 g, t_u8 b, t_u8 a);
t_rgba	rgb(t_u8 r, t_u8 g, t_u8 b);
t_u32	rgba_to_trgb(t_rgba rgba);

typedef struct s_frame
{
	void	*img;
	void	*pixel_data;
	t_s64	width;
	t_s64	height;
	t_int	bits_per_px;
	t_int	line_length;
	t_int	endianness;
}	t_frame;

void	clear_frame(t_frame *f, t_rgba color);
void	draw_pt(t_frame *f, t_vec2f pt, t_rgba color);
void	draw_circle(t_frame *f, t_vec2f pt, t_f32 radius, t_rgba color);
void	draw_line(t_frame *f, t_vec2f p1, t_vec2f p2, t_rgba color);

/* FDF */

typedef struct s_fdf
{
	void	*mlx;
	void	*win;
	t_s64	width;
	t_s64	height;
	t_f32	aspect_ratio;
	t_f32	scale;
	t_frame	front;
	t_frame	back;
	t_vec3f	camera_position;
	t_vec3f	camera_euler;
	t_mat4f	view;
	t_mat4f	projection;
	t_mat4f	view_projection;
	t_vec3f *points;
	t_s64	map_width;
	t_s64	map_height;
}	t_fdf;

t_bool	fdf_init(t_fdf *fdf, t_s64 width, t_s64 height);
void	fdf_calc_matrices(t_fdf *fdf);
t_bool	parse_map(t_fdf *fdf, t_cstr filename);

#endif
