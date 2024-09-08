#include <iostream>
#include "FactoryContainer.hpp"

class Wheel
{
public:
	Wheel(FactoryContainer& fc) {}
};

class Car
{
public:
	Car(FactoryContainer& fc, const std::string& brand) {
		pWheel1 = fc.Create<Wheel>();
		pWheel2 = fc.Create<Wheel>();
		pWheel3 = fc.Create<Wheel>();
		pWheel4 = fc.Create<Wheel>();
		Brand = brand;
	}

	~Car() {
		std::cout << "Car destroyed";
	}
private:
	std::string Brand;
	Wheel* pWheel1;
	Wheel* pWheel2;
	Wheel* pWheel3;
	Wheel* pWheel4;
};

int main(int argc, char* argv[]) {
	auto fc = FactoryContainer();
	fc.Add<Wheel>();
	fc.Add<Car>([](FactoryContainer& fc) {return new Car(fc, "Mercedes"); });
	fc.Add<Car>([](FactoryContainer& fc) {return new Car(fc, "Honda"); });

	auto myCar = fc.Create<Car>();
	fc.Destroy<Car>(myCar);


	auto c1 = &fc.Get<Car>();
	auto c2 = &fc.Get<Car>();
	// fc.Destroy<Car>(c1);

	std::cout << "Hello World";
}