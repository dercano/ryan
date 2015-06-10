
#if 0
// atomic.c
#include <stdint.h>	// for int32_t
#include <stdio.h>

int __bionic_cmpxchg(int32_t old_lock, int32_t new_lock, volatile int32_t* ptr) 
{
    int32_t prev;
    __asm__ __volatile__ ("lock; cmpxchgl %1, %2"
                          : "=a" (prev)
                          : "q" (new_lock), "m" (*ptr), "0" (old_lock)
                          : "memory");
    return prev != old_lock;
}

int main()
{
	int lock, ret;

	lock = 0;
	printf("before: lock = %d\n", lock);
	ret = __bionic_cmpxchg(0, 1, &lock);
	printf(" after: lock = %d, ret = %d\n", lock, ret);

	getchar();

	lock = 1;
	printf("before: lock = %d\n", lock);
	ret = __bionic_cmpxchg(0, 1, &lock);
	printf(" after: lock = %d, ret = %d\n", lock, ret);


	return 0;
}
#endif

#include <stdint.h>	// for int32_t
#include <stdio.h>

// /root/android-google/bionic/libc/private/bionic_atomic_x86.h
/* Atomic decrement, without explicit barriers. */
int32_t __bionic_atomic_dec(volatile int32_t* ptr) {
  int increment = -1;
  __asm__ __volatile__ ("lock; xaddl %0, %1"
                        : "+r" (increment), "+m" (*ptr)
                        : : "memory");
  /* increment now holds the old value of *ptr */
  return increment;
}

int main()
{
	int ret, value = 2;

	printf("before: value = %d\n", value);
	ret = __bionic_atomic_dec(&value);
	printf(" after: value = %d, ret = %d\n", value , ret);
}
























