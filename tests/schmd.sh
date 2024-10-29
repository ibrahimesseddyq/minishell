# **************************************************************************** #
#                                     SCMD                                     #
# **************************************************************************** #

ls ok

cat cmds.sh ok

/bin/echo test1 ok

"" ok

touch "" ok

touch "  " ok
/bin/rm -f "  "


touch " ok
"
/bin/rm -f "
"

mkdir " " ok 
/bin/rm -rf " "

asd ok
expr $? + $?

expr 21 + 21 ok

"ls" ok

"cat cmds.sh" ok

"/bin/echo" test1 ok

'/bin/echo test1' ok

awk '$1 ~ /^d/ {print $9}' ok

awk 'BEGIN{for(i=1;i<=10;i++){for(j=1;j<=10;j++){printf("%4d ",i*j)} printf("\n")}}' /dev/null | tail -n 10 ok

awk 'BEGIN{for(i=1;i<=1000000;i++)print int(i)}' | awk '{sum+=$1} END {print sum/NR}' ok

asd ok
echo asd
echo $?

asd ok
pwd
echo $?

asd ok
unset USER
asd
pwd

asd ok
pwd
asd
echo asd
echo $?

asd ok
cd ..
echo $?

asd ok
unset PATH
echo $?

touch whatever ok
cat <"./whatever" >"./whatever"
rm -rf whatever

ls >"./ with spaces" ok
rm -rf " with spaces"

# **************************************************************************** #
#                                  BROKEN SCMD                                 #
# **************************************************************************** #

"." ok

.ls ok

./ls ok 

"./"ls ok

"./""ls" ok

"./"''"ls" ok

3123 ok

lsa ok

/ls ok

EechoE ok

/ls/ ok

/bin/ ok

/bin/cats ok

./4242424242.sh ok

rm -f something ok

| echo -n oui ok

| | | ok


ALL TESTS Are OKAY