#!/bin/bash

# USAGE ##################
#
# all test
# ./exporttest.sh
#
# all test with leaks
# ./exporttest.sh leaks
#
# make only
# ./exporttest.sh make
#
##########################

if [ "$1" = "leaks" ]; then
    make bltest # LEAK TEST
else
    make btest
fi

if [ "$1" = "make" ]; then
    exit
fi

YELLOW=$(printf '\033[33m')
CYAN=$(printf '\033[36m')
RESET=$(printf '\033[0m')

printf "${YELLOW}%s${RESET}\n" "[mini] export"
./builtin.out export > mini_export
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] export"
echo "export > bash_export" | bash
echo $?
echo "===diff check start==="
cat mini_export | grep -vE '^declare -x _=' > mini_export
cat bash_export | grep -vE '^declare -x _=' > bash_export
diff mini_export bash_export
echo "===diff check end==="
rm mini_export bash_export
echo

printf "${YELLOW}%s${RESET}\n" "[mini] export --"
./builtin.out export -- > mini_export
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] export --"
echo "export -- > bash_export" | bash
echo $?
echo "===diff check start==="
cat mini_export | grep -vE '^declare -x _=' > mini_export
cat bash_export | grep -vE '^declare -x _=' > bash_export
diff mini_export bash_export
echo "===diff check end==="
rm mini_export bash_export
echo

printf "${CYAN}%s${RESET}\n" "export EXPORTTEST=0123"
export EXPORTTEST=0123
printf "${YELLOW}%s${RESET}\n" "[mini] export"
./builtin.out export > mini_export
echo $?
printf "${CYAN}%s${RESET}\n" "export EXPORTTEST=0123"
export EXPORTTEST=0123
printf "${YELLOW}%s${RESET}\n" "[bash] export"
echo "export > bash_export" | bash
echo $?
echo "===diff check start==="
cat mini_export | grep -vE '^declare -x _=' > mini_export
cat bash_export | grep -vE '^declare -x _=' > bash_export
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
./builtin.out export > mini_export
echo $?
printf "${CYAN}%s${RESET}\n" "export EXPORTTEST"
export EXPORTTEST
printf "${YELLOW}%s${RESET}\n" "[bash] export"
echo "export > bash_export" | bash
echo $?
echo "===diff check start==="
cat mini_export | grep -vE '^declare -x _=' > mini_export
cat bash_export | grep -vE '^declare -x _=' > bash_export
diff mini_export bash_export
echo "===diff check end==="
rm mini_export bash_export
echo

printf "${YELLOW}%s${RESET}\n" "[mini] export -z"
./builtin.out export -z
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] export -z"
echo "export -z" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] export \"\""
./builtin.out export ""
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] export \"\""
echo "export \"\"" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] export -"
./builtin.out export -
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] export -"
echo "export -" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] export ---"
./builtin.out export ---
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] export ---"
echo "export ---" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] export -- -z"
./builtin.out export -- -z
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] export -- -z"
echo "export -- -z" | bash
echo $?
echo

printf "${YELLOW}%s${RESET}\n" "[mini] export EXPORTTEST"
./builtin.out export EXPORTTEST > mini_export
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] export EXPORTTEST"
echo "export EXPORTTEST" | bash
echo $?
echo "export EXPORTTEST; export > bash_export" | bash
echo "===diff check start==="
cat mini_export | grep -vE '^declare -x _=' > mini_export
cat bash_export | grep -vE '^declare -x _=' > bash_export
diff mini_export bash_export
echo "===diff check end==="
rm mini_export bash_export
echo

printf "${YELLOW}%s${RESET}\n" "[mini] export EXPORTTEST="
./builtin.out export EXPORTTEST= > mini_export
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] export EXPORTTEST="
echo "export EXPORTTEST=" | bash
echo $?
echo "export EXPORTTEST= ; export > bash_export" | bash
echo "===diff check start==="
cat mini_export | grep -vE '^declare -x _=' > mini_export
cat bash_export | grep -vE '^declare -x _=' > bash_export
diff mini_export bash_export
echo "===diff check end==="
rm mini_export bash_export
echo

printf "${YELLOW}%s${RESET}\n" "[mini] export EXPORTTEST=0123"
./builtin.out export EXPORTTEST=0123 > mini_export
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] export EXPORTTEST=0123"
echo "export EXPORTTEST=0123" | bash
echo $?
echo "export EXPORTTEST=0123 ; export > bash_export" | bash
echo "===diff check start==="
cat mini_export | grep -vE '^declare -x _=' > mini_export
cat bash_export | grep -vE '^declare -x _=' > bash_export
diff mini_export bash_export
echo "===diff check end==="
rm mini_export bash_export
echo

