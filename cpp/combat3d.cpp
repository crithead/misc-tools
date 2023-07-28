//
//  Combat with 3 Dice
//
#include <cassert>
#include <cctype>
#include <iostream>
#include <random>
#include <string>

/**
 * Unit types
 */
enum {
    NoUnitType,
    HeavyInfantry,
    HeavyKnight,
    MediumInfantry,
    MediumKnight,
    LightInfantry,
    LightKnight,
    DualWeapons,
    LastUnitType
};

using namespace std;

struct Options;
struct Unit;

static int AttackResult(int, int);
static void Fight(const Options&, Unit&, Unit&);
static void GetDice(int, int&, int&, int&);
static void GetOptions(int, char **, Options&);
static void InitUnit(int, Unit&);
static int Max(const int, const int);
static void PrintHelp(void);
static void PrintUnit(const Unit&);
static void PrintWins(const Unit&);
static int RandInt(int, int);
static int Randomize(const Options&, Unit&);
static int Step(int);


struct Options
{
    Options() : printHelp(false), same(false), verbose(false),
            number(1), type(NoUnitType) {}
    void Check(void) {
        assert(number > 0);
    }
    void Print(void) {
        cerr << "printHelp  : " << (printHelp ? "true" : "false") << endl;
        cerr << "same       : " << (same ? "true" : "false") << endl;
        cerr << "verbose    : " << (verbose ? "true" : "false") << endl;
        cerr << "number     : " << number << endl;
        cerr << "type       : " << type << endl;
    }

    bool printHelp;
    bool random;
    bool same;
    bool verbose;
    int number;         // number of fights
    int type;           // Unit type
};


struct Unit
{
    Unit(const string& n, const string& d) : name( n ), description( d ),
            speed( 10 ), attack( 10 ), damage( 10 ), defense ( 10 ),
            armor( 10 ), health ( 100 ), maxHealth( 100 ),
            turn( 0 ), wins( 0 ) {}
    ~Unit() {}
    void reset(void) {
        health = maxHealth;
        turn = 0;
    }
    string name;
    string description;
    int speed;
    int attack;
    int damage;
    int defense;
    int armor;
    int health;
    int maxHealth;
    // int wounds;
    // int toughness; //  aka Wound Threshold
    int turn;
    int wins;
};


enum {
    None, Fumble, Miss, Hit, GoodHit, ExcellentHit
};


int AttackResult(int atk, int def )
{
    int value = None;
    int diff = atk - def;

    if ( atk == 3 )
        value = Fumble;
    else if ( diff > 2 * def )
        value = ExcellentHit;
    else if ( diff > def )
        value = GoodHit;
    else if ( diff > 0 )
        value = Hit;
    else
        value = Miss;

    return value;
}


void Fight( const Options& opts, Unit& u1, Unit& u2 )
{
    u1.reset();
    u2.reset();

    u1.turn = RandInt( 1, u1.speed );
    u2.turn = RandInt( 1, u2.speed );

    PrintUnit( u1 );
    PrintUnit( u2 );

    int turn = 0;
    while ( u1.health > 0 && u2.health > 0 ) {
        // Advance the turn counter until the next Unit's turn comes up
        while ( turn < u1.turn && turn < u2.turn )
            turn++;

        Unit *a = nullptr;
        Unit *b = nullptr;
        if ( turn == u1.turn ) {
            a = &u1;
            b = &u2;
        }
        else if ( turn == u2.turn ) {
            a = &u2;
            b = &u1;
        }
        else {
            cout << "--- turn    " << turn << endl; 
            cout << "--- u1.turn " << u1.turn << endl; 
            cout << "--- u2.turn " << u2.turn << endl; 
        }

        // A attacks B
        int atk = Step( a->attack );
        int def = Step( b->defense );
        int dam = 0;
        switch ( AttackResult( atk, def ) ) {
        case Fumble:
            cout << "[" << turn << "] " << a->name << " fumbles." << endl;
            // TODO Attacker's next attack is delayed
            a->turn += Step( a->speed );
            break;
        case Miss:
            cout << "[" << turn << "] " << a->name << " misses " << b->name << "." << endl;
            break;
        case Hit:
            cout << "[" << turn << "] " << a->name << " hits " << b->name;
            dam = Step( a->damage ) - b->armor;
            dam = Max( 0, dam );
            cout << " for " << Max( 0, dam ) << " damage." << endl;
            b->health -= dam;
            break;
        case GoodHit:
            // halves armor
            cout << "[" << turn << "] " << a->name << " solidly hits " << b->name;
            dam = Step( a->damage ) - ( b->armor / 2 );
            dam = Max( 0, dam );
            cout << " for " << Max( 0, dam ) << " damage." << endl;
            b->health -= dam;
            break;
        case ExcellentHit:
            // ignores armor
            cout << "[" << turn << "] " << a->name << " critically hits " << b->name;
            dam = Step( a->damage );
            dam = Max( 0, dam );
            cout << " for " << Max( 0, dam ) << " damage." << endl;
            b->health -= dam;
            break;
        }

        // Attacker attacks again in 'speed' turns
        a->turn += a->speed;
    }

    if ( u1.health > 0 && u2.health <= 0 )
        u1.wins++;
    else if ( u2.health > 0 && u1.health <= 0 )
        u2.wins++;
    else
        cout << "--- No winner! (U1 " << u1.health << ", U2 " << u2.health
             << ")" << endl;

    PrintUnit( u1 );
    PrintUnit( u2 );
}


