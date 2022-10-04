/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 09:28:47 by mraymond          #+#    #+#             */
/*   Updated: 2022/10/03 10:49:08 by mraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <unistd.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include "libft/header/libft.h"
# include <signal.h>
# include <errno.h>

#define OPEN_REDIR_IN "O_RDONLY, 0777"
#define OPEN_REDIR_OUT "O_WRONLY | O_CREATE, 0777"
#define OPEN_REDIR_OUT_APPEND "O_WRONLY | "


int	redirection(char *redirection)
{
	int	*cmd;
	int		fd_file;
	char	*filename;
	int		i;

	
	if (ft_strncmp(redirection, "<<", 2) == 0)
		//IN heredoc
	else if (ft_strncmp(redirection, ">>", 2) == 0)
		//OUT append
	else if (ft_strncmp(redirection, "<>", 2) == 0)
		//CREATE N CLOSE
	else if (redirection[0] == '<')
		//IN replace
	else if (redirection[0] == '>')
		//OUT replace
	
		
}

