#include "../ms.h"


// <from grep t >out
char	*get_fd(char *cmd, char sign)
{
	char	*filename;
	int		start;
	int		i;

	start = 1;
	i = 0;
	while (cmd[i] && cmd[i] != sign)
		++i;
	while (cmd[i] == sign || cmd[i] == ' ')
		start = ++i;
	if (i == ft_strlen(cmd))
		return (NULL);
	while (cmd[i] && cmd[i] != ' ')
		i++;
	filename = ft_substr(cmd, start, i - start);
	return (filename);
}

void	get_cmds(char **envp, t_ms *ms)
{
	int		i;
	char	**split;
	t_cmd	*new_cmd;

	split = ft_split(ms->last_line, '|');
	i = -1;
	while (split[++i])
	{
		new_cmd = malloc(sizeof(t_cmd) * 1);
		new_cmd->fd_in = get_fd(split[i], '<'); // default = 0 or open <filename> at exec later
		new_cmd->fd_out = get_fd(split[i], '>');; // default = 1;
		new_cmd->cmd_path = get_cmd_path(split[i], envp);
		new_cmd->args = NULL; // todo
		new_cmd->next = NULL;
		if (ms->cmds == NULL)
			ms->cmds = new_cmd;
		else
			lst_last(ms->cmds)->next = new_cmd;
	}
}
