/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_log.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 16:05:07 by fkhan             #+#    #+#             */
/*   Updated: 2022/07/26 21:03:25 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	debug_log(char *log)
{
	ft_printf("%s\n", log);
	exit(0);
}

void	print_help(void)
{
	ft_printf("Usage: ./fractol <name>\n");
	ft_printf("You can specify from 1 to 3 names of fractals\n");
	ft_printf("List of available fractals:\n");
	ft_printf("* Mandelbrot\n");
	ft_printf("* Julia set\n");
	ft_printf("* Julia set (with optional two float parameters)\n");
	ft_printf("* Burning ship\n");
}
