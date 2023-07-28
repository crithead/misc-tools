//
// Draw blobby areas
//

#include <cassert>
#include <cstdarg>
#include <cstring>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

struct options;
struct point;

static int Abs(int);
static void Draw(std::vector<point>&);
static void DrawLine(char *, int, int, int, int, char);
static void Fill(char *, char);
static void Generate(const options&, std::vector<point>&);
static bool InBounds(int, int);
static int ToIndex(int, int);
static void Msg(const char *fmt, ...);
static void Print(char *);
static void PrintHelp(void);
static int Roll(int, int);
static void SetOptions(int, char**, options&);
static int Sign(int);

// Program options
struct options
{
    options() : printHelp(false), verbose(false) {}

    void validate(void) const {
    }

    bool printHelp;
    bool verbose;
};

// A 2D point coordinate pair
struct point {
    point(int x0, int y0): x(x0), y(y0) {}
    point(const point& p): x(p.x), y(p.y) {}
    int x;
    int y;
};

static const int WIDTH = 64;
static const int HEIGHT = 64;

static bool _messages_on;

// Compute absolute value of Z
static int Abs(int z)
{
    return z >= 0 ? z : -z;
}

// Compute the sign of Z: {-1, 0, 1}
static int Sign(int z)
{
    int value = 0;
    if (z > 0)
        value = 1;
    else if (z < 0)
        value = -1;
    return value;
}

// Convert x,y coordinates to an array index
int ToIndex(int x, int y)
{
    return y * WIDTH + x;
}

// Return true if x, y is on the grid
bool InBounds(int x, int y)
{
    return x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT;
}

// Draw a line on the grid from x0, y0 to x1, y1 with character T
void DrawLine(char *grid, int x1, int y1, int x2, int y2, char t)
{
    assert( InBounds(x1, y1) );
    assert( InBounds(x2, y2) );

    Msg("Line: %d, %d -> %d, %d", x1, y1, x2, y2);

    //int steps = 2 * (HEIGHT > WIDTH ? HEIGHT : WIDTH);
    int x = x1;
    int y = y1;
    int dx = x2 - x1;
    int dy = y2 - y1;
    while (Abs(dx) > 0 || Abs(dy) > 0) {
        dx = x2 - x;
        dy = y2 - y;
        if (dx == 0) {
            y += Sign(dy);
        }
        else if (dy == 0) {
            x += Sign(dx);
        }
        else if (Abs(dx) > Abs(dy)) {
            x += Sign(dx);
        }
        else {
            y += Sign(dy);
        }
        grid[ ToIndex(x, y) ] = t;

        Msg("x %d, y %d, dx %d, dy %d", x, y, dy, dy);
        //if (--steps < 0)
        //    break;
    }
}

// Fill the grid with Ts
void Fill(char *grid, char t)
{
    memset(grid, static_cast<int>(t), HEIGHT * WIDTH * sizeof(char));
}

// Fill the center of the grid with Ts, stopping at Ts on the edges
// Recursive fill of non-T points
void FillAdjacent(char *grid, int x, int y, char t)
{
    if (!InBounds(x, y) || grid[ ToIndex(x, y)] == t)
        return;

    grid[ ToIndex(x, y) ] = t;
    FillAdjacent(grid, x - 1, y, t);
    FillAdjacent(grid, x + 1, y, t);
    FillAdjacent(grid, x, y - 1, t);
    FillAdjacent(grid, x, y + 1, t);
}

// Return the sum of N random numbers in the range of 1 to S
int Roll(int n, int s)
{
#if 1
    static random_device generator;
    uniform_int_distribution<int> distribution(1, s);
    int v = 0;
    for (int i = 0; i < n; i++)
        v += distribution(generator);
#else
    int v = 20;
#endif
    return v;
}

// Generate a point in each of the eight radial directions from the center
void Generate(const options& opts, std::vector<point>& points)
{
    const int cx = WIDTH / 2;
    const int cy = HEIGHT / 2;
    const int C = 3;
    const int D = 3;
    const int S = 10;

    Msg("Center: %d, %d", cx, cy);

    // Counter clockwise, from the x-axis
    int d = Roll(C, S);
    points.push_back(point(cx + d, cy));

    d = Roll(D, S);
    points.push_back(point(cx + d, cy + d));

    d = Roll(C, S);
    points.push_back(point(cx, cy + d));

    d = Roll(D, S);
    points.push_back(point(cx - d, cy + d));

    d = Roll(C, S);
    points.push_back(point(cx - d, cy));

    d = Roll(D, S);
    points.push_back(point(cx - d, cy - d));

    d = Roll(C, S);
    points.push_back(point(cx, cy - d));

    d = Roll(D, S);
    points.push_back(point(cx + d, cy - d));
}

// Draw the blob
void Draw(std::vector<point>& points)
{
    //const char T = '#';
    char T = '*';

    char grid[HEIGHT * WIDTH];

    Msg("Grid: %d x %d", WIDTH, HEIGHT);

    Msg("Set background");
    Fill(grid, '-');

    for (size_t i = 0; i < points.size(); i++) {
        size_t j = (i + 1) % points.size();
        Msg("i %d, j %d", i, j);
        point& p1 = points[i];
        point& p2 = points[j];
        DrawLine(grid, p1.x, p1.y, p2.x, p2.y, T);
    }

    // Fill the grid from the center outward
    Msg("Fill blob");
    FillAdjacent(grid, WIDTH / 2, HEIGHT / 2, T);

    Print(grid);
}

// Conditionally print a message to the console
void Msg(const char *fmt, ...)
{
    if (!_messages_on)
        return;

    va_list ap;
    va_start(ap, fmt);
    vprintf(fmt, ap);
    putchar('\n');
    va_end(ap);
}

// Print the grid
void Print(char *grid)
{
    Msg(__func__);
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++)
            cout << grid[ ToIndex(x, y) ];
        cout << endl;
    }
}

// Print helpful information about the program
void PrintHelp(void)
{
    cout << "blobs [-hv]" << endl;
    cout << "    -h, -help      Print usage and exit" << endl;
    cout << "    -v, -verbose   Enable verbose output" << endl;
}

// Parse command line arguments into an options structure
void SetOptions(int argc, char **argv, options& opts)
{
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] != '-')
            continue;
        else if (argv[i][1] == 'h') {
            opts.printHelp = true;
        }
        else if (argv[i][1] == 'v') {
            opts.verbose = true;
            _messages_on = true;
        }
    }

    opts.validate();
}

// 1. Get command line options
// 2. Generate a outline of the blob
// 3. Draw the blob
int main(int argc, char **argv)
{
    options opts;
    SetOptions(argc, argv, opts);

    if (opts.printHelp) {
        PrintHelp();
        return 0;
    }

    std::vector<point> points;
    Generate(opts, points);
    Draw(points);

    return 0;
}
