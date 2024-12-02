/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloiki <aloiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 17:05:48 by aloiki            #+#    #+#             */
/*   Updated: 2024/12/02 19:13:39 by aloiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	child_process(char **argv, char **envp, int *fd)
{
	int	infile;

	infile = open(argv[1], O_RDONLY, 0777);
	if (infile == -1)
	{
		ft_putstr_fd("line 1: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		exit(EXIT_FAILURE);
	}
	if (fd[1] == -1 || fd[0] == -1)
		ft_printerror("Invalid file descriptor\n");
	dup2(fd[1], STDOUT_FILENO);
	dup2(infile, STDIN_FILENO);
	close(fd[0]);
	execute_command(argv[2], envp);
}

static void	parent_process(char **argv, char **envp, int *fd)
{
	int	outfile;

	outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dup2(fd[0], STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	close(fd[1]);
	execute_command(argv[3], envp);
}

int	main(int argc, char **argv, char **envp)
{
	pid_t	child;
	int		files[2];

	check_valid_args(argc, argv);
	if (pipe(files) == -1)
		ft_printerror("Couldn't create pipe");
	child = fork();
	if (child == -1)
		ft_printerror("Forking failed\n");
	if (child == 0)
	{
		child_process(argv, envp, files);
		exit(0);
	}
	waitpid(child, NULL, 0);
	parent_process(argv, envp, files);
}
