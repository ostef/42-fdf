/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soumanso <soumanso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 01:33:10 by soumanso          #+#    #+#             */
/*   Updated: 2021/11/26 17:54:07 by soumanso         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"
#include <stdio.h>

t_vec4f	vec4f(t_f32 x, t_f32 y, t_f32 z, t_f32 w)
{
	t_vec4f	res;

	res.x = x;
	res.y = y;
	res.z = z;
	res.w = w;
	return (res);
}

t_vec4f	vec4f_zero(void)
{
	return (vec4f (0, 0, 0, 0));
}

static t_bool	frame_init(t_frame *f, t_fdf *fdf, t_s64 width, t_s64 height)
{
	f->img = mlx_new_image (fdf->mlx, width, height);
	if (!f->img)
		return (FALSE);
	f->pixel_data = (void *)mlx_get_data_addr (f->img, &f->bits_per_px,
		&f->line_length, &f->endianness);
	ft_assert (f->pixel_data != NULL, "Could not get image data ptr.");
	f->width = width;
	f->height = height;
	return (TRUE);
}

t_bool	fdf_init(t_fdf *fdf, t_s64 width, t_s64 height)
{
	fdf->mlx = mlx_init ();
	if (!fdf->mlx)
		return (FALSE);
	fdf->win = mlx_new_window (fdf->mlx, width, height, "FdF");
	if (!fdf->win)
		return (FALSE);
	if (!frame_init (&fdf->front, fdf, width, height))
		return (FALSE);
	if (!frame_init (&fdf->back, fdf, width, height))
		return (FALSE);
	fdf->width = width;
	fdf->height = height;
	return (TRUE);
}

/*
static void	print_mat4f(t_mat4f m)
{
	t_s64	i;
	t_s64	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			printf (" %3f ", m.n[j][i]);
			j += 1;
		}
		printf ("\n");
		i += 1;
	}
}
*/

void	fdf_calc_matrices(t_fdf *fdf)
{
	fdf->aspect_ratio = fdf->width / fdf->height;
	fdf->view = mat4f_mul_mat4f (
			mat4f_translate (vec3f_neg (fdf->camera_position)),
			mat4f_rotate_euler (vec3f_neg (fdf->camera_euler))
		);
	//fdf->projection = mat4f_ortho (fdf->width / fdf->scale, fdf->height / fdf->scale);
	fdf->projection = mat4f_perspective (60, fdf->aspect_ratio, 0.1, 1000);
	fdf->view_projection = mat4f_mul_mat4f (fdf->projection, fdf->view);
}

static void	swap_buffers(t_fdf *fdf)
{
	t_frame	tmp;

	tmp = fdf->front;
	fdf->front = fdf->back;
	fdf->back = tmp;
	mlx_put_image_to_window (fdf->mlx, fdf->win, fdf->back.img, 0, 0);
	mlx_do_sync (fdf->mlx);
}

static t_vec2f	cam_to_screen(t_fdf *fdf, t_vec3f p)
{
	return (vec2f (
		ft_minf (fdf->width - 1, (p.x + 1) * 0.5 * fdf->width),
		ft_minf (fdf->height - 1, (p.y + 1) * 0.5 * fdf->height)));
}

static t_vec3f	project(t_mat4f m, t_vec3f p)
{
	t_vec4f	p4;

	p4 = vec4f (p.x, p.y, p.z, 1);
	p4 = mat4f_mul_vec4f (m, p4);
	return (vec3f (p4.x / p4.w, p4.y / p4.w, p4.z / p4.w));
}

static void	draw_line3d(t_fdf *fdf, t_vec3f p0, t_vec3f p1, t_rgba color)
{
	t_vec3f	proj0;
	t_vec3f	proj1;

	proj0 = project (fdf->view_projection, p0);
	proj1 = project (fdf->view_projection, p1);
	draw_line (&fdf->back, cam_to_screen (fdf, proj0), cam_to_screen (fdf, proj1), color);
}

static void	draw_axes(t_fdf *fdf)
{
	draw_line3d (fdf, vec3f (0, 0, 0), vec3f (1, 0, 0), rgb (255, 0, 0));
	draw_line3d (fdf, vec3f (0, 0, 0), vec3f (0, 1, 0), rgb (0, 255, 0));
	draw_line3d (fdf, vec3f (0, 0, 0), vec3f (0, 0, 1), rgb (0, 0, 255));
}

