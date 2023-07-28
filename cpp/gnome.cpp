#include <iostream>
#include <stdexcept>
#include "gnome.h"

Gnome::Gnome(const std::string& n, const std::string& p, int a)
		: age(a), name(n), profession(p)
{
}

Gnome::Gnome(const Gnome& that)
{
	this->age = that.age;
	this->name = that.name;
	this->profession = that.profession;
}

Gnome::~Gnome()
{
}

int Gnome::Age() const
{
	return age;
}

std::string Gnome::Name() const
{
	return name;
}

std::string Gnome::Profession() const
{
	return profession;
}

void Gnome::SetAge(int a)
{
	if (a >= 0)
		this->age = a;
	else
		throw std::invalid_argument("age less than zero");
}

void Gnome::SetName(const std::string& newname)
{
	this->name = newname;
}

void Gnome::SetProfession(const std::string& newprof)
{
	this->profession = newprof;
}

Gnome& Gnome::operator=(const Gnome& that)
{
	if (this != &that) {
		this->age = that.age;
		this->name = that.name;
		this->profession = that.profession;
	}
	return *this;
}

// Overloaded Operators

bool operator==(const Gnome& a, const Gnome& b)
{
	return a.Age() == b.Age() && a.Name() == b.Name();
}

bool operator!=(const Gnome& a, const Gnome& b)
{
	return !(a == b);
}

std::ostream& operator<<(std::ostream& os, const Gnome &g)
{
	os << g.Name() << " [" << g.Age() << " y, " << g.Profession() << "]";
	return os;	
}

