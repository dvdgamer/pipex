/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   pipex.h                                           :+:    :+:             */
/*                                                    +:+                     */
/*   By: dponte <dponte@student.codam.nl>            +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/09/02 00:02:21 by dponte       #+#    #+#                  */
/*   Updated: 2025/11/12 16:12:57 by dponte       ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <error.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "libft/libft.h"

typedef struct _pipex
{
	int		maxchildren;
	int		pipefd1[2];
	int		pipefd2[2];
	char	**paths;
	pid_t	last_pid;
}	t_pipex;

int		open_file(char *file);
int		execute_cmd(char *paths[], char *arg_cmd, char **env);
int		main_loop(int argc, char *argv[], char *env[], char *paths[]);
char	**extract_env(char *env[]);
bool	empty_str_in_argv(char **argv);
void	safe_close(int *fd);
void	free_paths(char **paths);
int		create_pipes(int pipefd1[2], int pipefd2[2]);
void	back_to_parent(int i, int pipefd1[2], int pipefd2[2]);
int		wait_children_close_open_pipes(t_pipex *pipex, int i);
