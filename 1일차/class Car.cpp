#include <iostream>
#include <string>
#include <Windows.h>
#include <time.h>
using namespace std;

class Car {

private:
	int speed;
	int gear;
	string color;
	const int MAX_SPEED = 100;
public:
	Car(int s, int g, string c);
	Car() {
		cout << "생성자 호출" << endl;
		speed = 0;
		gear = 1;
		color = "white";
	}
	~Car() {
		cout << "소멸자 호출" << endl;
	}

	// get
	int getSpeed();
	int getGear();
	string getColor();
	// set
	void setSpeed(int s);
	void setGear(int g);
	void setColor(string c);

	void SpeedUp();
	void SpeedDown();
	void Show();
};

Car::Car(int s, int g, string c) : speed(s), gear(g), color(c), MAX_SPEED(200) {}

int Car::getSpeed() { return speed; }
int Car::getGear() { return gear; }
string Car::getColor() { return color; }

void Car::setSpeed(int s) { this->speed = s; }
void Car::setGear(int g) { this->gear = g; }
void Car::setColor(string c) { this->color = c; }

void Car::SpeedUp() { this->speed += 10; }
void Car::SpeedDown() { this->speed -= 10; }
void Car::Show() {
	cout << "============" << endl;
	cout << "속도: " << speed << endl;
	cout << "기어: " << gear << endl;
	cout << "색상: " << color << endl;
	cout << "============" << endl;
}

int main() {
	//srand(time(NULL));
	srand(GetTickCount());

	Car car1(rand() % 200, 1, "red"), car2(rand() % 200, 1, "red");
	Car* a = new Car();

	car1.Show();
	car2.Show();

	if (car1.getSpeed() > car2.getSpeed())
		cout << "car1이 승리함" << endl;
	else
		cout << "car2이 승리함" << endl;

	delete a;

	return 0;
}