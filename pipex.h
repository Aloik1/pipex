/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloiki <aloiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 00:18:28 by aloiki            #+#    #+#             */
/*   Updated: 2024/11/30 00:18:31 by aloiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <string.h>
# include <stdio.h>
# include <sys/wait.h>
# include <sys/types.h>

void	execute_command(char *argv, char **envp);

#endif