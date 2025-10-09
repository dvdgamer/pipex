// ************************************************************************** //
//                                                                            //
//                                                       ::::::::             //
//   pipex.h                                           :+:    :+:             //
//                                                    +:+                     //
//   By: dponte <dponte@student.codam.nl>            +#+                      //
//                                                  +#+                       //
//   Created: 2025/09/02 00:02:21 by dponte       #+#    #+#                  //
//   Updated: 2025/09/02 00:07:18 by dponte       ########   odam.nl          //
//                                                                            //
// ************************************************************************** //

#include <stdio.h>
#include <error.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdbool.h>
#include "libft/libft.h"

int		open_file(char* file);
void	create_pipe(char **argv, char **paths, char **env);
