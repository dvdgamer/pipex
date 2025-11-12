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
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "libft/libft.h"

int		open_file(char *file);
int		execute_cmd(char *paths[], char *arg_cmd, char **env);
int		main_loop(int argc, char *argv[], char *env[], char *paths[]);
char	**extract_env(char *env[]);
bool	empty_str_in_argv(char **argv);
void	create_pipe(char **argv, char **env);
