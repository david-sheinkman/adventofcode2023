#include <iostream>
#include <chrono>
using namespace std;

void p1();
void p2();
void p3();
void p4();
void p5();
void p6();
void p7();
void p8();
void p9();
void p10();
void p11();
void p12();
void p13();
void p14();
void p15();
void p16();
void p17();
void p18();
void p19();
void p20();
void p21();
void p22();
void p23();
void p24();
void p25();

int main() {
	auto begin = std::chrono::steady_clock::now();
	p8();
	auto end = std::chrono::steady_clock::now();
	std::cout << "Time=" << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << std::endl;
	return 0;
}
