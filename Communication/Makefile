CC=gcc

pipe_test:pipe_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

fifo_write:fifo_write.c
	-$(CC) -o $@ $^

fifo_read:fifo_read.c
	-$(CC) -o $@ $^

system_test:system_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

fork_test:fork_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

fork_fd_test:fork_fd_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

erlou:erlou.c
	-$(CC) -o $@ $^

execve_test: execve_test.c erlou
	-$(CC) -o $@ $<
	-./$@
	# -rm -f ./$@

execve_fork_test: execve_fork_test.c erlou
	-$(CC) -o $@ $(firstword $^)
	-./$@
	# -rm -f ./$(lastword $^)

waitpid_test:waitpid_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

ps_tree_test:ps_tree_test.c erlou
	-$(CC) -o $@ $<
	-./$@
	-rm ./$@ ./$(lastword $^)

shared_memory:shared_memory.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

father_son_mq_test:father_son_mq_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@