printf "${YELLOW}%s${RESET}\n" "[mini] export EXPORTTEST=\"B=C\""
./builtin.out export EXPORTTEST="B=C" > mini_export
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
./builtin.out export "EXPORTTEST=B"=C > mini_export
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] export \"EXPORTTEST=B\"=C"
echo "export \"EXPORTTEST=B\"=C" | bash
echo $?
echo "export \"EXPORTTEST=B\"=C ; export > bash_export" | bash
echo "===diff check start==="
cat mini_export | grep -vE '^declare -x _=' > mini_export
cat bash_export | grep -vE '^declare -x _=' > bash_export
diff mini_export bash_export
echo "===diff check end==="
rm mini_export bash_export
echo

printf "${YELLOW}%s${RESET}\n" "[mini] export EXPORTTEST=\"aaa     b\""
./builtin.out export EXPORTTEST="aaa     b" > mini_export
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] export EXPORTTEST=\"aaa     b\""
echo "export EXPORTTEST=\"aaa     b\"" | bash
echo $?
echo "export EXPORTTEST=\"aaa     b\" ; export > bash_export" | bash
echo "===diff check start==="
cat mini_export | grep -vE '^declare -x _=' > mini_export
cat bash_export | grep -vE '^declare -x _=' > bash_export
diff mini_export bash_export
echo "===diff check end==="
rm mini_export bash_export
echo

printf "${YELLOW}%s${RESET}\n" "[mini] export EXPORTTEST==="
./builtin.out export EXPORTTEST=== > mini_export
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] export EXPORTTEST==="
echo "export EXPORTTEST===" | bash
echo $?
echo "export EXPORTTEST=== ; export > bash_export" | bash
echo "===diff check start==="
cat mini_export | grep -vE '^declare -x _=' > mini_export
cat bash_export | grep -vE '^declare -x _=' > bash_export
diff mini_export bash_export
echo "===diff check end==="
rm mini_export bash_export
echo

printf "${YELLOW}%s${RESET}\n" "[mini] export EXPORTTEST=\\\"hello\\\""
./builtin.out export EXPORTTEST=\"hello\" > mini_export
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] export EXPORTTEST=\\\"hello\\\""
echo "export EXPORTTEST=\\\"hello\\\"" | bash
echo $?
echo "export EXPORTTEST=\\\"hello\\\" ; export > bash_export" | bash
echo "===diff check start==="
cat mini_export | grep -vE '^declare -x _=' > mini_export
cat bash_export | grep -vE '^declare -x _=' > bash_export
diff mini_export bash_export
echo "===diff check end==="
rm mini_export bash_export
echo

printf "${YELLOW}%s${RESET}\n" "[mini] export EXPORTTEST=\$hello"
./builtin.out export EXPORTTEST=\$hello > mini_export
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] export EXPORTTEST=\$hello"
echo "export EXPORTTEST=\\\$hello" | bash
echo $?
echo "export EXPORTTEST=\\\$hello ; export > bash_export" | bash
echo "===diff check start==="
cat mini_export | grep -vE '^declare -x _=' > mini_export
cat bash_export | grep -vE '^declare -x _=' > bash_export
diff mini_export bash_export
echo "===diff check end==="
rm mini_export bash_export
echo

printf "${YELLOW}%s${RESET}\n" "[mini] export EXPORTTEST=\\hello"
./builtin.out export EXPORTTEST=\\hello > mini_export
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] export EXPORTTEST=\\hello"
echo "export EXPORTTEST=\\\\hello" | bash
echo $?
echo "export EXPORTTEST=\\\\hello ; export > bash_export" | bash
echo "===diff check start==="
cat mini_export | grep -vE '^declare -x _=' > mini_export
cat bash_export | grep -vE '^declare -x _=' > bash_export
diff mini_export bash_export
echo "===diff check end==="
rm mini_export bash_export
echo

