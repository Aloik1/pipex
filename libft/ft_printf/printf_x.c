/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_x.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloiki <aloiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 18:03:44 by aloiki            #+#    #+#             */
/*   Updated: 2024/11/02 14:30:50 by aloiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_hex_num_len(unsigned int num)
{
	int	i;

	i = 0;
	while (num >= 16)
	{
		i++;
		num = num / 16;
	}
	i++;
	return (i);
}

static void	ft_put_nbr_hex_lower(unsigned int num)
{
	char	*hex;

	hex = "0123456789abcdef";
	if (num >= 16)
	{
		ft_put_nbr_hex_lower(num / 16);
		ft_put_nbr_hex_lower(num % 16);
	}
	else if (num < 16)
		ft_putchar_fd(hex[num], 1);
	return ;
}

int	ft_printf_x(unsigned int c)
{
	ft_put_nbr_hex_lower(c);
	return (ft_hex_num_len(c));
}
