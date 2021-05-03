#!/bin/bash

cd libft
make bonus
cd ..
gcc -g -Wall -Wextra -Werror -I./includes -I./libft \
    srcs/cd.c srcs/cd_error.c srcs/cd_path_utils.c srcs/cd_fullpath.c \
	srcs/echo.c srcs/pwd.c srcs/exit.c \
	srcs/env.c srcs/unset.c \
    srcs/export.c srcs/export_print.c srcs/export_setenv.c \
    srcs/init_env.c srcs/env_utils.c srcs/env_utils2.c \
    srcs/env_sort.c srcs/env_copy.c \
    srcs/utils/utils.c srcs/utils/minishell_errors.c srcs/utils/command_utils.c \
	srcs/utils/command_errors.c srcs/utils/utils_tnishina.c srcs/minishell.c\
	srcs/make_command.c srcs/make_token.c srcs/get_next_line.c srcs/expand_env.c \
    srcs/utils/tlist_utils.c srcs/utils/split_utils.c srcs/set_redirection.c\
    srcs/handle_signal.c srcs/add_space.c srcs/extract_redirect.c srcs/remove_escape.c\
    -Llibft -lft -o multipipe.out #-D LEAKS

YELLOW=$(printf '\033[33m')
CYAN=$(printf '\033[36m')
RESET=$(printf '\033[0m')

printf "\n${CYAN}%s${RESET}\n\n" "***Test starts***"

printf "${YELLOW}%s${RESET}\n\n" "[mini] echo \$?"
echo "echo \$?" | ./multipipe.out
echo
printf "${YELLOW}%s${RESET}\n\n" "[bash] echo \$?"
echo "echo \$?" | bash
echo

printf "${YELLOW}%s${RESET}\n\n" "[mini] echo \$PWD?"
echo "echo \$PWD?" | ./multipipe.out
echo
printf "${YELLOW}%s${RESET}\n\n" "[bash] echo \$PWD?"
echo "echo \$PWD?" | bash
echo

printf "${YELLOW}%s${RESET}\n\n" "[mini] echo \$?PWD"
echo "echo \$?PWD" | ./multipipe.out
echo
printf "${YELLOW}%s${RESET}\n\n" "[bash] echo \$?PWD"
echo "echo \$?PWD" | bash
echo

printf "${YELLOW}%s${RESET}\n\n" "[mini] echo \$?."
echo "echo \$?." | ./multipipe.out
echo
printf "${YELLOW}%s${RESET}\n\n" "[bash] echo \$?."
echo "echo \$?." | bash
echo

printf "${YELLOW}%s${RESET}\n\n" "[mini] echo \$.?"
echo "echo \$.?" | ./multipipe.out
echo
printf "${YELLOW}%s${RESET}\n\n" "[bash] echo \$.?"
echo "echo \$.?" | bash
echo

printf "${YELLOW}%s${RESET}\n\n" "[mini] echo \$?\$?"
echo "echo \$?\$?" | ./multipipe.out
echo
printf "${YELLOW}%s${RESET}\n\n" "[bash] echo \$?\$?"
echo "echo \$?\$?" | bash
echo

printf "${YELLOW}%s${RESET}\n\n" "[mini] echo \$USER\$?"
echo "echo \$USER\$?" | ./multipipe.out
echo
printf "${YELLOW}%s${RESET}\n\n" "[bash] echo \$USER\$?"
echo "echo \$USER\$?" | bash
echo

printf "${YELLOW}%s${RESET}\n\n" "[mini] echo \"\"\$?\"\""
echo "echo \"\"\$?\"\"" | ./multipipe.out
echo
printf "${YELLOW}%s${RESET}\n\n" "[bash] echo \"\"\$?\"\""
echo "echo \"\"\$?\"\"" | bash
echo

printf "${YELLOW}%s${RESET}\n\n" "[mini] echo \"\$?\""
echo "echo \"\$?\"" | ./multipipe.out
echo
printf "${YELLOW}%s${RESET}\n\n" "[bash] echo \"\$?\""
echo "echo \"\$?\"" | bash
echo

printf "${YELLOW}%s${RESET}\n\n" "[mini] echo \\ "
echo "echo \\ " | ./multipipe.out
echo
printf "${YELLOW}%s${RESET}\n\n" "[bash] echo \\ "
echo "echo \\ " | bash
echo

printf "${YELLOW}%s${RESET}\n\n" "[mini] echo hello 2147483647> file"
echo "echo hello 2147483647> file" | ./multipipe.out
echo
printf "${YELLOW}%s${RESET}\n\n" "[bash] echo hello 2147483647> file"
echo "echo hello 2147483647> file" | bash
echo

#未対応です
printf "\n${CYAN}%s${RESET}\n\n" "未対応です"
printf "${YELLOW}%s${RESET}\n\n" "[mini] whereis ls | cat -e | cat -e > test"
echo "whereis ls | cat -e | cat -e > test" | ./multipipe.out
echo
printf "${YELLOW}%s${RESET}\n\n" "[bash] whereis ls | cat -e | cat -e > test"
echo "whereis ls | cat -e | cat -e > test" | bash
echo

