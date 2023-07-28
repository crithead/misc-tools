//#! /usr/bin/env python3
// # x = x0 + v0 cos A t
// # y = y0 + v0 sin A t - (g / 2) t^2
//
// TODO implement parse_argv()
//
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <string>

static const float DEFAULT_ANGLE = 45.0f;
static const float DEFAULT_VELOCITY = 100.0f;

static const float GRAVITY = 9.8f;
static const double PI = 4.0 * std::atan(1);

static const double X0 = 0;
static const double Y0 = 0;


// Convert from degrees to radians.
static inline double to_radians(double degrees)
{
    return (degrees * PI) / 180.0;
}


// Calculate the distance a projectile travels before hitting the ground.
static double calc_position(double velocity, double angle)
{
    float x = X0 + (2.0 * velocity * velocity * std::cos(to_radians(angle)) *
            std::sin(to_radians(angle))) / GRAVITY;
    return x;
}


// Calculate the time a projectile takes to hit the ground.
static double calc_time(double velocity, double angle, double final_position)
{
    return (final_position - X0) / (velocity * std::cos(to_radians(angle)));
}

#if 0
// Calculate the time a projectile takes to hit the ground.
static double calc_time_2(double velocity, double angle)
{
    return 2 * velocity * std::sin(to_radians(angle)) / GRAVITY;
}
#endif //0

static void print_help(void)
{
    std::cout
        << "Calculate the distance a projectile travels." << std::endl
        << "    -a      Angle in degrees" << std::endl
        << "    -h      Print a usage message" << std::endl
        << "    -t      Output a table varying the angle" << std::endl
        << "    -v      Velocity in m/s" << std::endl;
}

// parser = ArgumentParser(description='Calculate the distance a projectile'
//         ' travels.')
// parser.add_argument('-a', '--angle', action='store', type=int, default=45,
//         help='Angle in degrees.')
// parser.add_argument('-v', '--velocity', action='store', type=int, default=10,
//         help='velocity in m/s')
// parser.add_argument('-t', '--table', action='store_true', default=False,
//         help='Print a table')
// args = parser.parse_args()

struct arguments {
    arguments() : angle(DEFAULT_ANGLE), velocity(DEFAULT_VELOCITY),
            help(false), table(false) {}

    arguments(int argc, char **argv) : angle(DEFAULT_ANGLE),
            velocity(DEFAULT_VELOCITY), help(false), table(false)
    {
        for (int i = 1; i < argc; i++) {
            if (!std::strncmp("-a", argv[i], 3))
                this->angle = std::strtof(argv[++i], 0);
            else if (!std::strncmp("-v", argv[i], 3))
                this->velocity = std::strtof(argv[++i], 0);
            else if (!std::strncmp("-h", argv[i], 3))
                this->help = true;
            else if (!std::strncmp("-t", argv[i], 3))
                this->table = true;
            else
                std::cerr << "Unknown switch: " << argv[i] << std::endl;
        }
    }

    float angle;
    float velocity;
    bool help;
    bool table;
};



int main(int argc, char **argv) 
{

    try {
        arguments args(argc, argv);
        double t, x;

        if (args.help) {
            print_help();
        } else if (args.table) {
            std::cout << "Initial velocity " << args.velocity << "m/s" << std::endl;
            std::cout << "      Angle     Distance  Time" << std::endl;
            for (float angle = 10; angle < 90; angle += 5) {
                x = calc_position(args.velocity, angle);
                t = calc_time(args.velocity, angle, x);
                std::cout << std::fixed;
                std::cout << std::setw(12);
                std::cout << std::setprecision(1);
                std::cout << angle << "\u00B0" << '\t';
                std::cout << x << '\t';
                std::cout << t << std::endl;
            }
        } else {
            x = calc_position(args.velocity, args.angle);
            t = calc_time(args.velocity, args.angle, x);
            std::cout << "A projectile launched at an angle of " <<
                    args.angle << "\u00B0 from horizontal" << '\n' <<
                    "with an initial velocity of " << args.velocity <<
                    " m/s will hit the ground" << '\n' << x << "m from its" <<
                    " launch position " << t << " seconds after launch." <<
                    std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}

