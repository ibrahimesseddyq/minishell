# **************************************************************************** #
#                                PARSING HELL                                  #
# **************************************************************************** #

">>" asd ok

>">" asd ok 
/bin/rm -f ">"

>> '$USER' ok
cat $USER
/bin/rm -f '$USER'

>> '$USER' ok
cat '$USER'
/bin/rm -f '$USER'

"echo " ok

"echo -nnnnn" ok

"ECho" -n -nnn"" "-"nnnnn ok

"ECHO" "-n" ok

ECHO '''''-''n' ok

echo '' -n ok

echo "" "" "" -n -n -n -n ok

cat << $USER ok
why
not
$USER

export T=">>" ok
$T lol

cat << "$USER" ok
why
not
$USER

cat << "$US"E"R" ok
because
we
love
bash
$USER

>> $HOME ok

>> "$H"OM"E" ok
cat OME
/bin/rm -f OME

>> "$USER'$USER'" ok
cat "$USER'$USER'"
/bin/rm -f "$USER'$USER'"

>> "$USER" ok
cat $USER
/bin/rm -f $USER

cd $HOME/Desktop/ ok
pwd

cd "$HOME"/Desktop/ ok
pwd

cd "$H"O"ME"/Desktop/ ok
echo $?

export T=n ok
echo "-"$T$T

export T=ech ok
echo $To

export T=ech ok
echo $T"o"

export T=ech ok
echo $T"o "

export T=ech ok
echo $T"o -n"

export T=ech ok
echo $T"o -n"

export T=ech ok
echo $T'o'

export T="-n test1 -n test 2" ok
echo $T

export T=ech ok
echo $T'o '

"ECHO" ok

'echo' ok

'PWD' ok

"PWD" ok

echo "-nnnnn " ok

ECHO -nn ok

ECHO -n -n ok

ECHO "-"""n""n""n""n""n""nnnnnn-n ok

ECHO "-"""n""n""n""n""n""nnnnnn -n ok

export T=nnnnnnnn
echo "-""$T"nnnnnnnnnnnnn -nnnnnnnn"$T" '-'"$T" ok

export T=nnnnnnnn
echo "-""$T"nnnnnnnnnnnnn -nnnnnnnn"$T" '-''$T' ok

export T=nnnnnnnn
echo "-"'$T'nnnnnnnnnnnnn -nnnnnnnn'$T' '-'"$T " ok

export T=nnnnnnnn
echo "-"'$T'nnnnnnnnnnnnn -nnnnnnnn$T '-''$T ' ok

export T=e E=c S=h L=o ok
$T$E$S$L

export T=e E=c S=h L=o L=ok ok 
$T$E$S$L

export T=e E=c S=h L=o ok
$T$E$S$L -n

export T=E E=c S=h L=o ok
$T$E$S$L -n

export T=E E=c S=h L=o ok
$T$E$S$L -nn

export T=e E=c S=h L=o ok
$T$E$S$L -nn

export T=e E=c S=h L=o ok
$T$E"c"$L -nn

export T=e E=c S=h L=o ok
$T$E"C"$L -nn

export T=e E=c S=h L=o ok
$T$E"C"$L "" -""n

$NOVAR ok

export T="s" ok
l$T

export T="s" ok
l$T -a

export T="l" ok
$Ts

export T="l" ok
$Ts -a

LS ok

Ls ok

lS ok

ls ok

PWD ok

pWD ok

pwd ok

pwD ok

ENV ok

CAT ok

EXPORT ok

export T="|" ok
echo segfault $T grep segfault

export T='|' ok
echo segfault $T grep segfault

export T=">" ok
echo segfault $T grep segfault 

export T='<'
echo segfault $T grep segfault

export T="<<"
echo segfault $T grep segfault

export T='<<'
echo segfault $T grep segfault

export T="|"
$T$T$T$T$T$T$T

export T="echo segfault | grep segfault"
$T

export T=-nnnnnnnn"nnnnnnn "
echo $T

export T=-"n                    "
Echo $T

EXIT 123

Exit

UNSET USER

Unset USER

EXPORT T=LA
echo $T

Export T=LA
echo $T

"e"'x''p''o''r''t' L=T
echo $T

e""""""""""""cho

export T='|'
echo $T echo lala $T echo $T echo ?

export T="<<"
$T.

OLDPWD

USER

" ls"

" cat"

" echo"

" PWD"

" pwd"

"PWD "

"pwd "

'pwd '

p""''''w''''''""""""''''''''''''''''''''''''''''''''d

'''''''''''''''' echo ok

           ''echo ok

           ""echo ok

           ""echo"" ok

           ""'echo'"" ok

echo "         |       "  | echo maybe ok

echo "|"  | echo maybe ok

echo '|'  | echo maybe ok

echo -nnnnnnnnnnnn ok

export L=amazing L=ok L=cool ok
echo $L

export L=amazing L=ok L=cool ok
export L=ok
echo $L

echo '$'$'$'$'$' ok

echo '$'$'$'$'$'$'$' ok

echo "$"$'$'$"$"$"$"$'$' ok

echo $/ $/ ok

echo $U/SER ok

echo "$/ $/" ok

echo $/"$/" ok

echo '$/' ok

exit 9223372036854775805 ok

exit 123"123" ok

<| echo ok ok

>| echo sure ok

cd -- ok


ALL is OKAYYY