#include "NoPersonException.h"

int main() {
	int pizzaSlices = 12;
	int persons = 0;
	int slicesPerPerson = 0;

	try {
		cout << "사람 수 입력 : ";
		cin >> persons;
		if (persons <= 0)
			throw NoPersonException(persons);
		
		slicesPerPerson = pizzaSlices / persons;
		cout << "한 사람당 피자는 " << slicesPerPerson << "입니다." << endl;
	}
	catch (NoPersonException e) {
		cout << "오류 : 사람이 " << e.getPersons() << "명 입니다." << endl;
	}
}