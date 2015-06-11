
#include <stdio.h>

class Car
{
public:
	Car() { printf("Car()\n"); }
	~Car() { printf("~Car()\n"); }
};

int main() {

	{
		Car car;
	}
	getchar();

	return 0;
}
