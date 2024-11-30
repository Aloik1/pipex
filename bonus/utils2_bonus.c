/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloiki <aloiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 14:15:11 by aloiki            #+#    #+#             */
/*   Updated: 2024/11/30 17:37:34 by aloiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*free_and_null(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i++])
		free(matrix[i]);
	free(matrix);
	return (NULL);
}

int	how_to_open(char *argv, int i)
{
	int	fd;
	
	fd = 0;
	if (i == 0)
		fd = open(argv, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (i == 1)
		fd = open(argv, O_RDONLY);
	else if (i == 2)
		fd = open(argv, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("line 1: ", 2);
		ft_putstr_fd(argv, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		exit(EXIT_FAILURE);
	}
	return (fd);
}
