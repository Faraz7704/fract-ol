/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 14:59:12 by fkhan             #+#    #+#             */
/*   Updated: 2022/06/19 14:40:44 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	start(void)
{
	void	*mlx;

	mlx = mlx_init();
	mlx_loop(mlx);
}

int	main(int ac, char **av)
{
	ft_printf("ac: %d av: %s\n", ac, av[0]);
	start();
	return (0);
}