static int	render_loop(t_fdf *fdf)
{
	t_s64	start_time;
	t_s64	end_time;
	t_s64	x;
	t_s64	y;

	start_time = get_time ();
	ft_reset_temp_storage ();
	clear_frame (&fdf->back, rgb (0, 0, 0));
	fdf_calc_matrices (fdf);
	draw_axes (fdf);
	//printf ("%f\n", fdf->scale);
	x = 0;
	while (x < fdf->map_width)
	{
		y = 0;
		while (y < fdf->map_height)
		{
			t_vec3f	p0 = fdf->points[y * fdf->map_width + x];
			if (x != fdf->map_width - 1)
			{
				t_vec3f	p1 = fdf->points[y * fdf->map_width + (x + 1)];
				draw_line3d (fdf, p0, p1, rgb (255, 0, 0));
			}
			if (y != fdf->map_height - 1)
			{
				t_vec3f	p1 = fdf->points[(y + 1) * fdf->map_width + x];
				draw_line3d (fdf, p0, p1, rgb (255, 0, 0));
			}
			y += 1;
		}
		x += 1;
	}
	swap_buffers (fdf);
	end_time = get_time ();
	//ft_println ("Frame took %d ms.", end_time - start_time);
	return (0);
}

#define KC_Q 12
#define KC_W 13
#define KC_E 14
#define KC_A 0
#define KC_S 1
#define KC_D 2
#define KC_SPACE 49
#define KC_CTRL 256
#define KC_UP 126
#define KC_DOWN 125
#define KC_LEFT 123
#define KC_RIGHT 124
#define CAM_SPEED 0.5
#define CAM_ROT_SPEED 0.01

static int	key_hook(int key_code, t_fdf *fdf)
{
	(void)fdf;
	if (key_code == KC_W)
		fdf->camera_position.z += CAM_SPEED;
	else if (key_code == KC_S)
		fdf->camera_position.z -= CAM_SPEED;
	else if (key_code == KC_D)
		fdf->camera_position.x += CAM_SPEED;
	else if (key_code == KC_A)
		fdf->camera_position.x -= CAM_SPEED;
	else if (key_code == KC_E)
		fdf->camera_position.y += CAM_SPEED;
	else if (key_code == KC_Q)
		fdf->camera_position.y -= CAM_SPEED;
	else if (key_code == KC_UP)
		fdf->camera_euler.x += PI * CAM_ROT_SPEED;
	else if (key_code == KC_DOWN)
		fdf->camera_euler.x -= PI * CAM_ROT_SPEED;
	else if (key_code == KC_LEFT)
		fdf->camera_euler.y += PI * CAM_ROT_SPEED;
	else if (key_code == KC_RIGHT)
		fdf->camera_euler.y -= PI * CAM_ROT_SPEED;
	else if (key_code == KC_SPACE)
		fdf->scale = ft_maxf (fdf->scale * 2, 1);
	else if (key_code == KC_CTRL)
		fdf->scale = ft_maxf (fdf->scale / 2, 1);
	ft_println ("key_code is %i.", key_code);
	return (0);
}

int	main(int argc, char **args)
{
	t_fdf	fdf;

	if (argc < 2)
	{
		ft_println ("Error: Not enough arguments.");
		return (1);
	}
	ft_memset (&fdf, 0, sizeof (t_fdf));
	fdf.scale = 8000;
	//fdf.camera_position.x = -10;
	//fdf.camera_position.y = -10;
	fdf.camera_position.z = -10;
	//fdf.camera_euler.x = PI * 0.1;
	//fdf.camera_euler.y = PI * 0.3;
	if (!fdf_init (&fdf, 640, 480))
	{
		ft_println ("Error: Could not initialize mlx.");
		return (1);
	}
	parse_map (&fdf, args[1]);
	mlx_hook(fdf.win, 2, 1L<<0, key_hook, &fdf);
	mlx_loop_hook (fdf.mlx, render_loop, &fdf);
	mlx_loop (fdf.mlx);
	return (0);
}
