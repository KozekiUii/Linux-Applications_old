CC=gcc

CFLAGS = `pkg-config --cflags glib-2.0`
LIBS = `pkg-config --libs glib-2.0`
#LL = `pkg-config --cflags --libs glib-2.0`

create_test:create_test.c
	-$(CC) -o $@ $^
# 	-./$@
# 	-rm ./$@

terminate_test:terminate_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

pthread_detach_test:pthread_detach_test.c
	-$(CC) -o $@ $^
	-./$@
# 	-rm ./$@

pthread_cancel:pthread_cancel.c
	-$(CC) -g -pthread -o $@ $^
	-./$@
	-rm ./$@

pthread_cancel_async_test:pthread_cancel_async_test.c
	-$(CC) -o $@ $^ -pthread
	-./$@
	-rm ./$@

pthread_cancel_disable_test:pthread_cancel_disable_test.c
	-$(CC) -g -o $@ $^ -pthread
	-./$@
# 	-rm ./$@

race_condition_test:race_condition_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

mutex_test:mutex_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

rwlock_test_writer_unlock:rwlock_test_writer_unlock.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

rwlock_test:rwlock_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

rwlock_rw_alternate_test:rwlock_rw_alternate_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

rwlock_write_hungry:rwlock_write_hungry.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

rwlock_write_hungry_solved:rwlock_write_hungry_solved.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

condition_var:condition_var.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

unnamed_sem_bin_thread_condition:unnamed_sem_bin_thread_condition.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

unnamed_sem_bin_thread:unnamed_sem_bin_thread.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

unnamed_sem_bin_process:unnamed_sem_bin_process.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

unnamed_sem_count_thread:unnamed_sem_count_thread.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

unnamed_sem_count_thread:unnamed_sem_count_thread.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

unnamed_sem_count_process:unnamed_sem_count_process.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

named_sem_bin:named_sem_bin.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

named_sem_count:named_sem_count.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

#thread_pool_test:thread_pool_test.c
#	-$(CC) -o $@ -I/usr/include/glib-2.0 $^
#	-./$@
#	-rm ./$@

# 编译 thread_pool_test 的规则
thread_pool_test: thread_pool_test.c
	gcc -o thread_pool_test thread_pool_test.c $(CFLAGS) $(LIBS)
	-./$@
	-rm ./$@
