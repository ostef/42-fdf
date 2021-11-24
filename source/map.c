/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soumanso <soumanso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 18:09:50 by soumanso          #+#    #+#             */
/*   Updated: 2021/11/24 19:52:10 by soumanso         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_s64	count_points(t_str str)
{
	t_s64	i;
	t_s64	start;
	t_s64	end;

	i = 0;
	end = 0;
	start = 0;
	while (str[end])
	{
		if (ft_is_space (str[end]))
		{
			if (end > start)
				i += 1;
			start = end + 1;
		}
		end += 1;
	}
	return (i);
}

static t_s64	read_line(t_fdf *fdf, t_cstr str, t_int y)
{
	t_s64	i;
	t_int	x;
	t_int	z;
	
	i = 0;
	x = 0;
	while (str[i])
	{
		while (str[i] == ' ')
			i += 1;
		if (str[i] == '\n')
		{
			fdf->map_width = x;
			return (i + 1);
		}
		if (!str[i])
			return (i);
		i += ft_str_to_int (str + i, &z);
		fdf->points[y * fdf->map_width + x] = vec3f (x, y, z);
		x += 1;
	}
	return (i);
}

t_bool	parse_map(t_fdf *fdf, t_cstr filename)
{
	t_str	str;
	t_s64	i;
	t_s64	count;

	str = ft_read_entire_file (filename, ALLOC_TEMP);
	count = count_points (str);
	fdf->points = (t_vec3f *)ft_alloc (sizeof (t_vec3f) * count, ALLOC_HEAP);
	i = 0;
	fdf->map_width = 0;
	fdf->map_height = 0;
	while (str[i])
	{
		i += read_line(fdf, str + i, fdf->map_height);
		fdf->map_height += 1;
	}
	return (TRUE);
}