printf "${YELLOW}%s${RESET}\n\n" "[mini] echo \">\""
echo "echo \">\"" | ./multipipe.out
echo
printf "${YELLOW}%s${RESET}\n\n" "[bash] echo \">\""
echo "echo \">\"" | bash
echo

printf "${YELLOW}%s${RESET}\n\n" "[mini] touch \">\""
echo "touch \">\"" | ./multipipe.out
rm ">"
echo
printf "${YELLOW}%s${RESET}\n\n" "[bash] touch \">\""
echo "touch \">\"" | bash
rm ">"
echo

printf "${YELLOW}%s${RESET}\n\n" "[mini] echo something > > file"
echo "echo something > > file" | ./multipipe.out
echo
printf "${YELLOW}%s${RESET}\n\n" "[bash] echo something > > file"
echo "echo something > > file" | bash
echo

printf "${YELLOW}%s${RESET}\n\n" "[mini] > file cd wtf ; cat file"
echo "> file cd wtf ; cat file" | ./multipipe.out
echo
printf "${YELLOW}%s${RESET}\n\n" "[bash] > file cd wtf ; cat file"
echo "> file cd wtf ; cat file" | bash
echo

printf "${YELLOW}%s${RESET}\n\n" "[mini] cat < Makefile > file"
echo "cat < Makefile > file" | ./multipipe.out
rm file
echo
printf "${YELLOW}%s${RESET}\n\n" "[bash] cat < Makefile > file"
echo "cat < Makefile > file" | bash
rm file
echo

printf "${YELLOW}%s${RESET}\n\n" "[mini] export TEST=hello; echo \$TEST"
echo "export TEST=hello; echo \$TEST" | ./multipipe.out
echo
printf "${YELLOW}%s${RESET}\n\n" "[bash] export TEST=hello; echo \$TEST"
echo "export TEST=hello; echo \$TEST" | bash
echo

printf "${YELLOW}%s${RESET}\n\n" "[mini] echo $"
echo "echo $" | ./multipipe.out
echo
printf "${YELLOW}%s${RESET}\n\n" "[bash] echo $"
echo "echo $" | bash
echo

printf "${YELLOW}%s${RESET}\n\n" "[mini] echo \"$\""
echo "echo \"$\"" | ./multipipe.out
echo
printf "${YELLOW}%s${RESET}\n\n" "[bash] echo \"$\""
echo "echo \"$\"" | bash
echo

printf "${YELLOW}%s${RESET}\n\n" "[mini] echo \\$"
echo "echo \\$" | ./multipipe.out
echo
printf "${YELLOW}%s${RESET}\n\n" "[bash] echo \\$"
echo "echo \\$" | bash
echo

printf "${YELLOW}%s${RESET}\n\n" "[mini] echo \"\\$\""
echo "echo \"\\$\"" | ./multipipe.out
echo
printf "${YELLOW}%s${RESET}\n\n" "[bash] echo \"\\$\""
echo "echo \"\\$\"" | bash
echo

printf "${YELLOW}%s${RESET}\n\n" "[mini] echo \\\"\\\""
echo "echo \\\"\\\"" | ./multipipe.out
echo
printf "${YELLOW}%s${RESET}\n\n" "[bash] echo \\\"\\\""
echo "echo \\\"\\\"" | bash
echo

printf "${YELLOW}%s${RESET}\n\n" "[mini] echo test >"
echo "echo test >" | ./multipipe.out
echo
printf "${YELLOW}%s${RESET}\n\n" "[bash] echo test >"
echo "echo test >" | bash
echo

printf "${YELLOW}%s${RESET}\n\n" "[mini] echo test > >"
echo "echo test > >" | ./multipipe.out
echo
printf "${YELLOW}%s${RESET}\n\n" "[bash] echo test > >"
echo "echo test > >" | bash
echo

printf "${YELLOW}%s${RESET}\n\n" "[mini] echo test > >>"
echo "echo test > >>" | ./multipipe.out
echo
printf "${YELLOW}%s${RESET}\n\n" "[bash] echo test > >>"
echo "echo test > >>" | bash
echo

printf "${YELLOW}%s${RESET}\n\n" "[mini] echo test <"
echo "echo test <" | ./multipipe.out
echo
printf "${YELLOW}%s${RESET}\n\n" "[bash] echo test <"
echo "echo test <" | bash
echo

printf "\n${CYAN}%s${RESET}\n\n" "私達の実装だと<<をカバーしていないので、エラーメッセージも違っています"
printf "${YELLOW}%s${RESET}\n\n" "[mini] echo test < <<"
echo "echo test < <<" | ./multipipe.out
echo
printf "${YELLOW}%s${RESET}\n\n" "[bash] echo test < <<"
echo "echo test < <<" | bash
echo

printf "${YELLOW}%s${RESET}\n\n" "[mini] echo 1 >file; cat file"
echo "echo 1 >file; cat file" | ./multipipe.out
echo
rm file
printf "${YELLOW}%s${RESET}\n\n" "[bash] echo 1 >file; cat file"
echo "echo 1 >file; cat file" | bash
echo
rm file

