/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloiki <aloiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 18:24:31 by aloiki            #+#    #+#             */
/*   Updated: 2024/12/02 14:05:05 by aloiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**init_matrix(char *arg)
{
	char	**command;
	int		i;
	int		j;

	command = (char **)malloc(sizeof(char *) * 3);
	if (!command)
		return (NULL);
	i = 0;
	j = 0;
	while (arg[i] != 32)
		i++;
	command[0] = (char *)malloc(i + 1);
	if (!command[0])
		ft_printerror("Memory allocation failed");
	while (arg[j])
		j++;
	command[1] = (char *)malloc(j - i + 2);
	if (!command[1])
		ft_printerror("Memory allocation failed");
	command[2] = NULL;
	return (command);
}

static char	**split_command(char *arg)
{
	char	**command;
	int		i;
	int		j;

	i = 0;
	j = 0;
	command = init_matrix(arg);
	while (arg[i] != 32)
	{
		command[0][i] = arg[i];
		i++;
	}
	command[0][i] = '\0';
	i++;
	while (arg[i])
	{
		command[1][j] = arg[i];
		j++;
		i++;
	}
	command[1][j] = '\0';
	return (command);
}

static char	*path_finder(char *command, char **envp)
{
	char	**paths;
	char	*path_piece;
	char	*full_path;
	int		i;

	i = 0;
	while (!ft_strnstr(envp[i], "PATH", 4))
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i++])
	{
		if (paths[i] == NULL)
			return (free_and_null(paths));
		path_piece = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(path_piece, command);
		free(path_piece);
		if (access(full_path, F_OK) == 0)
			return (full_path);
		if (full_path != NULL)
			free(full_path);
	}
	return (NULL);
}

static char	**modify_command(char *argv, char **command)
{
	int	i;

	i = 0;
	while (command[i++])
		free(command[i]);
	free(command);
	command = split_command(argv);
	if (ft_strchr(argv, 39) && ft_strchr(argv, 34))
	{
		if (command[1][0] == 34)
			command[1] = ft_strtrim(command[1], "\"");
		else
		{
			command[1] = ft_strtrim(command[1], "\"");
			command[1] = ft_strtrim(command[1], "\'");
		}
	}
	else if (ft_strchr(argv, 34))
		command[1] = ft_strtrim(command[1], "\"");
	else if (ft_strchr(argv, 39))
		command[1] = ft_strtrim(command[1], "\'");
	return (command);
}

void	execute_command(char *argv, char **envp)//, int fd)
{
	char	**command;
	char	*path;

	command = ft_split(argv, ' ');
	path = path_finder(command[0], envp);
	if (!path)
	{
		ft_putstr_fd("line 1: ", 2);
		ft_putstr_fd(command[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(EXIT_FAILURE);
	}
	if (ft_strchr(argv, 39) || ft_strchr(argv, 34))
		command = modify_command(argv, command);
	if (execve(path, command, envp) == -1)
		ft_printerror("Couldn't execute new process");
	//close(fd);
}
