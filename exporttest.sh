#!/bin/bash

cd libft
make bonus
cd ..
gcc -g -Wall -Wextra -Werror -I./includes -I./libft srcs/cd.c srcs/pwd.c srcs/exit.c srcs/env.c srcs/unset.c srcs/export.c srcs/command_utils.c srcs/env_utils.c -Llibft -lft -D EXPORTTEST -o export.out

YELLOW=$(printf '\033[33m')
CYAN=$(printf '\033[36m')
RESET=$(printf '\033[0m')

printf "${YELLOW}%s${RESET}\n" "[mini] export"
./export.out export > mini_export
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] export"
echo "export > bash_export" | bash
echo $?
echo "===diff check start==="
diff mini_export bash_export
echo "===diff check end==="
rm mini_export bash_export
echo

printf "${YELLOW}%s${RESET}\n" "[mini] export --"
./export.out export -- > mini_export
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] export --"
echo "export -- > bash_export" | bash
echo $?
echo "===diff check start==="
diff mini_export bash_export
echo "===diff check end==="
rm mini_export bash_export
echo

printf "${CYAN}%s${RESET}\n" "export EXPORTTEST=0123"
export EXPORTTEST=0123
printf "${YELLOW}%s${RESET}\n" "[mini] export"
./export.out export > mini_export
echo $?
printf "${CYAN}%s${RESET}\n" "export EXPORTTEST=0123"
export EXPORTTEST=0123
printf "${YELLOW}%s${RESET}\n" "[bash] export"
echo "export > bash_export" | bash
echo $?
echo "===diff check start==="
diff mini_export bash_export
echo "===diff check end==="
printf "${CYAN}%s${RESET}\n" "unset EXPORTTEST"
unset EXPORTTEST
rm mini_export bash_export
echo

# nameのみの環境変数はシェル起動時に引き継がない
printf "${CYAN}%s${RESET}\n" "export EXPORTTEST"
export EXPORTTEST
printf "${YELLOW}%s${RESET}\n" "[mini] export"
./export.out export > mini_export
echo $?
printf "${CYAN}%s${RESET}\n" "export EXPORTTEST"
export EXPORTTEST
printf "${YELLOW}%s${RESET}\n" "[bash] export"
echo "export > bash_export" | bash
echo $?
echo "===diff check start==="
diff mini_export bash_export
echo "===diff check end==="
rm mini_export bash_export
echo

printf "${YELLOW}%s${RESET}\n" "[mini] export -z"
./export.out export -z
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] export -z"
echo "export -z" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] export \"\""
./export.out export ""
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] export \"\""
echo "export \"\"" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] export -"
./export.out export -
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] export -"
echo "export -" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] export ---"
./export.out export ---
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] export ---"
echo "export ---" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] export -- -z"
./export.out export -- -z
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] export -- -z"
echo "export -- -z" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] export EXPORTTEST"
./export.out export EXPORTTEST > mini_export
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] export EXPORTTEST"
echo "export EXPORTTEST" | bash
echo $?
echo "export EXPORTTEST; export > bash_export" | bash
echo "===diff check start==="
diff mini_export bash_export
echo "===diff check end==="
rm mini_export bash_export
echo

printf "${YELLOW}%s${RESET}\n" "[mini] export EXPORTTEST="
./export.out export EXPORTTEST= > mini_export
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] export EXPORTTEST="
echo "export EXPORTTEST=" | bash
echo $?
echo "export EXPORTTEST= ; export > bash_export" | bash
echo "===diff check start==="
diff mini_export bash_export
echo "===diff check end==="
rm mini_export bash_export
echo

printf "${YELLOW}%s${RESET}\n" "[mini] export EXPORTTEST=0123"
./export.out export EXPORTTEST=0123 > mini_export
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] export EXPORTTEST=0123"
echo "export EXPORTTEST=0123" | bash
echo $?
echo "export EXPORTTEST=0123 ; export > bash_export" | bash
echo "===diff check start==="
diff mini_export bash_export
echo "===diff check end==="
rm mini_export bash_export
echo

printf "${YELLOW}%s${RESET}\n" "[mini] export EXPORTTEST=\"B=C\""
./export.out export EXPORTTEST="B=C" > mini_export
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] export EXPORTTEST=\"B=C\""
echo "export EXPORTTEST=\"B=C\"" | bash
echo $?
echo "export EXPORTTEST=\"B=C\" ; export > bash_export" | bash
echo "===diff check start==="
diff mini_export bash_export
echo "===diff check end==="
rm mini_export bash_export
echo

printf "${YELLOW}%s${RESET}\n" "[mini] export \"EXPORTTEST=B\"=C"
./export.out export "EXPORTTEST=B"=C > mini_export
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] export \"EXPORTTEST=B\"=C"
echo "export \"EXPORTTEST=B\"=C" | bash
echo $?
echo "export \"EXPORTTEST=B\"=C ; export > bash_export" | bash
echo "===diff check start==="
diff mini_export bash_export
echo "===diff check end==="
rm mini_export bash_export
echo

printf "${YELLOW}%s${RESET}\n" "[mini] export EXPORTTEST=\"aaa     b\""
./export.out export EXPORTTEST="aaa     b" > mini_export
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] export EXPORTTEST=\"aaa     b\""
echo "export EXPORTTEST=\"aaa     b\"" | bash
echo $?
echo "export EXPORTTEST=\"aaa     b\" ; export > bash_export" | bash
echo "===diff check start==="
diff mini_export bash_export
echo "===diff check end==="
rm mini_export bash_export
echo

