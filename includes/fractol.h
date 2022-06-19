/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 14:59:12 by fkhan             #+#    #+#             */
/*   Updated: 2022/06/19 16:46:21 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "libft.h"
# include "ft_printf.h"
# include <mlx.h>
# include "debug_log.h"

# define WIDTH		700
# define HEIGHT		500

typedef struct s_imageinfo
{
	void			*image;
	char			*data_addr;
	int				bits_per_pixel;
	int				size_line;
	int				endian;
}	t_imageinfo;

typedef struct s_fractolinfo
{
	char			*name;
	t_imageinfo		*imageinfo;
}	t_fractolinfo;

typedef struct s_appinfo
{
	void	*mlx;
	void	*window;
}	t_appinfo;

#endif