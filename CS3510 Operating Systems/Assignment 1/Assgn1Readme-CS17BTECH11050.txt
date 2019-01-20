About

The file `time.c` calculates the time taken by a shell command to run(in SECONDS).
Author: SHRAIYSH VAISHAY - CS17BTECH11050

========================================

Running instructions: 

1. Once the files are extracted in a directory, the file time.c can be compiled by running 
	$ gcc Assgn1Src-CS17BTECH11050.c -o time -lrt

2. A binary file named time is created and now any valid shell command can be run with the following syntex
	$ ./time <command> <arg1> <arg2> ..

========================================

Examples:

1. The `ls` command

	$ gcc Assgn1Src-CS17BTECH11050.c -o time -lrt
	$ ./time ls
	Assgn1Readme-CS17BTECH11050.txt  Assgn1Report-CS17BTECH11050.pdf  Assgn1Src-CS17BTECH11050.c  time
	Elapsed time: 0.002046

2. The `ls -l` command

	$ gcc Assgn1Src-CS17BTECH11050.c -o time -lrt
	$ ./time ls -l
	total 448
	-rw-rw-r-- 1 shraiysh shraiysh   1167 Nov 16 17:39 Assgn1Readme-CS17BTECH11050.txt
	-rw-rw-r-- 1 shraiysh shraiysh 436523 Nov 16 17:27 Assgn1Report-CS17BTECH11050.pdf
	-rw-rw-r-- 1 shraiysh shraiysh   1151 Nov 16 13:53 Assgn1Src-CS17BTECH11050.c
	-rwxrwxr-x 1 shraiysh shraiysh   8840 Nov 16 17:41 time
	Elapsed time: 0.003514

3. The `mkdir` command

	$ gcc Assgn1Src-CS17BTECH11050.c -o time -lrt
	$ ./time mkdir hello
	Elapsed time: 0.002834

========================================