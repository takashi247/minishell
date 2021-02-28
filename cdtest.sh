#!/bin/sh

make ../libft
make clean ../libft
gcc -Wall -Wextra -Werror -I./includes -I./libft srcs/cd.c srcs/command_utils.c -Llibft -lft -D CDTEST -o cd.out
echo "\x1b[33m./cd.out\x1b[0m"
./cd.out

echo "\x1b[33m./cd.out cd\x1b[0m"
./cd.out cd

echo "\x1b[33m./cd.out cd ~\x1b[0m"
./cd.out cd ~

echo "\x1b[33m./cd.out cd \$HOME\x1b[0m"
./cd.out cd $HOME

echo "\x1b[33m./cd.out cd hoge\x1b[0m"
./cd.out cd hoge

echo "\x1b[33m./cd.out mkdir test\x1b[0m"
./cd.out mkdir test
echo "\x1b[33m./cd.out cd test\x1b[0m"
./cd.out cd test

echo "\x1b[33m./cd.out cd hoge world\x1b[0m"
./cd.out cd hoge world
