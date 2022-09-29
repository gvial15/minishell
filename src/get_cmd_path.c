#include "../libft/libft.h"
#include "../ms.h"

static char	*get_full_path(char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
		if (!ft_strncmp(envp[i], "PATH=", 5))
			break ;
	return (&envp[i][5]);
}

static char	**get_paths(char **envp)
{
	char	*full_path;
	char	**paths;
	int		i;

	full_path = get_full_path(envp);
	paths = ft_split(full_path, ':');
	i = -1;
	while (paths[++i])
		paths[i] = ft_strjoin_gnl(paths[i], "/");
	return (paths);
}

char	*get_cmd_path(char *cmd, char **envp) // needs to parse eg: <test grep t > out
{											  // function was built to receive
	int		i;								  // parsed cmd like: "grep"
	char	*path;
	char	**paths;
	char	**cmd_without_args;

	i = -1;
	paths = get_paths(envp);
	cmd_without_args = ft_split(cmd, ' ');
	while (paths[++i])
	{
		path = ft_strjoin(paths[i], cmd_without_args[0]);
		if (access(path, X_OK) == 0)
			break ;
		free(path);
		path = NULL;
	}
	free_split(cmd_without_args);
	free_split(paths);
	return (path);
}