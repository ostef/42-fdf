/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soumanso <soumanso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 00:52:38 by soumanso          #+#    #+#             */
/*   Updated: 2021/11/24 20:40:22 by soumanso         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_mat4f	mat4f_identity(void)
{
	t_mat4f	mat;

	ft_memset (&mat, 0, sizeof (t_mat4f));
	mat.c0r0 = 1;
	mat.c1r1 = 1;
	mat.c2r2 = 1;
	mat.c3r3 = 1;
	return (mat);
}
