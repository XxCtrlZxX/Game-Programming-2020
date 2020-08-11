#include <iostream>
using namespace std;

template <typename T>
T get_max(T x, T y) {
	return x > y ? x : y;
}

template <typename T1, typename T2>
void ShowData(T1 t1, T2 t2) {
	cout << t1 << " + " << t2 << endl;
}

int main() {
	/*int x, y;
	float x1, y1;
	
	cin >> x >> y;
	cout << "정수 : " << get_max(x, y) << endl;
	cin >> x1 >> y1;
	cout << "실수 : " << get_max(x1, y1) << endl;*/

	int a;
	float b;
	char c;

	cin >> a >> b >> c;

	ShowData<int, float>(a, b);
	ShowData<float, char>(b, c);
	ShowData<int, char>(a, c);


}