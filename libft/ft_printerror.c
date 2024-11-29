/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printerror.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloiki <aloiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 14:41:11 by aloiki            #+#    #+#             */
/*   Updated: 2024/11/04 19:49:49 by aloiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_printerror(char *error_msg)
{
	ft_putstr_fd("\033[31mError: ", 2);
	ft_putendl_fd(error_msg, 2);
	ft_putstr_fd("\033[0m", 2);
	exit(EXIT_FAILURE);
}
