#include <iostream>
#include "goblin.h"

Goblin& TheMasterGoblin(void);

int main(int argc, char *argv[])
{
    Goblin g("Peon");
    Goblin& m = TheMasterGoblin();
    std::cout << "g : " << g.Name() << std::endl;
    std::cout << "m : " << m.Name() << std::endl;
    return 0;
}

// This function contains the instance of "the master goblin."
// It is a "global object" and this function allows its initialization to be
// controlled with access across multiple translation units (object files).
// 
// Normally, this function would go in another file that is linked into the
// project.
//
// It keeps the object out of the global namespace, but replaces it with a
// function that is global.  This is a limited form of the Singleton pattern.
// 
Goblin& TheMasterGoblin(void)
{
    static Goblin theMasterGoblin("The Master", Goblin::Master);
    return theMasterGoblin;
}