void GetDice( int step, int& a, int& b, int& c )
{
    if ( step > 3 ) {
        a = b = c = ( step / 3 ) * 2;
        if ( step % 3 == 0 )
            a -= 2;
        else if ( step % 3 == 2 )
            c += 2;
    }
    else {
        a = b = c = 1;
    }
}


void GetOptions( int argc, char **argv, Options& opts )
{
    for ( int i = 1; i < argc; i++ ) {
        string value( argv[i] );

        if (value == "--help") {
            opts.printHelp = true;
        }
        else if (value == "--same") {
            opts.same = true;
        }
        else if (value == "--verbose") {
            opts.verbose = true;
        }
        else if (value == "--number") {
            if ( i + 1 < argc )
                opts.number = atoi( argv[ i + 1 ] );
        }
        else if (value == "--type") {
            if ( i + 1 < argc )
                opts.type = atoi( argv[ i + 1 ] );
            assert( NoUnitType < opts.type && opts.type < LastUnitType );
        }
    }

    opts.Check();
}


/**
 *  Armor and weapons "table"
 */
enum {
    BaseSpeed = 6,
    BaseAttack = 6,
    BaseDamage = 6,
    BaseDefense = 6,
    BaseArmor = 0,

    HeavyArmorSpeed = 9,
    MediumArmorSpeed = 5,
    LightArmorSpeed = 2,

    OneHandWeaponSpeed = 5,
    OneHandWeaponAttack = 5,
    OneHandWeaponDamage = 5,

    TwoHandWeaponSpeed = 8,
    TwoHandWeaponAttack = 5,
    TwoHandWeaponDamage = 10,

    StabbyWeaponSpeed = 1,
    StabbyWeaponAttack = 5,
    StabbyWeaponDamage = 2,

    HeavyArmorDefense = 4,
    MediumArmorDefense = 4,
    LightArmorDefense = 4,

    HeavyArmor = 10,
    MediumArmor = 7,
    LightArmor = 4,

    ShieldSpeed = 2,
    ShieldDefense = 4,
    ShieldArmor = 2,
};


