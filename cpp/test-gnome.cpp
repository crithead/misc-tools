#include <cppunit/TestFixture.h>
#include <cppunit/TestSuite.h>
#include <cppunit/extensions/HelperMacros.h>

#include "gnome.h"

class GnomeTest : public CppUnit::TestFixture
{
public:
	static CppUnit::TestSuite *suite() {
		CppUnit::TestSuite *testSuite = new CppUnit::TestSuite("Gnome test");
		testSuite->addTest(new CppUnit::TestCaller<GnomeTest>(
				"Test constructor", &GnomeTest::TestConstructor));
		testSuite->addTest(new CppUnit::TestCaller<GnomeTest>(
				"Test equals", &GnomeTest::TestEquals));
		return testSuite;
	}

	GnomeTest(std::string name = "Gnome test") : CppUnit::TestFixture() {}

	~GnomeTest() {}

	void setUp() {
	}

	void tearDown() {
	}

	void TestConstructor() {
		Gnome gnome;
		CPPUNIT_ASSERT(gnome.Name() == "None");
		CPPUNIT_ASSERT(gnome.Profession() == "None");
		CPPUNIT_ASSERT(gnome.Name() == "None");
	}

	void TestEquals() {
		Gnome gnomeOne("One", "Red", 1);
		Gnome gnomeTwo("Two", "Blue", 2);
		CPPUNIT_ASSERT(gnomeOne == gnomeOne);
		CPPUNIT_ASSERT(gnomeOne != gnomeTwo);
		gnomeOne = gnomeTwo;
		CPPUNIT_ASSERT(gnomeOne == gnomeTwo);
	}
private:

};


