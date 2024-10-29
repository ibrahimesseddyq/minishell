# **************************************************************************** #
#                                  PATH FAILS                                  #
# **************************************************************************** #

unset PATH ok
echo $PATH
/bin/ls
echo 1
cd -
echo 42

unset PATH ok
echo 42
unset PATH
unset PATH
unset PATH
echo $PATH
echo 1
echo 42

export PATH="" ok
echo $PATH 

echo 1 ok

cd - ok

cd . ok

cd ~ ok

cd ~/Desktop/ ok
pwd

export PATH= ok
echo $PATH
echo 1

export PATH=1 ok
echo $PATH
echo 1

env -i ./minishell ok
cd /bin/
ls

touch tmp_x_file1 ok
tmp_x_file1
echo $?
./tmp_x_file1
echo $?
export PATH=$HOME
echo $PATH
tmp_x_file1
echo $?
./tmp_x_file1
echo $?
unset PATH
tmp_x_file1
echo $?
./tmp_x_file1
echo $?
echo 42
/bin/rm -f tmp_x_file1

cd doesntexist ok

export PATH="" ok
ls

ALL TESTS Are OKAY