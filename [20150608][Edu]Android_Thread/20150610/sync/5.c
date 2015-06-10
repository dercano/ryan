
// 5.c
#include <stdio.h>
#include <pthread.h>
#include <stdint.h>	// for int32_t

// /root/android-google/bionic/libc/private/bionic_atomic_x86.h
int __bionic_cmpxchg(int32_t old_value, int32_t new_value, volatile int32_t* ptr) {
    int32_t prev;
    __asm__ __volatile__ ("lock; cmpxchgl %1, %2"
                          : "=a" (prev)
                          : "q" (new_value), "m" (*ptr), "0" (old_value)
                          : "memory");
    return prev != old_value;
}

int32_t __bionic_atomic_dec(volatile int32_t* ptr) {
	int increment = -1;
	__asm__ __volatile__ ("lock; xaddl %0, %1"
			: "+r" (increment), "+m" (*ptr)
			: : "memory");
	/* increment now holds the old value of *ptr */
	return increment;
}

void spin_lock(int* lock) { while(__bionic_cmpxchg(0, 1, lock)); }
void spin_unlock(int* lock) { __bionic_atomic_dec(lock); }

int lock = 0;
int sum = 0;
void* thread_func(void* arg) {
	int i;
	for(i = 0; i < 100000000; i++) {
		spin_lock(&lock);	//while(__bionic_cmpxchg(0, 1, &lock));
		//--------------------------
		++sum; sleep(60);
		//--------------------------
		spin_unlock(&lock);	//__bionic_atomic_dec(&lock);
		
	}
	return NULL;
}

int main() {
	pthread_t t1, t2;

	pthread_create(&t1, 0, thread_func, 0);
	pthread_create(&t2, 0, thread_func, 0);

	pthread_join(t1, 0);
	pthread_join(t2, 0);

	printf("sum = %d\n", sum);
	return 0;
}