printf "${YELLOW}%s${RESET}\n\n" "[mini] echo 2 >file"
echo "echo 2 >file" | ./multipipe.out
echo
rm file
printf "${YELLOW}%s${RESET}\n\n" "[bash] echo 2 >file"
echo "echo 2 >file" | bash
echo
rm file

printf "${YELLOW}%s${RESET}\n\n" "[mini] echo 256 >file"
echo "echo 256 >file" | ./multipipe.out
echo
rm file
printf "${YELLOW}%s${RESET}\n\n" "[bash] echo 256 >file"
echo "echo 256 >file" | bash
echo
rm file

printf "${YELLOW}%s${RESET}\n\n" "[mini] echo 2>file"
echo "echo 2>file" | ./multipipe.out
echo
rm file
printf "${YELLOW}%s${RESET}\n\n" "[bash] echo 2>file"
echo "echo 2>file" | bash
echo
rm file

printf "${YELLOW}%s${RESET}\n\n" "[mini] echo 2 \'1\'>file; cat file"
echo "echo 2 \'1\'>file; cat file" | ./multipipe.out
echo
rm file
printf "${YELLOW}%s${RESET}\n\n" "[bash] echo 2 \'1\'>file; cat file"
echo "echo 2 \'1\'>file; cat file" | bash
echo
rm file

printf "${YELLOW}%s${RESET}\n\n" "[mini] 1>file echo 1"
echo "1>file echo 1" | ./multipipe.out
echo
rm file
printf "${YELLOW}%s${RESET}\n\n" "[bash] 1>file echo 1"
echo "1>file echo 1" | bash
echo
rm file

printf "${YELLOW}%s${RESET}\n\n" "[mini] touch file; chmod 0 file; echo hello >file"
echo "touch file; chmod 0 file; echo hello >file" | ./multipipe.out
echo
rm -f file
printf "${YELLOW}%s${RESET}\n\n" "[bash] touch file; chmod 0 file; echo hello >file"
echo "touch file; chmod 0 file; echo hello >file" | bash
echo
rm -rf file

printf "${YELLOW}%s${RESET}\n\n" "[mini] echo hello > ./"
echo "echo hello > ./" | ./multipipe.out
echo
printf "${YELLOW}%s${RESET}\n\n" "[bash] echo hello > ./"
echo "echo hello > ./" | bash
echo

printf "${YELLOW}%s${RESET}\n\n" "[mini] echo hello >>>> file"
echo "echo hello >>>> file" | ./multipipe.out
echo
printf "${YELLOW}%s${RESET}\n\n" "[bash] echo hello >>>> file"
echo "echo hello >>>> file" | bash
echo

printf "${YELLOW}%s${RESET}\n\n" "[mini] echo hello \">\""
echo "echo hello \">\"" | ./multipipe.out
echo
printf "${YELLOW}%s${RESET}\n\n" "[bash] echo hello \">\""
echo "echo hello \">\"" | bash
echo

printf "${YELLOW}%s${RESET}\n\n" "[mini] echo hi > file1; cat < file1 > file2; diff file1 file2"
echo "echo hi > file1; cat < file1 > file2; diff file1 file2" | ./multipipe.out
echo
rm file1 file2
printf "${YELLOW}%s${RESET}\n\n" "[bash] echo hi > file1; cat < file1 > file2; diff file1 file2"
echo "echo hi > file1; cat < file1 > file2; diff file1 file2" | bash
echo
rm file1 file2

printf "${YELLOW}%s${RESET}\n\n" "[mini] export ZERO=0; echo \$ZERO> file1; cat file1"
echo "export ZERO=0; echo \$ZERO> file1; cat file1" | ./multipipe.out
echo
rm file1
printf "${YELLOW}%s${RESET}\n\n" "[bash] export ZERO=0; echo \$ZERO> file1; cat file1"
echo "export ZERO=0; echo \$ZERO> file1; cat file1" | bash
echo
rm file1

printf "${YELLOW}%s${RESET}\n\n" "[mini] echo hello >>>file"
echo "echo hello >>>file" | ./multipipe.out
echo
printf "${YELLOW}%s${RESET}\n\n" "[bash] echo hello >>>file"
echo "echo hello >>>file" | bash
echo

printf "${YELLOW}%s${RESET}\n\n" "[mini] echo hello > 1; cat 1"
echo "echo hello > 1; cat 1" | ./multipipe.out
echo
rm "1"
printf "${YELLOW}%s${RESET}\n\n" "[bash] echo hello > 1; cat 1"
echo "echo hello > 1; cat 1" | bash
echo
rm "1"

printf "${YELLOW}%s${RESET}\n\n" "[mini] echo hello \">\""
echo "echo hello \">\"" | ./multipipe.out
echo
printf "${YELLOW}%s${RESET}\n\n" "[bash] echo hello \">\""
echo "echo hello \">\"" | bash
echo
