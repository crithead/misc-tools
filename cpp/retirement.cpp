//
// Retirement estimator
//

#include <iostream>
#include <sstream>
#include <vector>

//
// Calculate the Social Security payout total based on the first year.
//
// TODO : Figure out how to add the effects of inflation
// TODO : Print 0-fill month
//

struct ssitem {
    int age;        // Age to start collecting
    int percent;    // Perecent of full benefits
};

const struct ssitem SSAGEPCTTAB[] = {
    { 62,  70 },
    { 63,  75 },
    { 64,  80 },
    { 65,  87 },
    { 66,  93 },
    { 67, 100 },
    { 68, 108 },
    { 69, 116 },
    { 70, 124 },
    {  0,   0 }
};

const int MIN_SS = 62;
const int MAX_SS = 70;

// Full Benefit in $/month
const int MONTHLY = 1000;

// Annual inflation in Percent
const int INFLATION = 2;

const int MIN_AGE = 62;
const int MAX_AGE = 99;
const int NUM_YEARS = MAX_AGE - MIN_AGE + 1;
const int MAX_LIFE = 12 * NUM_YEARS;

static void social_security(void);

struct rec {
    int age;
    int *total;
    rec(int a, int* t) : age(a), total(t) {}
    rec(const rec& p) : age(p.age), total(p.total) {}
};

void allocate_records(std::vector<rec>& v)
{
    for (int y = MIN_SS; y <= MAX_SS; y++) {
        int *t = new int[MAX_LIFE];
        v.push_back(rec(y, t));
    }
}

void free_records(std::vector<rec>& v)
{
    for (auto r : v)
        delete r.total;
}

int find_percent(int start_age)
{
    if (start_age < MIN_AGE)
        return 0;
    if (start_age > MAX_AGE)
        return SSAGEPCTTAB[MAX_AGE].percent;

    for (int i = 0; SSAGEPCTTAB[i].age; i++) {
        if (start_age == SSAGEPCTTAB[i].age)
            return SSAGEPCTTAB[i].percent;
    }

    return 0;
}

void fill(int monthly, int start_age, int *month)
{
    int f = find_percent(start_age);
    std::cout << "percent = " << f << std::endl;
    for (int y = 0; y < NUM_YEARS; y++) {
        for (int m = 0; m < 12; m++) {
            int i = y * 12 + m;
            if (y < start_age - MIN_AGE) {
                month[i] = 0;
            }
            else {
                int prev_month = i ? month[i - 1] : 0;
                month[i] = prev_month + f * monthly / 100;
            }
        }
    }
}

std::string printable(int month_after_min)
{
    std::stringstream ss;
    int m = month_after_min % 12;
    int y = MIN_AGE + (month_after_min / 12);
    ss << y << '.' << (m + 1);
    return ss.str();
}


void print_records(const std::vector<rec>& v)
{
    // Header
    std::cout << "Month";
    for (auto r : v)
        std::cout << '\t' << r.age;
    std::cout << std::endl;

    // Rows
    for (int m = 0; m < MAX_LIFE; m++) {
        std::cout << printable(m);
#if 1
        for (size_t r = 0; r < v.size(); r++)
            std::cout << '\t' << v[r].total[m];
#else
        for (auto r : v)
            std::cout << '\t' << r.total[m];
#endif
        std::cout << std::endl;
    }
}


void social_security(void)
{
    std::vector<rec> v;
    allocate_records(v);

    for (auto r : v) {
        fill(MONTHLY, r.age, r.total);
    }

    print_records(v);

    free_records(v);
}


//
// Run the sections
//
int main(int argc, char **argv)
{
    social_security();
}