printf "${YELLOW}%s${RESET}\n" "[mini] export EXPORTTEST==="
./export.out export EXPORTTEST=== > mini_export
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] export EXPORTTEST==="
echo "export EXPORTTEST===" | bash
echo $?
echo "export EXPORTTEST=== ; export > bash_export" | bash
echo "===diff check start==="
diff mini_export bash_export
echo "===diff check end==="
rm mini_export bash_export
echo

printf "${YELLOW}%s${RESET}\n" "[mini] export EXPORTTEST=\\\"hello\\\""
./export.out export EXPORTTEST=\"hello\" > mini_export
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] export EXPORTTEST=\\\"hello\\\""
echo "export EXPORTTEST=\\\"hello\\\"" | bash
echo $?
echo "export EXPORTTEST=\\\"hello\\\" ; export > bash_export" | bash
echo "===diff check start==="
diff mini_export bash_export
echo "===diff check end==="
rm mini_export bash_export
echo

printf "${YELLOW}%s${RESET}\n" "[mini] export EXPORTTEST=\$hello"
./export.out export EXPORTTEST=\$hello > mini_export
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] export EXPORTTEST=\$hello"
echo "export EXPORTTEST=\\\$hello" | bash
echo $?
echo "export EXPORTTEST=\\\$hello ; export > bash_export" | bash
echo "===diff check start==="
diff mini_export bash_export
echo "===diff check end==="
rm mini_export bash_export
echo

printf "${YELLOW}%s${RESET}\n" "[mini] export EXPORTTEST=\\hello"
./export.out export EXPORTTEST=\\hello > mini_export
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] export EXPORTTEST=\\hello"
echo "export EXPORTTEST=\\\\hello" | bash
echo $?
echo "export EXPORTTEST=\\\\hello ; export > bash_export" | bash
echo "===diff check start==="
diff mini_export bash_export
echo "===diff check end==="
rm mini_export bash_export
echo

printf "${YELLOW}%s${RESET}\n" "[mini] export EXPORTTEST=\`hello"
./export.out export EXPORTTEST=\`hello > mini_export
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] export EXPORTTEST=\`hello"
echo "export EXPORTTEST=\\\`hello" | bash
echo $?
echo "export EXPORTTEST=\\\`hello ; export > bash_export" | bash
echo "===diff check start==="
diff mini_export bash_export
echo "===diff check end==="
rm mini_export bash_export
echo

printf "${YELLOW}%s${RESET}\n" "[mini] export EXPORTTEST= 0123"
./export.out export EXPORTTEST= 0123 > mini_export
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] export EXPORTTEST= 0123"
echo "export EXPORTTEST= 0123" | bash
echo $?
echo "export EXPORTTEST= 0123 ; export > bash_export" | bash
echo "===diff check start==="
diff mini_export bash_export
echo "===diff check end==="
rm mini_export bash_export
echo

# $mark
printf "${YELLOW}%s${RESET}\n" "[mini] export EXPORTTEST$=0123"
./export.out export EXPORTTEST$=0123
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] export EXPORTTEST$=0123"
echo "export EXPORTTEST$=0123" | bash
echo $?
echo

# 先頭に数字
printf "${YELLOW}%s${RESET}\n" "[mini] export 0EXPORTTEST=0123"
./export.out export 0EXPORTTEST=0123
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] export 0EXPORTTEST=0123"
echo "export 0EXPORTTEST=0123" | bash
echo $?
echo

# 途中に数字
printf "${YELLOW}%s${RESET}\n" "[mini] export EXP0RT0TEST=0123"
./export.out export EXPORT0TEST=0123 > mini_export
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] export 0EXPORT0TEST=0123"
echo "export EXPORT0TEST=0123" | bash
echo $?
echo "export EXPORT0TEST=0123 ; export> bash_export" | bash
echo "===diff check start==="
diff mini_export bash_export
echo "===diff check end==="
rm mini_export bash_export
echo
echo

# 最後に数字
printf "${YELLOW}%s${RESET}\n" "[mini] export EXP0RTTEST0=0123"
./export.out export EXPORTTEST0=0123 > mini_export
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] export 0EXPORTTEST0=0123"
echo "export EXPORTTEST0=0123" | bash
echo $?
echo "export EXPORTTEST0=0123 ; export > bash_export" | bash
echo "===diff check start==="
diff mini_export bash_export
echo "===diff check end==="
rm mini_export bash_export
echo

# _ (under score)
printf "${YELLOW}%s${RESET}\n" "[mini] export _A=0123"
./export.out export _A=0123 > mini_export
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] export _A=0123"
echo "export _A=0123" | bash
echo $?
echo "export _A=0123 ; export > bash_export" | bash
echo "===diff check start==="
diff mini_export bash_export
echo "===diff check end==="
rm mini_export bash_export
echo

# OLDPWDにexportで値を設定
printf "${YELLOW}%s${RESET}\n" "[mini] export OLDPWD=override_oldpwd"
./export.out export OLDPWD=override_oldpwd > mini_export
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] export OLDPWD=override_oldpwd"
echo "export OLDPWD=override_oldpwd" | bash
echo $?
echo "export OLDPWD=override_oldpwd ; export > bash_export" | bash
echo "===diff check start==="
diff mini_export bash_export
echo "===diff check end==="
rm mini_export bash_export
echo

# PWDがunsetされた状態でminishell起動
printf "${CYAN}%s${RESET}\n" "unset PWD"
unset PWD
printf "${YELLOW}%s${RESET}\n" "[mini] export"
./export.out export > mini_export
echo $?
printf "${CYAN}%s${RESET}\n" "unset PWD"
unset PWD
printf "${YELLOW}%s${RESET}\n" "[bash] export"
echo "export > bash_export" | bash
echo $?
echo "===diff check start==="
diff mini_export bash_export
echo "===diff check end==="
rm mini_export bash_export
echo
