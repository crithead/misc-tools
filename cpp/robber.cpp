//
// Robber
// You are a professional robber planning to rob houses along a street. Each
// house has a certain amount of money stashed, the only constraint stopping
// you from robbing each of them is that adjacent houses have security system
// connected and it will automatically contact the police if two adjacent
// houses were broken into on the same night.
//
// Given a list of non-negative integers representing the amount of money of
// each house, determine the maximum amount of money you can rob tonight
// without alerting the police.
//

#include <iostream>
#include <random>
#include <vector>

// number of houses with a stash
static const int STASH_SIZE = 12;

//
// Return random integer betweem a and b, inclusive.
//
static int RandInt( int a, int b )
{
	static std::random_device generator;

	if (a > b) {
		int t = b;
		b = a;
		a = t;
	}

	std::uniform_int_distribution<int> distribution(a, b);
	return distribution(generator);
}

// Return the larger of two integers.
//
static int Max( int a, int b )
{
	if ( a >= b )
		return a;
	else
		return b;
}

//
// Print the values in a vector of int.
//
static void PrintVector( std::vector<int>& v )
{
	for ( size_t i = 0; i < v.size(); i++ )
		std::cout << '\t' << v[i];
	std::cout << std::endl;
}

//
// Initialze the cash stashed in each house on the street with a random
// amount betweem $10 and $99.
//
static void InitStash( std::vector<int>& stash, int num_stashes )
{
	stash.resize( num_stashes );
	for ( int i = 0; i < num_stashes; i++ )
		stash[ i ] = RandInt( 10, 99 );
}

//
// Going from house to house, the strategy is to rob the better of the first
// two houses, then at each house select the better option between adding this
// house's take to that of the next to last house or staying with the take from
// the last house.  The list 'taken' is a running total of the cash stolen and
// the last value will be the best total after working all the way down the
// street.
//
static int GoRobbing( std::vector<int>& stash )
{
	int value = 0;

	if ( stash.size() == 0 ) {
		value = 0;
	} else if ( stash.size() == 1 ) {
		value = stash[0];
	} else if ( stash.size() == 2 ) {
		value = Max( stash[0], stash[1] );
	} else {
		std::vector<int> taken( stash.size(), 0 );
		taken[0] = stash[0];
		taken[1] = Max( stash[0], stash[1] );
		for (size_t i = 2; i < stash.size(); i++ )
			taken[i] = Max( taken[i - 2] + stash[i], taken[i - 1] );
		value = taken[ taken.size() - 1 ];
		PrintVector( taken );
	}

	return value;
}

//
//
//
int main( int argc, char **argv )
{
	std::vector<int> stash( STASH_SIZE );
	InitStash( stash, STASH_SIZE );
	PrintVector( stash );

	int bestTake = GoRobbing( stash );
	std::cout << "Best take " << bestTake << std::endl;

	return 0;
}

