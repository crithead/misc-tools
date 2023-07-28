//
// Constructors Initialization and Inheritance
//
// How to initialize the base class in a derived class constructor.
//
#include <iostream>

class One
{
public:
	One(int a0 = 0, int b0 = 0);
	One(const One& one);
	virtual ~One() {}
	virtual int A() const;
	virtual int B() const;
private:
	int a;
	int b;
};

class Two : public One
{
public:
	Two(int a0 = 0, int b0 = 0, int x0 = 0, int y0 = 0);
	Two(const Two& two);
	virtual ~Two() {}
	virtual int X() const;
	virtual int Y() const;
private:
	int x;
	int y;
};

One::One(int a0, int b0) :
	a(a0), b(b0)
{
}

One::One(const One & o) :
	a(o.a), b(o.b)
{
}

int One::A() const
{
	return a;
}

int One::B() const
{
	return b;
}


Two::Two(int a0, int b0, int x0, int y0) :
	One(a0, b0), x(x0), y(y0)
{
}

Two::Two(const Two& t) :
	One(t.A(), t.B()), x(t.x), y(t.y)
{
}

int Two::X() const
{
	return x;
}

int Two::Y() const
{
	return y;
}


int main(int argc, char **argv)
{
	One o1(11, 22);
	Two t1(111, 222, 333, 444);

	std::cout << "o1.A() = " << o1.A() << std::endl;
	std::cout << "o1.B() = " << o1.B() << std::endl;

	std::cout << "t1.A() = " << t1.A() << std::endl;
	std::cout << "t1.B() = " << t1.B() << std::endl;
	std::cout << "t1.X() = " << t1.X() << std::endl;
	std::cout << "t1.Y() = " << t1.Y() << std::endl;

	return 0;
}

