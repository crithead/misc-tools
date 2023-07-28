//
// Master of Magic Combat Simulator (as best I can recall)
//

#include <cassert>
#include <cstdarg>
#include <cstdio>
#include <iomanip>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct options;
class unit;

static void msg(const char *fmt, ...);
static void combat(const options&);
static int d10(void);
static void delete_units(vector<unit *> *);
static void fight(unit&, unit&);
static vector<unit *> *generate_units(int, bool);
static string make_name(void);
static int num_survivors(vector<unit *> *);
static void print_help(void);
static int roll(int, int);
static void set_options(int, char**, options&);

struct options
{
    options() : debug(false), fight_till_dead(false), print_help(false),
            randomize(false), team_size(1000), verbose(false) {}

    void validate(void) const {
        assert(team_size > 0);
    }

    bool debug;
    bool fight_till_dead;
    bool print_help;
    bool randomize;
    size_t team_size;
    bool verbose;
};

class unit
{
public:
    static constexpr int MAX_HEALTH = 10;

    unit(const string& n = "Unit", int at = 1, int df = 1, int dm = 1,
         int ar = 1) : name(n), attack_power(at), attack_bonus(0),
         defense_power(df), defense_bonus(0), damage_power(dm),
         damage_bonus(0), armor_power(ar), armor_bonus(0), health(MAX_HEALTH)
         {}

    unit(const unit& u) : name(u.name), attack_power(u.attack_power),
         attack_bonus(u.attack_bonus), defense_power(u.defense_power),
         defense_bonus(u.defense_bonus), damage_power(u.damage_power),
         damage_bonus(u.damage_bonus), armor_power(u.armor_power),
         armor_bonus(u.armor_bonus), health(u.health) {}

    ~unit() {}

    string to_str(void) {
        stringstream ss;
        ss << name << ": "
           << health << '/' << MAX_HEALTH << ", "
           << attack_power << '/' << attack_bonus << ", "
           << defense_power << '/' << defense_bonus << ", "
           << damage_power << '/' << damage_bonus << ", "
           << armor_power << '/' << armor_bonus;
        return ss.str();
    }

    int roll_attack(void) {
        return roll(attack_power, attack_bonus);
    }

    int roll_defense(void) {
        return roll(defense_power, defense_bonus);
    }

    int roll_damage(void) {
        return roll(damage_power, damage_bonus);
    }

    int roll_armor(void) {
        return roll(armor_power, armor_bonus);
    }

    void modify_health(int amount = 0) {
        health += amount;
        if (health < 0)
            health = 0;
    }

    bool is_alive(void) const {
        return health > 0;
    }

//private:
    string name;
    int attack_power;
    int attack_bonus;
    int defense_power;
    int defense_bonus;
    int damage_power;
    int damage_bonus;
    int armor_power;
    int armor_bonus;
    int health;
};

static bool _messages_on;

void combat(const options& opts)
{
    vector<unit *> *team_a = generate_units(opts.team_size, opts.randomize);
    assert( team_a != nullptr );
    assert( team_a->size() == opts.team_size );
    vector<unit *> *team_b = generate_units(opts.team_size, opts.randomize);
    assert( team_b != nullptr );
    assert( team_b->size() == opts.team_size );

    size_t fighter_a = 0;
    size_t fighter_b = 0;
    while (fighter_a < team_a->size() && fighter_b < team_b->size()) {
        unit *fa = team_a->at(fighter_a);
        assert( fa != nullptr );
        unit *fb = team_b->at(fighter_b);
        assert( fb != nullptr );

        fight( *fa, *fb );

        if (opts.fight_till_dead) {
            if (! team_a->at(fighter_a)->is_alive() )
                fighter_a++;
            if (! team_b->at(fighter_b)->is_alive() )
                fighter_b++;
        }
        else {  // PAIR_THEM_UP
            fighter_a++;
            fighter_b++;
        }
    }

    cout << "Team A (" << num_survivors(team_a) << ')' << endl;
    if (opts.verbose) {
        for (auto u : *team_a)
            cout << u->to_str() << endl;
    }
    cout << "Team B (" << num_survivors(team_b) << ')' << endl;
    if (opts.verbose) {
        for (auto u : *team_b)
            cout << u->to_str() << endl;
    }

    delete_units(team_a);
    delete_units(team_b);
}

