
#include <stdio.h>
#include <stdint.h>

int32_t __bionic_swap(int32_t new_value, volatile int32_t *ptr) {
  __asm__ __volatile__ ("xchgl %1, %0"
                        : "=r" (new_value)
                        : "m" (*ptr), "0" (new_value)
                        : "memory");
  return new_value;
}

int main() {
	int ret, lock = 1;

	printf("before: lock = %d\n", lock);
	ret = __bionic_swap(3, &lock);
	printf(" after: lock = %d, ret = %d\n", lock, ret);

	return 0;
}
