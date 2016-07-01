# 42sh
A unix shell.  

42sh run like other basic shells like sh or csh.  
It includes the following builtins :  
exit.  
cd [-LP].  
echo.  
history [-cdanrwps].  
read [-r].  
export [-p].  
set.  
unset.  
setenv.  
unsetenv.  

It also includes several functionalities :  
  
The semicolon and conditons :  
>% mkdir repertory ; cd repertory ; pwd  
>/.../repertory  
>% test 10 -gt 2 && echo TRUE ; test 2 -gt 10 || echo FALSE  
>TRUE  
>FALSE  

The pipe :  
>% echo test | tr e E | cat -e  
>tEst$  

The redirection :  
>% echo A > file ; echo B >> file ; cat < file  
>A  
>B  

The heredoc :  
>% cat << eof  
>>test  
>>eof  

>test  

The file descriptors :  
>% touch foo ; touch bar ; rm foo ; ls foo bar 2>&-  
>bar  
>% touch foo ; touch bar ; rm foo ; ls foo bar 2>&1 | cat -e  
>ls: foo: No such file or directory$  
>bar$  
>% echo TEST 6>file 1>&6 ; cat 8<file 0<&8  
>TEST  

The globing :  
>% touch a2 aa2 aa1 bb1 b2 cc2 ; echo [ab]?[2]  
>aa2  
>% touch a2 aa2 aa1 bb1 b2 cc2 ; echo \*a\*  
>aa2 a2 aa1  

The subshell :  
>% (echo A ; echo B ; echo C) | cat -e  
>A$  
>B$  
>C$  

The backquotes :  
>% \`echo touch file\` ; ls -l file  
-rw-r--r--  1 mdugot  2015_paris  0 Jul  1 14:01 file  

The quotes and backslash :  
>% echo "';'" ; echo '"|"' ; echo \\*  
>';'  
>"|"  
>\*  

The exclamation mark :  
>%echo 2  
>%echo 1  
>%!e  
>echo 1  
>1  
>%!-2  
>echo 2  
>2  

And a line editor with keyboard shortcut :  
LEFT-RIGHT :  move the cursor.  
UP-DOWN : can browse through the history.  
TAB : autocompletion.  
Ctrl-b : go one world back.  
Ctrl-n : go to the next world.  
Ctrl-l : go down to the next line.  
Ctrl-k : go up to the previous line.  




