/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloiki <aloiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 17:05:48 by aloiki            #+#    #+#             */
/*   Updated: 2024/12/02 19:24:47 by aloiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	read_line_by_line(int *fd, char *limiter)
{
	char	*line;
	char	*line_no_nl;

	close(fd[0]);
	line = get_next_line(0);
	while (line)
	{
		line_no_nl = ft_strtrim(line, "\n");
		if (ft_strncmp(line_no_nl, limiter, ft_strlen(line)) == 0)
			exit(1);
		free(line_no_nl);
		ft_printf("> ");
		write(fd[1], line, ft_strlen(line));
		free(line);
		line = get_next_line(0);
	}
}

static void	read_from_buffer(char *limiter, int argc)
{
	pid_t	separator;
	int		fd[2];

	if (pipe(fd) == -1)
		ft_printerror("Pipe creation failed");
	if (argc < 6)
		ft_printerror("Invalid format");
	ft_printf("> ");
	separator = fork();
	if (separator == 0)
		read_line_by_line(fd, limiter);
	else
	{
		close(fd[1]);
		dup2(fd[0], 0);
		wait(NULL);
	}
}

static void	child_process(char *argv, char **envp)
{
	pid_t	child;
	int		fd[2];

	if (pipe(fd) == -1)
		ft_printerror("Pipe creation failed");
	child = fork();
	if (child == -1)
		ft_printerror("Forking failed");
	if (child == 0)
	{
		close(fd[0]);
		dup2(fd[1], 1);
		execute_command(argv, envp);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], 0);
		waitpid(child, NULL, 0);
	}
}

static void	valid(int argc, char **argv, char **envp)
{
	int		infile;
	int		outfile;
	int		i;

	i = 0;
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		i = 3;
		outfile = how_to_open(argv[argc - 1], 0);
		read_from_buffer(argv[2], argc);
	}
	else
	{
		i = 2;
		outfile = how_to_open(argv[argc - 1], 2);
		infile = how_to_open(argv[1], 1);
		dup2(infile, 0);
	}
	while (i < argc - 2)
		child_process(argv[i++], envp);
	dup2(outfile, STDOUT_FILENO);
	execute_command(argv[argc - 2], envp);
}

int	main(int argc, char **argv, char **envp)
{
	check_valid_args(argc, argv);
	if (argc >= 5)
		valid(argc, argv, envp);
}
