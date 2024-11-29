/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_d_i.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloiki <aloiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 18:06:16 by aloiki            #+#    #+#             */
/*   Updated: 2024/11/25 04:19:08 by aloiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_number_len(int num)
{
	int	i;

	i = 0;
	if (num == -2147483648)
		return (11);
	if (num < 0)
	{
		i++;
		num = -num;
	}
	while (num / 10 != 0)
	{
		i++;
		num = num / 10;
	}
	i++;
	return (i);
}

int	ft_printf_d_i(int c)
{
	int	nb;

	nb = c;
	if (nb == -2147483648)
		ft_putstr_fd("-2147483648", 1);
	else if (nb < 0)
	{
		nb = -nb;
		ft_putchar_fd('-', 1);
		ft_putnbr_fd(nb, 1);
	}
	else if (nb < 10 && nb >= 0)
	{
		ft_putchar_fd(nb + '0', 1);
	}
	else if (nb >= 10)
	{
		ft_putnbr_fd(nb / 10, 1);
		ft_putnbr_fd(nb % 10, 1);
	}
	return (ft_number_len(c));
}
