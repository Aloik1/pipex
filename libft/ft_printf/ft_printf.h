/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloiki <aloiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 13:37:26 by aloiki            #+#    #+#             */
/*   Updated: 2024/11/02 15:31:55 by aloiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include "../libft.h"

int	ft_printf(const char *str, ...);
int	ft_printf_c(int c);
int	ft_printf_d_i(int c);
int	ft_printf_s(char *str);
int	ft_printf_u(unsigned int c);
int	ft_printf_x(unsigned int c);
int	ft_printf_x_big(unsigned int c);
int	ft_printf_p(void *str);

#endif