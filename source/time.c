/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soumanso <soumanso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 16:45:46 by soumanso          #+#    #+#             */
/*   Updated: 2021/11/24 18:07:54 by soumanso         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <sys/time.h>

t_s64	get_time(void)
{
	struct timeval	time;

	gettimeofday (&time, NULL);
	return ((t_s64)time.tv_sec * 1000 + (t_s64)time.tv_usec / 1000);
}
