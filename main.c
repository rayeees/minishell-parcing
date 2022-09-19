/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araysse <araysse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 11:27:46 by araysse           #+#    #+#             */
/*   Updated: 2022/09/19 17:11:46 by araysse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_struct(t_cmd **cmd)
{
	int i;
	t_cmd *com;
	
	com = *cmd;

	i = 0;
	while ((*cmd))
	{
		i = 0;
		while ((*cmd)->cmd[i])
		{
			free((*cmd)->cmd[i]);
			i++;
		}
		free((*cmd)->cmd);
		(*cmd) = (*cmd)->next;
	}
	free((*cmd));
}

void	ft_free2(t_redirection **redir)
{
	int		i;

	i = 0;
	while (*redir)
	{
		free((*redir)->type);
		free((*redir)->value);
		(*redir) = (*redir)->next;
	}
	free ((*redir));
}

void	pr_struct(t_cmd *str)
{
	int i;
	t_cmd*	cmd;
	
	cmd = str;
	i = 0;
	while (cmd)
	{
		i = 0;
		printf("########  STRUCT  ######\n");
		while (cmd->cmd[i])
		{
			printf(" ---cmd[%d]--->   %s\n",i, cmd->cmd[i]);
			i++;
		}
		cmd =cmd->next;
	}
	printf("nanannanananaanan \n");
}

void	ppp_struct(t_redirection *str)
{
	int i;
	t_redirection*	redir;
	
	redir = str;
	i = 0;
	while (redir)
	{
		printf("########  STRUCT  ######\n");
		printf("neud n:%d type : %s, value : %s\n", i, redir->type, redir->value);
		redir =redir->next;
		i++;
	}
	printf("nonoonoonoonono \n");
}

int main(int ac, char **av, char **env)
{

	while(1)
	{
		char    *inpt;
		char	*str;
		t_redirection	*redir;
		t_cmd	*cmd;
		t_cmd	*new;
		
		cmd = NULL;
		token_t *token = (void*)0;
        inpt = readline( "minishell> " );
        add_history(inpt);
		redir = NULL;
		lexer_t *lexer = init_lexer(inpt);
		
		(void) (ac);
		(void) (av);
		while ((token = lexer_get_next_token(lexer, env)) != (void*)0)
		{
			//printf("%s\n", token->value);
			while (token->type != token_pipe)
			{
				if (is_redirection(token))
				{
					ft_lstadd_bak(&redir, struct_redir(token, lexer, env));
					//printf("heere\n");
				}
				else
					str = struct_cmd(lexer, token, str, env);
				if ((token = lexer_get_next_token(lexer, env)) == (void*)0)
					break;
			}
			//ppp_struct(redir);
			ft_lstnew(&new, redir, str);
			new->next = NULL;
			ft_lstadd_back(&cmd, new);
			//pr_struct(cmd);
			free(str);
		}
		ft_free2(&redir);
		ft_free_struct(&cmd);
	}
}

t_redirection	*struct_redir(token_t *token, lexer_t *lexer, char **env)
{
	t_redirection	*redir;

	redir = malloc(sizeof(t_redirection));
	redir->next = NULL;
	
	if (token->type == token_herdoc)
		collect_redirection(redir, lexer, token, env);
	else if (token->type == token_apend)
		collect_redirection(redir, lexer, token, env);
	else if (token->type == token_infile)
		collect_redirection(redir, lexer, token, env);
	else if (token->type == token_outfile)
		collect_redirection(redir, lexer, token, env);
	return (redir);
}

void collect_redirection(t_redirection *redir, lexer_t *lexer, token_t *token, char **env)
{
	redir->type = token->value;
	redir->value = (lexer_get_next_token(lexer, env))->value;
}

char	*struct_cmd(lexer_t *lexer, token_t *token, char *str, char **env)
{
	(void)lexer;
	(void)env;
	str = ft_strjoin(str, token->value);
	str = ft_strjoin(str, ft_getchar(127));

	return (str);
}

char	*ft_getchar(char c)
{
	char	*str;

	str = malloc(2 * sizeof(char));
	str[0] = c;
	str[1] = '\0';
	return (str);
}

int	is_redirection(token_t *token)
{
	if (token->type < 4 && token->type >= 0)
		return (1);
	return (0);
}

	