void InitUnit(int type, Unit& u)
{
    switch (type) {
    case HeavyInfantry:
        // Heavy Infantry = Weapon & shield
        u.description = "Heavy Infantry";
        u.speed += HeavyArmorSpeed + OneHandWeaponSpeed + ShieldSpeed;
        u.attack += OneHandWeaponAttack;
        u.damage += OneHandWeaponDamage;
        u.defense += HeavyArmorDefense + ShieldDefense;
        u.armor += HeavyArmor + ShieldArmor;
        break;
    case HeavyKnight:
        // Heavy Knight == 2h weapon
        u.description = "Heavy Knight";
        u.speed += HeavyArmorSpeed + TwoHandWeaponSpeed;
        u.attack += TwoHandWeaponAttack;
        u.damage += TwoHandWeaponDamage;
        u.defense += HeavyArmorDefense;
        u.armor += HeavyArmor + ShieldArmor;
        break;
    case MediumInfantry:
        // Medium Infantry -- Weapon & shield
        u.description = "Medium Infantry";
        u.speed += MediumArmorSpeed + OneHandWeaponSpeed + ShieldSpeed;
        u.attack += OneHandWeaponAttack;
        u.damage += OneHandWeaponDamage;
        u.defense += MediumArmorDefense + ShieldDefense;
        u.armor += MediumArmor + ShieldArmor;
        break;
    case MediumKnight:
        // Medium Knight -- 2H Weapon
        u.description = "Medium Knight";
        u.speed += MediumArmorSpeed + TwoHandWeaponSpeed;
        u.attack += TwoHandWeaponAttack;
        u.damage += TwoHandWeaponDamage;
        u.defense += MediumArmorDefense;
        u.armor += MediumArmor;
        break;
    case LightInfantry:
        // Light Infantry -- Weapon & shield
        u.description = "Light Infantry";
        u.speed += LightArmorSpeed + OneHandWeaponSpeed + ShieldSpeed;
        u.attack += OneHandWeaponAttack;
        u.damage += OneHandWeaponDamage;
        u.defense += LightArmorDefense + ShieldDefense;
        u.armor += LightArmor + ShieldArmor;
        break;
    case LightKnight:
        // Light Knight -- Polearm
        u.description = "Light Polearm";
        u.speed = BaseSpeed + TwoHandWeaponSpeed;
        u.attack += TwoHandWeaponAttack;
        u.damage += TwoHandWeaponDamage;
        u.defense += LightArmorDefense;
        u.armor += LightArmor;
        break;
    case DualWeapons:
        // Light Knight -- Dual weapons
        u.description = "Dual Weapons";
        u.speed = BaseSpeed + StabbyWeaponSpeed;
        u.attack += StabbyWeaponAttack;
        u.damage += StabbyWeaponDamage;
        u.defense += LightArmorDefense;
        u.armor += LightArmor;
        break;
     default:
        assert( false );
        break;
    }
}


int Max( const int a, const int b )
{
    return ( a > b ) ? a : b;
}


void PrintHelp( void )
{
    cout << endl;
    cout << "combat3d OPTIONS" << endl;
    cout << "    --help         Print help and exit" << endl;
    cout << "    --number N     Number of fights" << endl;
    cout << "    --same         Generate Units of the same type" << endl;
    cout << "    --verbose      Extra messages" << endl;
    cout << endl;
}


void PrintUnit( const Unit& u )
{
    cout << endl;
    cout << u.name << " (" << u.description << ")" << endl;
    cout << "  Speed   : " << u.speed << endl;
    cout << "  Attack  : " << u.attack << endl;
    cout << "  Damage  : " << u.damage << endl;
    cout << "  Defense : " << u.defense << endl;
    cout << "  Armor   : " << u.armor << endl;
    cout << "  Health  : " << u.health << endl;
    cout << endl;
}


void PrintWins( const Unit& u )
{
    cout << u.name << " (" << u.description << ") had " << u.wins
         << " wins."<< endl;
}


int RandInt( int a, int b )
{
    static random_device generator;

    if (a > b) {
        int t = b;
        b = a;
        a = t;
    }

    uniform_int_distribution<int> distribution(a, b);
    return distribution(generator);
}


int Randomize( const Options& opts, Unit& u )
{
    (void)opts;
    int rating = 0;     // TODO Randomization rating

    u.speed = BaseSpeed;
    u.attack = BaseAttack;
    u.damage = BaseDamage;
    u.defense = BaseDefense;
    u.armor = BaseArmor;

    int type = None;
    int choice = RandInt( 1, 100 );
    if (choice <= 10)
        type = HeavyInfantry;
    else if (choice <=20)
        type = HeavyKnight;
    else if (choice <= 40)
        type = MediumInfantry;
    else if (choice <= 60)
        type = MediumKnight;
    else if (choice <= 80)
        type = LightInfantry;
    else if (choice <= 90)
        type = LightKnight;
    else if (choice <= 100)
        type = DualWeapons;
    else
        type = None;

    InitUnit( type, u );

    // TODO calculate rating

    return rating;
}


int Step( int n )
{
    int d1, d2, d3;
    GetDice( n, d1, d2, d3 );
    return RandInt( 1, d1 ) + RandInt( 1, d2 ) + RandInt( 1, d3 );
}


//
//
//
int main( int argc, char **argv )
{
    Options opts;
    GetOptions( argc, argv, opts );

    opts.Print();

    if ( opts.printHelp ) {
        PrintHelp();
        return 0;
    }

    Unit u1( "Aardvark", "Generic warrior" );
    Unit u2( "Baboon", "Generic warrior" );

    if ( opts.type == NoUnitType ) {
        (void)Randomize( opts, u1 );
        (void)Randomize( opts, u2 );
    }

    for ( int n = 0; n < opts.number; n++ )
        Fight( opts, u1, u2 );

    PrintWins( u1 );
    PrintWins( u2 );

    return 0;
}

