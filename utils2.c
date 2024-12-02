/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloiki <aloiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 14:15:11 by aloiki            #+#    #+#             */
/*   Updated: 2024/12/02 19:25:03 by aloiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*free_and_null(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i++])
		free(matrix[i]);
	free(matrix);
	return (NULL);
}

void	check_valid_args(int argc, char **argv)
{
	int	i;

	i = 0;
	if (argc != 5)
		ft_printerror("Invalid number of arguments");
	while (argv[i])
	{
		if (argv[i][0] == '\0')
			ft_printerror("Invalid arguments");
		i++;
	}
}
