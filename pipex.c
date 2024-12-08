/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloiki <aloiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 17:05:48 by aloiki            #+#    #+#             */
/*   Updated: 2024/12/03 23:38:43 by aloiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	child_process(char **argv, char **envp, int *fd)
{
	int	infile;

	infile = open(argv[1], O_RDONLY);
	if (infile == -1)
	{
		ft_putstr_fd("line 1: ", 2);
		ft_putstr_fd(argv[1], 2);
		perror(" ");
		exit(127);
	}
	if (fd[1] == -1 || fd[0] == -1)
		ft_printerror("Invalid file descriptor\n");
	dup2(fd[1], STDOUT_FILENO);
	dup2(infile, STDIN_FILENO);
	close(fd[0]);
	execute_command(argv[2], envp);
}

static void	other_child_process(char **argv, char **envp, int *fd)
{
	int	outfile;

	outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile == -1)
	{
		ft_putstr_fd("line 1: ", 2);
		ft_putstr_fd(argv[1], 2);
		perror(" ");
		exit(127);
	}
	dup2(fd[0], STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	close(fd[1]);
	execute_command(argv[3], envp);
}

int	main(int argc, char **argv, char **envp)
{
	pid_t	child1;
	pid_t	child2;
	int		files[2];

	check_valid_args(argc, argv);
	if (pipe(files) == -1)
		ft_printerror("Couldn't create pipe");
	child1 = fork();
	if (child1 == -1)
		ft_printerror("Forking failed");
	if (child1 == 0)
	{
		child_process(argv, envp, files);
		exit(0);
	}
	child2 = fork();
	if (child2 == -1)
		ft_printerror("Forking failed");
	if (child2 == 0)
	{
		other_child_process(argv, envp, files);
		exit(0);
	}
	waitpid(child1, NULL, 0);
	exit (EXIT_SUCCESS);
}
