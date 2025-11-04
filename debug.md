Debugging with Valgrind

I've been busy writing a replacement for the Config handling in NeoMutt.
It involved lots of structures and pointers and it was quite bewildering at
times.

To make sure that I wasn't leaking memory, or using invalid pointers, I ran
the test code through valgrind (a memory checker and much more).

    valgrind -v --track-origins=yes demo

Whilst Googling for some gdb knowledge, I came across this article by
Thomas Nilefalk:

    http://www.responsive.se/thomas/2013/09/20/debugging-memory-leaks-with-valgrind-and-gdb/

By using valgrind and gdb together you can stop the program at the point
where there's an illegal memory access.

To try it out you'll need two windows:

Window 1:
    valgrind --vgdb=yes --vgdb-error=0 mutt [args]
    This will start neomutt under valgrind

Window 2:
    cgdb mutt
        set non-stop off
        target remote | vgdb
        cont

On my machine NeoMutt stops 6 times in the regex code at startup.
(I'm not sure if we can do anything about this)

When stopped at a breakpoint, you can send commands to valgrind, such as:

    monitor leak_check          # run the leak checker now
    who_points_at               # Who references this bit of memory?

This made my debugging much simpler.

Do YOU have any debugging tips?

Cheers,
    Rich / FlatCap
