< nonexistingfile cat | ls \> outfiule

This should still execute `ls` and write into `outfile` regardless of that `cat` failed to execute.

< big_text/txt cat | head -2 > outfile

This (I believe) overwrites the buffer of the pipe and therefore doesn't close properly anymore leaving the "head -2" command with an open fd thereby never ending the process. 
