/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araysse <araysse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 11:27:46 by araysse           #+#    #+#             */
/*   Updated: 2022/10/04 15:38:51 by araysse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

void	pr_struct(t_cmd *str)
{
	int		i;
	t_cmd	*cmd;

	cmd = str;
	i = 0;
	while (cmd)
	{
		i = 0;
		printf("########  STRUCT  ######\n");
		while (cmd->cmd[i])
		{
			printf(" ---cmd[%d]--->   %s\n", i, cmd->cmd[i]);
			i++;
		}
		printf("infile : %d\n", cmd->infile);
		printf("outfile : %d\n", cmd->outfile);
		while (cmd->redirection)
		{
			printf("redirection : %s\n", cmd->redirection->type);
			printf("redirection : %s\n", cmd->redirection->value);
			cmd->redirection = cmd->redirection->next;
		}
		cmd = cmd->next;
	}
	printf("nanannanananaanan \n");
}

void	function(t_cmd **cmd, lexer_t **lexer, char **env, token_t **token)
{
	char	*str;
	t_cmd	*new;
	t_redir	*redir;

	redir = NULL;
	str = NULL;
	new = NULL;
	while ((*token)->type != token_pipe)
	{
		if (is_redirection(*token))
			ft_lstadd_bak(&redir, struct_redir((*token), (*lexer), env));
		else
			str = struct_cmd((*lexer), (*token), str, env);
		(*token) = lexer_next((*lexer), env);
		if ((*token) == NULL)
			break ;
	}
	if (*token)
		ft_after_pipe((*lexer), (*token), env);
	ft_lstnew(&new, &(*redir), str);
	new->next = NULL;
	ft_lstadd_back(&(*cmd), new);
	redir = NULL;
	str = NULL;
}

void	ft_help_main2(t_cmd **cmd, lexer_t **lexer, char **env)
{
	token_t	*token;

	token = NULL;
	token = lexer_next((*lexer), env);
	while (token != NULL)
	{
		function(&(*cmd), &(*lexer), env, &token);
		token = lexer_next((*lexer), env);
	}
}

void	ft_help_main1(t_cmd **cmd, char **env)
{
	char	*inpt;
	lexer_t	*lexer;

	inpt = readline(YELLOW "bash-0.0 " WHITE);
	if (!inpt)
	{
		g_glob[1] = 0;
		// ft_exit_sig("exit");
	}
	if (ft_strcmp(inpt, ""))
	{
		add_history(inpt);
		lexer = init_lexer(inpt);
		ft_help_main2(&(*cmd), &lexer, env);
		// if (g_glob[0] == 0)
		// 	ft_get_exec(shell, cmd);
		pr_struct(*cmd);
		ft_free_struct(&(*cmd));
	}
}

int	main(int ac, char **av, char **env)
{
	t_shell	*shell;
	t_cmd	*cmd;

	(void)(ac);
	(void)(av);
	cmd = NULL;
	shell = malloc(sizeof(t_shell));
	ft_init_env(shell, env);
	g_glob[1] = 0;
	while (1)
	{
		g_glob[0] = 0;
		// signal(SIGINT, ft_sig_int);
		// signal(SIGQUIT, SIG_IGN);
		ft_help_main1(&cmd, shell->env);
	}
}
