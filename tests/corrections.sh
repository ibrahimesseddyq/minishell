# **************************************************************************** #
#                                  CORRECTION                                  #
# **************************************************************************** #

/bin/echo ok
/bin/echo 1 ok
/bin/cat 42 ok

"" ok

"   " ok

"    " ok

"		" ok 

"			" ok

/bin/echo hello 42 ok

/bin/sleep 0 ok

/bin/echo -n 1 ok

echo ok

echo hello world ok

echo -n 42 ok

echo -n 42 -n ok

echo 42 -n ok

echo -n -n -n 42 ok

echo -n -n -n -n 42 ok

exit ok

exit 42 ok

exit "" ok

exit 1 2 3 ok

exit 42 42 ok

exit A ok

exit A 1 ok

exit 1 A

/bin/echo 42 ok
echo $?

/bin/cat 42 ok
echo $?

/bin/exe42 42 ok

42 42 ok

/bin/echo 42 ok
expr $? + $?

/bin/cat 42 ok
expr $? + $?

echo "Hello World" ok

echo "  ""Hello World" ok

echo "  "Hello "World " ok

"echo" 42 ok

"echo 42" ok

echo " cat ' lol.c" ok

/bin/echo @World"42"Hello ok

echo 'Hello World' ok

echo '  ' Hello World ok

echo '  'Hello 'World ' ok

'echo' 42 ok

'e'cho 42 ok

echo 'cat lol.c << cat > lol.c' ok

echo @World'42'Hello ok

echo "" '' ok

echo """"''""''"" ok 

echo " "" " ' ' " " ' ' " " ok

echo 1 '|' echo 2 ok

echo 1 '&&' echo 2 ok 

echo 1 '||' echo 2 ok

echo 1 '>' echo 2 ok

echo 1 '>>' file 2 ok

'<<' lim echo 1 >>/dev/null ok

echo "$USER" ok

echo "   $   " ok

echo '$USER' ok

echo '   $   ' ok

echo "$HO ME" ok

echo '$HO ME' ok

echo $"HOME" ok

echo $'HOME' ok

echo ""$PWD"" ok

echo ''$PWD'' ok

echo $USE"R"$HOME ok

echo $"HOME"$USER ok 

echo $"HOM"E$USER ok

echo $"'HOM'E"$USER ok

echo $'HOM'E$USER ok

echo $"HOME" ok

echo $'HOME' ok

echo $ ok

echo "$" ok

echo '$=' ok 

echo "$""$" ok

echo $"$" ok

echo $"42$" ok

echo "$"$ ok

echo $'$' ok

echo '$'$

env | grep HOME ok

env | grep $USER ok

export USER= ok
env | grep USER

export USER="@?/" ok
env | grep USER 

export NEW="4 2" ok
env | grep NEW

export NEW="4=2" ok
env | grep NEW

export NEW=4=2 ok
env | grep 4=2

export = ok

export ''='' ok

export ""="" ok 

export export ok 

export =============123 ok 

export echo ok

unset ok

unset env ok

unset PATH ok
echo $PATH
unset PATH
echo $PATH
unset HOME
echo $HOME

export NEW=42 ok
env | grep NEW
unset NEW
env | grep NEW
unset NEW
unset NEW
unset NEW
unset NEW
unset NEW
env | grep NEW

cd . ok
/bin/ls

cd .. ok
/bin/ls

cd /notsuchdir ok
/bin/ls

cd ///// ok
/bin/ls

cd "cmds/" ok
/bin/ls

cd cmds/ ok
/bin/ls

cd ./cmds/ ok
/bin/ls

mkdir bla_test ok
chmod -wrx bla_test
cd bla_test
chmod +wrx bla_test
rm -r bla_test

pwd ok

cd $HOME ok
pwd

pwd pwd ok

pwd hello ok

unset PATH ok
pwd

unset PATH ok
cd /bin
ls

unset PATH ok
cd /bin/../bin/
ls

unset PATH ok
cd /bin/../bin/../bin/../bin/../bin/../bin/../bin/../bin/
../bin/../bin/ls

unset PATH ok
cd /bin/
sleep 2

mkdir tmp_path_test1 tmp_path_test2 ok
printf '#include <unistd.h>\nint main(){write(1, \"1\\n\", 2);}' > tmp_path_test1/test1.c
gcc tmp_path_test1/test1.c -o tmp_path_test1/a.out
printf '#include <unistd.h>\nint main(){write(1, \"2\\n\", 2);}' > tmp_path_test2/test2.c
gcc tmp_path_test2/test2.c -o tmp_path_test2/a.out
export PATH=tmp_path_test1:tmp_path_test2
a.out
export PATH=tmp_path_test2:tmp_path_test1
a.out
/bin/rm -rf tmp_path_test1 tmp_path_test2

ALL IS OKAY

