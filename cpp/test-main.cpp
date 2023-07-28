//#include <cppunit/CompilerOutputter.h>
//#include <cppunit/TestResultCollector.h>
//#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>

#include "test-gnome.cpp"

int main(int argc, char **argv)
{
	CppUnit::TextUi::TestRunner runner;

	runner.addTest( GnomeTest::suite() );

	runner.run();

	return 0;
}

