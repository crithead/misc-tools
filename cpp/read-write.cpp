// Read-Write number from/to stdin
#include <cmath>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

static double calc_mean( std::vector<double>& );
static double calc_median( std::vector<double>& );
static double calc_stdev( std::vector<double>&, double );
static double find_min( std::vector<double>& );
static double find_max( std::vector<double>& );

int main( void )
{
    using namespace std;
    vector<double> data;

    copy( istream_iterator<double>( cin ),
          istream_iterator<double>(),
          back_inserter( data ) );


    sort( data.begin(), data.end() );

    copy( data.begin(), data.end(),
          ostream_iterator<double>( cout, " " ) );
    cout << endl;

    double value  = 0.0;
    value = find_min( data );
    cout << "Min   : " << value << endl;
    double mean = calc_mean( data );
    value = calc_stdev( data, mean );
    cout << "Mean  : " << mean << " \u00B1" << value << endl;
    value = calc_median( data );
    cout << "Median: " << value << endl;
    value = find_max( data );
    cout << "Max   : " << value << endl;

    return 0;
}

double calc_mean( std::vector<double>& numbers )
{
    double total = 0.0;
    double size = static_cast<double>( numbers.size() );
    for ( std::vector<double>::const_iterator i = numbers.begin();
          i != numbers.end(); ++i )
        total += *i;
    return total / size;
}

// numbers must be sorted
double calc_median( std::vector<double>& numbers )
{
    double median = 0.0;
    size_t size = numbers.size();
    if ( size % 2 )
        median = numbers[ size / 2 ];
    else
        median = ( numbers[ size / 2 ] + numbers[ size / 2 + 1] ) / 2.0;

    return median;
}

double calc_stdev( std::vector<double>& numbers, double mean )
{
    const double size = static_cast<double>( numbers.size() );
    double sum = 0.0;
    for ( size_t i = 0; i < size; i++ ) {
        double x = numbers[ i ] - mean;
        sum += x * x;
    }
    return std::sqrt( sum / (size - 1) );
}

double find_min( std::vector<double>&  numbers)
{
    double value = 0.0;
    if ( numbers.size() > 0 )
        value = numbers[ 0 ];
    return value;
}

double find_max( std::vector<double>& numbers )
{
    double value = 0.0;
    if ( numbers.size() > 0 )
        value = numbers[ numbers.size() - 1 ];
    return value;
}

