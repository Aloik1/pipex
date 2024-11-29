/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloiki <aloiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 18:24:31 by aloiki            #+#    #+#             */
/*   Updated: 2024/11/30 00:19:58 by aloiki           ###   ########.fr       */
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
		path_piece = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(path_piece, command);
		free(path_piece);
		if (access(full_path, F_OK) == 0)
			return (full_path);
		free(full_path);
	}
	i = 0;
	while (paths[i++])
		free(paths[i]);
	free(paths);
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

void	execute_command(char *argv, char **envp)
{
	char	**command;
	char	*path;
	int		i;

	i = 0;
	command = ft_split(argv, ' ');
	path = path_finder(command[0], envp);
	if (!path)
	{
		while (command[i++])
			free(command[i]);
		free(command);
		ft_printerror("Couldn't find path");
	}
	if (ft_strchr(argv, 39) || ft_strchr(argv, 34))
		command = modify_command(argv, command);
	if (execve(path, command, envp) == -1)
		ft_printerror("Couldn't execute new process");
}
