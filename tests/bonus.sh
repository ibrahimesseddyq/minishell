/bin/echo 1 && /bin/echo 2 ok
cat file_does_not_exist && /bin/echo 2 ok

/bin/echo 1 || /bin/echo 2 ok
cat file_does_not_exist || /bin/echo 2 ok

/bin/echo 1 && /bin/echo 2 && /bin/echo 3 ok
/bin/echo 1 || /bin/echo 2 || /bin/echo 3 ok

### PIPELINES AFTER OPERATORS ###
/bin/echo 1 && /bin/echo 2 | /bin/echo 3 ok
/bin/echo 1 || /bin/echo 2 | /bin/echo 3 ok

/bin/echo 1 && cat file_does_not_exist | /bin/echo 3 ok
/bin/echo 1 && /bin/echo 3 | cat file_does_not_exist ok
/bin/echo 1 || cat file_does_not_exist | /bin/echo 3 ok
/bin/echo 1 || /bin/echo 2 | cat file_does_not_exist ok
cat file_does_not_exist && /bin/echo 2 | /bin/echo 3 ok
cat file_does_not_exist || /bin/echo 2 | /bin/echo 3 ok

### PIPELINES BEFORE OPERATOR ###
/bin/echo 1 | /bin/echo 2 && /bin/echo 3 ok
/bin/echo 1 | /bin/echo 2 || /bin/echo 3 ok

/bin/echo 1 | cat file_does_not_exist && /bin/echo 3 ok
/bin/echo 1 | cat file_does_not_exist || /bin/echo 3 ok
cat file_does_not_exist | /bin/echo 2 && /bin/echo 3 ok
cat file_does_not_exist | /bin/echo 2 || /bin/echo 3 ok
/bin/echo 1 | /bin/echo 2 && cat file_does_not_exist ok
/bin/echo 1 | /bin/echo 2 || cat file_does_not_exist ok

### PIPELINES BEFORE AND AFTER OPERATOR ###
/bin/echo 1 | /bin/echo 2 && /bin/echo 3 | /bin/echo 4 ok
/bin/echo 1 | /bin/echo 2 || /bin/echo 3 | /bin/echo 4 ok

/bin/echo 1 | /bin/echo 2 | /bin/echo 3 && /bin/echo 4 | /bin/echo 5 ok
/bin/echo 1 | /bin/echo 2 | /bin/echo 3 || /bin/echo 4 | /bin/echo 5 ok




/usr/bin/printf "%s\n" * | sort ok

export ARG="*" ok
/usr/bin/printf "%s\n" $ARG | sort

ls * ok
ls 'test'* ok
ls "test"* ok

touch "*1"
/usr/bin/printf "%s\n" "*"* | sort
rm "*1"

touch "   "
ls * | grep "   "
rm "   "

touch "a" "aa"
/usr/bin/printf "%s\n" *a | sort
rm "a" "aa"

touch "a" "aa" "aaa"
/usr/bin/printf "%s\n" *a*a | sort
rm "a" "aa" "aaa"

/usr/bin/printf "%s\n" "Mak"'e'*'*' | sort

/usr/bin/printf "%s\n" "Mak"'e'** | sort

/usr/bin/printf "%s\n" ***"Mak"'e'** | sort

/usr/bin/printf "%s\n" "."* | sort

/usr/bin/printf "%s\n" *"." | sort

/usr/bin/printf "%s\n" *"."* | sort

/usr/bin/printf "%s\n" "*" | sort

/usr/bin/printf "%s\n" '*' | sort

/usr/bin/printf "%s\n" Minishe*l | sort

/usr/bin/printf "%s\n" minishe*l | sort

touch minishelxxxl
/usr/bin/printf "%s\n" minishe*l | sort
/usr/bin/printf "%s\n" minishel*l | sort
/usr/bin/printf "%s\n" minishelxxx*l | sort
/usr/bin/printf "%s\n" minishel*xxx*l | sort
rm minishelxxxl

touch tmp_out
/bin/echo 42 >tmp_o*t*
rm -f "tmp_out*"

touch tmp_out1
touch tmp_out2
/bin/echo 42 >tmp_out*
rm -f "tmp_out*"

export test=" * "
touch "$USER * ?eHallo"
/bin/echo "$USER "*" ?e"*
rm -f "$USER * ?eHallo"



### Surprise
echo "'$HOME'"
echo '"$HOME"'


/bin/echo 1 && /bin/echo 2 ||

/bin/echo 1 && /bin/echo 2 |

/bin/echo 1 && /bin/echo 2 &&

()

(/bin/echo 1

/bin/echo 1)

(/bin/echo 1))

(/bin/echo 1) (/bin/echo 2)

()

(echo) hi

(echo) (hi)

(echo hi && ((echo hi && (echo hi) && echo hi)))


echo 42 < in | wc -l && ( /bin/echo 1 2 3 4 > tmp_out || /bin/echo 2 > tmp_out >> tmp_out tmp_out )
rm -f tmp_out

grep 42 < in | wc -l && ( /bin/echo 1 2 3 4 > tmp_out || /bin/echo 2 > tmp_out >> tmp_out tmp_out )
rm -f tmp_out

(echo 1 && echo 2) | (grep 1 && grep 2)

(printf "Hello\nWorld\n") | (/usr/bin/read -n 3 && cat)

(echo 1 && echo 2) | (/usr/bin/read -n 1 && grep 2)

(echo 1 && echo 2) | (/usr/bin/read -n 1 && grep 1)

/bin/echo 42 | /bin/echo 42 || (/bin/echo 42)

/bin/echo 42 | /bin/echo 42 && (/bin/echo 42)

export bla='||' || echo 42 && echo 43

export or='||' && export and='&&' && echo 42 $and echo 43 $or echo 43


