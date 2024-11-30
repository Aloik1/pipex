/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloiki <aloiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 17:05:48 by aloiki            #+#    #+#             */
/*   Updated: 2024/11/30 17:56:41 by aloiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	read_from_doc(char *argv1, char *limiter, int argc)
{
	pid_t	separator;
	char	*line;
	int		doc_fd;
	int		fd[2];

	if (pipe(fd) == -1)
		ft_printerror("Pipe creation failed");
	if (argc < 6)
		ft_printerror("Invalid format");
	separator = fork();
	if (separator == 0)
	{
		close(fd[0]);
		doc_fd = open(argv1, O_RDONLY);
		line = get_next_line(doc_fd);
		while (line)
		{
			if (ft_strncmp(line, limiter, ft_strlen(line)) == 0)
				exit(1);
			write(fd[1], line, ft_strlen(line));
			line = get_next_line(doc_fd);
		}
	}
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

int	main(int argc, char **argv, char **envp)
{
	int		i;
	int		infile;
	int		outfile;

	i = 0;
	if (argc < 5)
		ft_printerror("Invalid number of arguments");
	if (argc >= 5)
	{
		if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		{
			i = 3;
			outfile = how_to_open(argv[argc - 1], 0);
			read_from_doc(argv[1], argv[2], argc);
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
}
