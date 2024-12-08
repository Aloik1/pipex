/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloiki <aloiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 14:15:11 by aloiki            #+#    #+#             */
/*   Updated: 2024/12/02 19:24:33 by aloiki           ###   ########.fr       */
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
		perror(" ");
		exit(127);
	}
	return (fd);
}

void	check_valid_args(int argc, char **argv)
{
	int	i;

	i = 0;
	if (argc < 5)
		ft_printerror("Invalid number of arguments");
	while (argv[i])
	{
		if (argv[i][0] == '\0')
			ft_printerror("Invalid arguments");
		i++;
	}
}
