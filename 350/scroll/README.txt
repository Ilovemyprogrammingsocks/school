Amber Dean

some bugs exist.  I'm sure some that I'm unaware of.
notably the math in next() is scuffed and imprecise.
some window sizes may behave erratically.
error handling is inconsistent.
however it does compile, it does run, and does function largely as expected,
though not entirely aligned with some specifications.




self assessment

man page - mostly works
	might not be formatted exactly to your ideals. I tried to follow the man
	page for more as close as I could.

initial screen full - works

prompt - works

space key - mostly works
	doesn't technically skip, I implemented it so it would quickly process a
	screen of lines to appear as though it skipped. unsure how this compares
	to expected behavior so im leaving it as mostly works

slow/stop scroll - works

f & s keys - works
	uses percentage based incrementation

line wrapping - mostly works
	I think that it fully works but havent properly stress tested it

tabs handled - mostly works
	replaces tab characters with '\t' I think it meets specs but not sure

q key - works

stdin handling - not implemented

makefile - mostly works
	uses standard c libraries, and does not list them as conditions, unsure
	if this breaks standard

error handling - sometimes works
	input errors and some external calls have error handling, others were neglected.

extra credit - not implemented
