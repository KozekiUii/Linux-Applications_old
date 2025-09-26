CC=gcc

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