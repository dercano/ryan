
// sp.cpp
#include <stdio.h>

class Car
{
public:
	Car() { printf("Car()\n"); }
	~Car() { printf("~Car()\n"); }

	void go() { printf("Car::go()\n"); }
};

template<typename T> class sp
{
	T* p;
public:
	sp(T* a) : p(a) {}
	~sp() { delete p; }

	T* operator->() { return p; }
	T& operator*() { return *p; }
};

int main()
{
	{
		// Car* pCar = new Car();
		sp<Car> pCar = new Car();
		pCar->go();	// pCar.operator->()go(); -> (pCar.operator->())->go();
		(*pCar).go();	// (pCar.operator*()).go();
	}
	getchar();
	return 0;
}



















