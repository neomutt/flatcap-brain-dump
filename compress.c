
Compressed files
	working?
	add to empty box
	add to "add-only" box
	set each combination of hooks

compress
	limitations -- filenames
	document %f %t need to be quoted
		limit filenames
		can't contain quotes
			'' can't contain '
			"" can't contain "
		need code to escape filenames
			would need to be done in an OS-dependent way

compress -- hooks should be considered first, then default mutt behaviour
	need test-hook i.e. "is this an xz-compressed" file?
	mailbox type should be per-hook-set

compress features
	example of tar.gz of maildir mailbox?
	compress won't be able to tidy up
	unless...
		compress creates a dir
		extracts to that dir
		deletes entire dir on close

compress
	change hook placeholders to be more descriptive?
	%t -> (T)emp file
	%p -> (P)laintext file
	%c -> (C)ompressed file

