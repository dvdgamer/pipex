To give the system stack trace I use the command:
``` strace -e trace=open,openat,write,fork,vfork,clone,pipe2,close,dup2,execve,execvp -f -o trace.log bash -c './pipex "infile" "cat" "grep h" "outfile"' | awk '{pid=$1; if(!(pid in color)) {c=30+((++i)%7); color[pid]=c} printf "\033[%sm%s\033[0m %s\n", color[pid], pid, substr($0,index($0,$2))}' trace.log | grep -E "outfile|infile|pipe|dup|clone|fork|execve" ```