printf "${YELLOW}%s${RESET}\n" "[mini] export EXPORTTEST=\`hello"
./builtin.out export EXPORTTEST=\`hello > mini_export
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] export EXPORTTEST=\`hello"
echo "export EXPORTTEST=\\\`hello" | bash
echo $?
echo "export EXPORTTEST=\\\`hello ; export > bash_export" | bash
echo "===diff check start==="
cat mini_export | grep -vE '^declare -x _=' > mini_export
cat bash_export | grep -vE '^declare -x _=' > bash_export
diff mini_export bash_export
echo "===diff check end==="
rm mini_export bash_export
echo

printf "${YELLOW}%s${RESET}\n" "[mini] export EXPORTTEST=\" hello\""
./builtin.out export EXPORTTEST=" hello" > mini_export
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] export EXPORTTEST=\" hello\""
echo "export EXPORTTEST=\" hello\"" | bash
echo $?
echo "export EXPORTTEST=\" hello\" ; export > bash_export" | bash
echo "===diff check start==="
cat mini_export | grep -vE '^declare -x _=' > mini_export
cat bash_export | grep -vE '^declare -x _=' > bash_export
diff mini_export bash_export
echo "===diff check end==="
rm mini_export bash_export
echo

printf "${YELLOW}%s${RESET}\n" "[mini] export EXPORTTEST= 0123"
./builtin.out export EXPORTTEST= 0123 > mini_export
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] export EXPORTTEST= 0123"
echo "export EXPORTTEST= 0123" | bash
echo $?
echo

# $mark
printf "${YELLOW}%s${RESET}\n" "[mini] export EXPORTTEST$=0123"
./builtin.out export EXPORTTEST$=0123
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] export EXPORTTEST$=0123"
echo "export EXPORTTEST$=0123" | bash
echo $?
rm mini_export bash_export
echo

# 先頭に数字
printf "${YELLOW}%s${RESET}\n" "[mini] export 0EXPORTTEST=0123"
./builtin.out export 0EXPORTTEST=0123
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] export 0EXPORTTEST=0123"
echo "export 0EXPORTTEST=0123" | bash
echo $?
rm mini_export bash_export
echo

# 途中に数字
printf "${YELLOW}%s${RESET}\n" "[mini] export EXP0RT0TEST=0123"
./builtin.out export EXPORT0TEST=0123 > mini_export
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] export EXPORT0TEST=0123"
echo "export EXPORT0TEST=0123" | bash
echo $?
echo "export EXPORT0TEST=0123 ; export> bash_export" | bash
echo "===diff check start==="
cat mini_export | grep -vE '^declare -x _=' > mini_export
cat bash_export | grep -vE '^declare -x _=' > bash_export
diff mini_export bash_export
echo "===diff check end==="
rm mini_export bash_export
echo

# 最後に数字
printf "${YELLOW}%s${RESET}\n" "[mini] export EXP0RTTEST0=0123"
./builtin.out export EXPORTTEST0=0123 > mini_export
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] export 0EXPORTTEST0=0123"
echo "export EXPORTTEST0=0123" | bash
echo $?
echo "export EXPORTTEST0=0123 ; export > bash_export" | bash
echo "===diff check start==="
cat mini_export | grep -vE '^declare -x _=' > mini_export
cat bash_export | grep -vE '^declare -x _=' > bash_export
diff mini_export bash_export
echo "===diff check end==="
rm mini_export bash_export
echo

# _ (under score)
printf "${YELLOW}%s${RESET}\n" "[mini] export _A=0123"
./builtin.out export _A=0123 > mini_export
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] export _A=0123"
echo "export _A=0123" | bash
echo $?
echo "export _A=0123 ; export > bash_export" | bash
echo "===diff check start==="
cat mini_export | grep -vE '^declare -x _=' > mini_export
cat bash_export | grep -vE '^declare -x _=' > bash_export
diff mini_export bash_export
echo "===diff check end==="
rm mini_export bash_export
echo

# OLDPWDにexportで値を設定
printf "${YELLOW}%s${RESET}\n" "[mini] export OLDPWD=override_oldpwd"
./builtin.out export OLDPWD=override_oldpwd > mini_export
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] export OLDPWD=override_oldpwd"
echo "export OLDPWD=override_oldpwd" | bash
echo $?
echo "export OLDPWD=override_oldpwd ; export > bash_export" | bash
echo "===diff check start==="
cat mini_export | grep -vE '^declare -x _=' > mini_export
cat bash_export | grep -vE '^declare -x _=' > bash_export
diff mini_export bash_export
echo "===diff check end==="
rm mini_export bash_export
echo

# PWDがunsetされた状態でminishell起動
printf "${CYAN}%s${RESET}\n" "unset PWD"
unset PWD
printf "${YELLOW}%s${RESET}\n" "[mini] export"
./builtin.out export > mini_export
echo $?
printf "${CYAN}%s${RESET}\n" "unset PWD"
unset PWD
printf "${YELLOW}%s${RESET}\n" "[bash] export"
echo "export > bash_export" | bash
echo $?
echo "===diff check start==="
cat mini_export | grep -vE '^declare -x _=' > mini_export
cat bash_export | grep -vE '^declare -x _=' > bash_export
diff mini_export bash_export
echo "===diff check end==="
rm mini_export bash_export
echo

# 既存の環境変数をnameのみで上書きしようとする -> 何もしない
printf "${YELLOW}%s${RESET}\n" "[mini] export HOME"
./builtin.out export HOME > mini_export
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] export HOME"
echo "export HOME ; export > bash_export" | bash
echo $?
echo "===diff check start==="
cat mini_export | grep -vE '^declare -x _=' > mini_export
cat bash_export | grep -vE '^declare -x _=' > bash_export
diff mini_export bash_export
echo "===diff check end==="
rm mini_export bash_export
echo

# 既存の環境変数をnameのみで上書きしようとする -> 何もしない & 正常ケース
printf "${YELLOW}%s${RESET}\n" "[mini] export HOME EXPORTTEST=0123"
./builtin.out export HOME EXPORTTEST=0123 > mini_export
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] export HOME EXPORTTEST=0123"
echo "export HOME EXPORTTEST=0123" | bash
echo $?
echo "export HOME EXPORTTEST=0123" | bash
echo

# 複数ダブルクォート
printf "${YELLOW}%s${RESET}\n" "[mini] export EXPORTTEST=\"echo \"\$USER\"\""
./builtin.out export EXPORTTEST="echo "$USER"" > mini_export
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] export EXPORTTEST=\"echo \"\$USER\"\""
echo "export EXPORTTEST=\"echo \"\$USER\"\"" | bash
echo $?
echo "export EXPORTTEST=\"echo \"\$USER\"\" ; export > bash_export" | bash
echo "===diff check start==="
cat mini_export | grep -vE '^declare -x _=' > mini_export
cat bash_export | grep -vE '^declare -x _=' > bash_export
diff mini_export bash_export
echo "===diff check end==="
rm mini_export bash_export
echo

# += new
printf "${YELLOW}%s${RESET}\n" "[mini] export EXPORTTEST+=012"
./builtin.out export EXPORTTEST+=012 > mini_export
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] export EXPORTTEST+=012"
echo "export EXPORTTEST+=012" | bash
echo $?
echo "export EXPORTTEST+=012 ; export > bash_export" | bash
echo "===diff check start==="
cat mini_export | grep -vE '^declare -x _=' > mini_export
cat bash_export | grep -vE '^declare -x _=' > bash_export
diff mini_export bash_export
echo "===diff check end==="
rm mini_export bash_export
echo

# = new, += join
printf "${YELLOW}%s${RESET}\n" "[mini] export EXPORTTEST=012 EXPORTTEST+=34"
./builtin.out export EXPORTTEST=012 EXPORTTEST+=34 > mini_export
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] export EXPORTTEST=012 EXPORTTEST+=34"
echo "export EXPORTTEST=012 EXPORTTEST+=34" | bash
echo $?
echo "export EXPORTTEST=012 ; EXPORTTEST+=34 ; export > bash_export" | bash
echo "===diff check start==="
cat mini_export | grep -vE '^declare -x _=' > mini_export
cat bash_export | grep -vE '^declare -x _=' > bash_export
diff mini_export bash_export
echo "===diff check end==="
rm mini_export bash_export
echo

#  += new, += join, += join
printf "${YELLOW}%s${RESET}\n" "[mini] export EXPORTTEST+=012 EXPORTTEST+=34 EXPORTTEST+=abc"
./builtin.out export EXPORTTEST+=012 EXPORTTEST+=34 EXPORTTEST+=abc > mini_export
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] export EXPORTTEST+=012 EXPORTTEST+=34 EXPORTTEST+=abc"
echo "export EXPORTTEST+=012 EXPORTTEST+=34 EXPORTTEST+=abc" | bash
echo $?
echo "export EXPORTTEST+=012 ; EXPORTTEST+=34 ; EXPORTTEST+=abc ; export > bash_export" | bash
echo "===diff check start==="
cat mini_export | grep -vE '^declare -x _=' > mini_export
cat bash_export | grep -vE '^declare -x _=' > bash_export
diff mini_export bash_export
echo "===diff check end==="
rm mini_export bash_export
echo

# += new (no value)
printf "${YELLOW}%s${RESET}\n" "[mini] export EXPORTTEST+="
./builtin.out export EXPORTTEST+= > mini_export
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] export EXPORTTEST+="
echo "export EXPORTTEST+=" | bash
echo $?
echo "export EXPORTTEST+= ; export > bash_export" | bash
echo "===diff check start==="
cat mini_export | grep -vE '^declare -x _=' > mini_export
cat bash_export | grep -vE '^declare -x _=' > bash_export
diff mini_export bash_export
echo "===diff check end==="
rm mini_export bash_export
echo

# _+=
printf "${YELLOW}%s${RESET}\n" "[mini] export _+="
./builtin.out export _+= > mini_export
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] export _+="
echo "export _+=" | bash
echo $?
echo "export _+= ; export > bash_export" | bash
echo "===diff check start==="
cat mini_export | grep -vE '^declare -x _=' > mini_export
cat bash_export | grep -vE '^declare -x _=' > bash_export
diff mini_export bash_export
echo "===diff check end==="
rm mini_export bash_export
echo

# __+=
printf "${YELLOW}%s${RESET}\n" "[mini] export __+="
./builtin.out export __+= > mini_export
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] export __+="
echo "export __+=" | bash
echo $?
echo "export __+= ; export > bash_export" | bash
echo "===diff check start==="
cat mini_export | grep -vE '^declare -x _=' > mini_export
cat bash_export | grep -vE '^declare -x _=' > bash_export
diff mini_export bash_export
echo "===diff check end==="
rm mini_export bash_export
echo

# _+
printf "${YELLOW}%s${RESET}\n" "[mini] export _+"
./builtin.out export _+ > mini_export
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] export _+"
echo "export _+" | bash
echo $?
echo

# __+
printf "${YELLOW}%s${RESET}\n" "[mini] export __+"
./builtin.out export __+ > mini_export
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] export __+"
echo "export __+" | bash
echo $?
echo

# unset SHLVL; export;
MYSHLVL=$SHLVL
printf "${CYAN}%s${RESET}\n" "unset SHLVL"
unset SHLVL
printf "${YELLOW}%s${RESET}\n" "[mini] export"
./builtin.out export > mini_export
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] export"
echo "export > bash_export" | bash
echo $?
echo "===diff check start==="
cat mini_export | grep -vE '^declare -x _=' > mini_export
cat bash_export | grep -vE '^declare -x _=' > bash_export
diff mini_export bash_export
echo "===diff check end==="
rm mini_export bash_export
export SHLVL=$MYSHLVL
echo

# export SHLVL=-1; export;
MYSHLVL=$SHLVL
printf "${CYAN}%s${RESET}\n" "export SHLVL=-1"
export SHLVL=-1
printf "${YELLOW}%s${RESET}\n" "[mini] export"
./builtin.out export > mini_export
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] export"
echo "export > bash_export" | bash
echo $?
rm mini_export bash_export
export SHLVL=$MYSHLVL
echo

# export SHLVL=999; export;
MYSHLVL=$SHLVL
printf "${CYAN}%s${RESET}\n" "export SHLVL=999"
export SHLVL=999
printf "${YELLOW}%s${RESET}\n" "[mini] export"
./builtin.out export > mini_export
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] export"
echo "export > bash_export" | bash
echo $?
rm mini_export bash_export
export SHLVL=$MYSHLVL
echo

# export SHLVL=1000; export;
MYSHLVL=$SHLVL
printf "${CYAN}%s${RESET}\n" "export SHLVL=1000"
export SHLVL=1000
printf "${YELLOW}%s${RESET}\n" "[mini] export"
./builtin.out export > mini_export
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] export"
echo "export > bash_export" | bash
echo $?
rm mini_export bash_export
export SHLVL=$MYSHLVL
echo

# export SHLVL=a; export;
MYSHLVL=$SHLVL
printf "${CYAN}%s${RESET}\n" "export SHLVL=a"
export SHLVL=a
printf "${YELLOW}%s${RESET}\n" "[mini] export"
./builtin.out export > mini_export
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] export"
echo "export > bash_export" | bash
echo $?
rm mini_export bash_export
export SHLVL=$MYSHLVL
echo

# export SHLVL=2147483646; export;
MYSHLVL=$SHLVL
printf "${CYAN}%s${RESET}\n" "export SHLVL=2147483646"
export SHLVL=2147483646
printf "${YELLOW}%s${RESET}\n" "[mini] export"
./builtin.out export > mini_export
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] export"
echo "export > bash_export" | bash
echo $?
rm mini_export bash_export
export SHLVL=$MYSHLVL
echo

# export SHLVL=2147483647; export;
MYSHLVL=$SHLVL
printf "${CYAN}%s${RESET}\n" "export SHLVL=2147483647"
export SHLVL=2147483647
printf "${YELLOW}%s${RESET}\n" "[mini] export"
./builtin.out export > mini_export
echo $?
printf "${YELLOW}%s${RESET}\n" "[bash] export"
echo "export > bash_export" | bash
echo $?
rm mini_export bash_export
export SHLVL=$MYSHLVL
echo
