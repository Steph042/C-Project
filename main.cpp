/**
@file main.cpp
@brief test d'uso della classe Stack
**/

#include "stack.h" //dichiarazione dei metodi
#include <iostream> //std::cout

/**
  Punto
  @brief Implementazione dei metodi della struct di test Punto
*/
Punto::Punto(void) : x(0.0), y(0.0) {}

Punto::Punto(double xx, double yy) : x(xx), y(yy){}

std::ostream& operator<<(std::ostream &os, const Punto &p){
  os << "(" << p.x << ", " << p.y << ")";

  return os;
}

bool Punto::operator==(const Punto &p2){
  if(this->x == p2.x && this->y == p2.y)
    return true;

  return false;
}

/**
  isEven
  @brief Predicato usato per testare removeif
*/
bool isEven (int x) { return ((x % 2) == 0); }

/**
  even
  @brief struct utilizzate per testare remove if
*/
struct even {
	bool operator()(int v) const {
		return ((v % 2) == 0);
	}
};

int main(int argc, char const *argv[]) {

  Stack<Punto>::iterator it, ite;

  Punto p1(3, 0);
  Punto p2(1, 2);
  Punto p3(3, 5);

  Stack<Punto> s1(3, p1);

  for(it=s1.begin(),ite=s1.end(); it!=ite; ++it) {
		std::cout << *it << std::endl;
  }

  Stack<Punto>::iterator s, e;
  s = s1.begin();
  e = s1.end();

  Stack<Punto> s2(s, e);

  for(it=s2.begin(),ite=s2.end(); it!=ite; ++it) {
		std::cout << *it << std::endl;
  }
  const int n = 2;
  Stack<int> s3(3, n);
  Stack<bool> s4;
  std::cout << s4 << '\n';

  Stack<double> s6(s3);
  std::cout << s6 << '\n';

  Stack<int> s7(s3);
  std::cout << s7 << '\n';

  Stack<Punto> s8;
  s8.fill(s, e);
  std::cout << s8 << '\n';

  s3.push(3);
  s3.push(5);
  s6.clean();
  std::cout << s6 << '\n';

  s7 = s3;
  std::cout << s7 << '\n';

  std::cout << s3 << '\n';

  s3.removeif(isEven);
  std::cout << s3 << '\n';

  s3.push(2);
  s3.push(6);
  std::cout << s3 << '\n';

  s3.removeif(even());

  std::cout << s3 << '\n';

  int es = s3.pop();

  std::cout << s3 << '\n';
  std::cout << es << '\n';

  return 0;
}