int d10(void)
{
    static random_device generator;
    static uniform_int_distribution<int> distribution(1, 10);
    return distribution(generator);
}

void delete_units(vector<unit *> *units)
{
    if (units == nullptr)
        return;
    for (size_t i = 0; i < units->size(); i++)
        delete units->at(i);
    delete units;
}

void fight(unit& one, unit& two)
{
    msg("%s: one %s, two %s", __FUNCTION__, one.name.c_str(), two.name.c_str());

    while (one.is_alive() && two.is_alive()) {
        int value = one.roll_attack() - two.roll_defense();
        if (value >= 0) {
            value = one.roll_damage() - two.roll_armor();
            if (value > 0)
                two.modify_health(-value);
        }
        if (!two.is_alive())
            break;
        value = two.roll_attack() - one.roll_defense();
        if (value >= 0) {
            value = two.roll_damage() - one.roll_armor();
            if (value > 0)
                one.modify_health(-value);
        }
    }
}

vector<unit *> *generate_units(int num_units, bool randomize)
{
    msg("%s: num_units %d, randomize %c", __FUNCTION__, num_units,
        randomize ? 't' : 'f');
    assert( num_units > 0 );

    vector<unit *> *units = new vector<unit *>();
    assert( units != nullptr );

    for (int i = 0; i < num_units; i++) {
        int at, df, dm, ar;
        if (randomize) {
            at = 3 + d10() / 2;     // 3 - 7
            df = 3 + d10() / 2;
            dm = 3 + d10() / 2;
            ar = 3 + d10() / 2;
        }
        else {
            at = df = dm = ar = 5;
        }
        unit *u = new unit(make_name(), at, df, dm, ar);
        assert( u != nullptr );
        units->push_back(u);
    }

    msg("%s: units.size() %d", __FUNCTION__, units->size());
    return units;
}

string make_name(void)
{
    static int name_count = 0;

    stringstream ss;
    ss << setfill('0') << setw(4) << ++name_count;
    return ss.str();
}

void msg(const char *fmt, ...)
{
    if (!_messages_on)
        return;

    va_list ap;
    va_start(ap, fmt);
    vprintf(fmt, ap);
    putchar('\n');
    va_end(ap);
}

int num_survivors(vector<unit *> *units)
{
    int n = 0;
    for (auto u : *units) {
        if (u->is_alive())
            n++;
    }
    return n;
}

void print_help(void)
{
    cout << "momcombat [-dfhrv] [-s TEAMSIZE]" << endl;
    cout << "    -d, -debug     Enable debugging messages" << endl;
    cout << "    -f             Fight Till Dead mode" << endl;
    cout << "    -h, -help      Print usage and exit" << endl;
    cout << "    -s N           Set the number of units per team" << endl;
    cout << "    -v, -verbose   Enable verbose output" << endl;
}

int roll(int power, int bonus)
{
    int value = 0;
    for( int i = 0; i < power; i++) {
        if (d10() + bonus >= 5)
            value += 1;
    }
    return value;
}

void set_options(int argc, char **argv, options& opts)
{
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] != '-')
            continue;
        if (argv[i][1] == 'd') {
            opts.debug = true;
            _messages_on = true;
        }
        else if (argv[i][1] == 'f') {
            opts.fight_till_dead = true;
        }
        else if (argv[i][1] == 'h') {
            opts.print_help = true;
        }
        else if (argv[i][1] == 'r') {
            opts.randomize = true;
        }
        else if (argv[i][1] == 's') {
            opts.team_size = atoi(argv[++i]);
        }
        else if (argv[i][1] == 'v') {
            opts.verbose = true;
        }
    }

    opts.validate();
}

//
// MoM Combat
//
int main(int argc, char **argv)
{
    options opts;
    set_options(argc, argv, opts);

    if (opts.print_help) {
        print_help();
        return 0;
    }

    combat(opts);

    return 0;
}

