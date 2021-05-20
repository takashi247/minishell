#ifndef TEST_BUILTIN_H
# define TEST_BUILTIN_H

# include "minishell_tnishina.h"

/* test_init.c */
int	test_init_minishell(void);
int	test_finalize_minishell(char ***args_head, const int exit_code);
/* test_exec.c */
int	test_commands(char **args);
/* test_launch.c */
int	test_launch(char **args);
/* test_cd.c */
int	test_cd(char **args, const t_bool is_nodir);
int	test_cdnodir(char **args);
int	test_cdnodir2(char **args);
int	test_cd_and_pwd(char **args);

#endif
