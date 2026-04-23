A C program by Amber Dean

Known bugs:
should be none, but I experienced some issues if the archive or folder being un archived have unexpected permissions. Unsure how it might interact with different environment permission defaults.

Known deviations:
no z827 compression
wasn't sure if you wanted us to chech for a .z extension during creation so I just appended .z to every submitted archive name.  this should not affect anythingfunctionally, except maybe external automation so sorry if thats you.
there wasn't a specified format that create should accept while selecting files,so I came up with one.  again, shouldn't be a functional change execpt for automation purposes
I have not fully tested the error handling, and some cases aren't covered because they should be inacessible.  The common errors that would be encountered by standard use should all be covered, like input checking and prechecks for file maniplulation.  I should also mention that some specific errors arent covered if the file system being accessed is edited or changed while the program is running. 






Testing cases:


:3amber@OWO:~/Desktop$ make
gcc zarchive.c -o zarchive
:3amber@OWO:~/Desktop$ ./zarchive c archive
HERE IS A LIST OF AVAILIBLE FILES, PLEASE ENTER A LIST OF YOUR OWN INCLUDING THE FILES YOU WISH TO ARCHIVE, OR ENTER "*" TO SELECT ALL FILES
<<enter 'q' when done>>
zarchive.c 	 5901 bytes 	 2026-04-22 16:52:17
zarchive 	 16800 bytes 	 2026-04-22 18:07:20
Stars.ods 	 20997 bytes 	 2026-04-18 17:31:53
Makefile 	 73 bytes 	 2026-04-22 16:53:53
Makefile
zarchive.c
q
zarchive.c 	 5901 bytes 	 2026-04-22 16:52:17
Makefile 	 73 bytes 	 2026-04-22 16:53:53
:3amber@OWO:~/Desktop$ ./zarchive x archive.z folder
:3amber@OWO:~/Desktop$ ls -l
total 72
-rw-rw-r-- 1 amber amber  6606 Apr 22 18:08 archive.z
drwxrwxr-x 2 amber amber  4096 Apr 22 18:08 folder
-rw-rw-r-- 1 amber amber    73 Apr 22 16:53 Makefile
drwxrwxr-x 5 amber amber  4096 Mar 25 16:40 school
-rw-rw-r-- 1 amber amber 20997 Apr 18 17:31 Stars.ods
-rwxrwxr-x 1 amber amber 16800 Apr 22 18:07 zarchive
-rw-rw-r-- 1 amber amber  5901 Apr 22 16:52 zarchive.c


:3amber@OWO:~/Desktop$ ./zarchive c
HELLO amber, WHAT ARCHIVE WOULD YOU LIKE TO CREATE TODAY
tarball
HERE IS A LIST OF AVAILIBLE FILES, PLEASE ENTER A LIST OF YOUR OWN INCLUDING THE FILES YOU WISH TO ARCHIVE, OR ENTER "*" TO SELECT ALL FILES
<<enter 'q' when done>>
zarchive.c 	 5901 bytes 	 2026-04-22 16:52:17
zarchive 	 16840 bytes 	 2026-04-22 19:23:47
Stars.ods 	 20997 bytes 	 2026-04-18 17:31:53
Makefile 	 73 bytes 	 2026-04-22 16:53:53
*
zarchive.c 	 5901 bytes 	 2026-04-22 16:52:17
zarchive 	 16840 bytes 	 2026-04-22 19:23:47
Stars.ods 	 20997 bytes 	 2026-04-18 17:31:53
Makefile 	 73 bytes 	 2026-04-22 16:53:53
:3amber@OWO:~/Desktop$ ./zarchive x tarball.z folder
:3amber@OWO:~/Desktop$ cd folder
:3amber@OWO:~/Desktop/folder$ ls -l
total 56
-rw-rw-r-- 1 amber amber    73 Apr 22 19:29 Makefile
-rw-rw-r-- 1 amber amber 20997 Apr 22 19:29 Stars.ods
-rw-rw-r-- 1 amber amber 16840 Apr 22 19:29 zarchive
-rw-rw-r-- 1 amber amber  5901 Apr 22 19:29 zarchive.c




Archive Compression Self-evaluation

Ask for archive name (5pts)
	x works  _ mostly works _ sometimes works _ not implemented

Make sure archive does not exist (5pts)
	x works  _ mostly works _ sometimes works _ not implemented

Get user's name (5pts)
	x works  _ mostly works _ sometimes works _ not implemented

Show list of files to archive (25pts)
	x works  _ mostly works _ sometimes works _ not implemented

Ask for files to archive (5pts)
	x works  _ mostly works _ sometimes works _ not implemented

Archive the list of files (15pts)
	x works  _ mostly works _ sometimes works _ not implemented

Archive with * (5pts)
	x works  _ mostly works _ sometimes works _ not implemented

Show final contents of archive (5pts)
	x works  _ mostly works _ sometimes works _ not implemented

Makefile (5pts)
	x works  _ mostly works _ sometimes works _ not implemented

Unarchive file (15pts)
	x works  _ mostly works _ sometimes works _ not implemented

Error handling (5pts)
	_ works  x mostly works _ sometimes works _ not implemented

z827 compression (5pts)
	_ works  _ mostly works _ sometimes works x not implemented
