/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soumanso <soumanso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 01:33:10 by soumanso          #+#    #+#             */
/*   Updated: 2021/11/24 21:12:59 by soumanso         ###   ########lyon.fr   */
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
	fdf->view = mat4f_translate (vec3f_neg (fdf->camera_position));
	fdf->projection = mat4f_ortho ((t_f32)fdf->width, (t_f32)fdf->height);
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
	x = 0;
	while (x < fdf->map_width)
	{
		y = 0;
		while (y < fdf->map_height)
		{
			t_vec3f	p0 = fdf->points[y * fdf->map_width + x];
			t_vec4f	p1 = mat4f_mul_vec4f (fdf->view_projection, vec4f (p0.x, p0.y, p0.z, 1));
			printf ("p0: %.2f %.2f %.2f\n", p0.x, p0.y, p0.z);
			printf ("p1: %.2f %.2f %.2f %.2f\n", p1.x, p1.y, p1.z, p1.w);
			//draw_line (&fdf->back, vec2f (10, 10), vec2f (100, 100), rgb (255, 255, 255));
			draw_circle (&fdf->back, vec2f (p1.x * 100, p1.z * 100), 10, rgb (255, 255, 255));
			y += 1;
		}
		x += 1;
	}
	swap_buffers (fdf);
	end_time = get_time ();
	//ft_println ("Frame took %d ms.", end_time - start_time);
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
	if (!fdf_init (&fdf, 1920, 1080))
	{
		ft_println ("Error: Could not initialize mlx.");
		return (1);
	}
	parse_map (&fdf, args[1]);
	mlx_loop_hook (fdf.mlx, render_loop, &fdf);
	mlx_loop (fdf.mlx);
	return (0);
}
