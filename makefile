MAKEFLAGS += --silent

warn_flags = -Wall -Wextra

debug_flags = -ggdb3

optimize_flags = -O3

thread_flags = -pthread

all_flags = $(thread_flags) $(warn_flags)

default:
	gcc src/*.c $(all_flags) -o main

debug:
	gcc src/*.c $(all_flags) $(debug_flags) -o main

optimized:
	gcc src/*.c $(all_flags) $(optimize_flags) -o main