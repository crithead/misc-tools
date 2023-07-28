//
// Markov chain algorithm from "The Practice of Programming" by Kernigan & Pike
// C++ version
//
#include <cstdlib>
#include <ctime>
#include <deque>
#include <map>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

typedef deque<string> Prefix;
static map<Prefix, vector<string> > statetab; // prefix -> suffixes

static const int MAXGEN = 1000;
static const int NPREF = 2;
static const string NONWORD = "\n";

// add: add word to tsuffix list, update prefix
void add(Prefix& prefix, const string &s)
{
	if (prefix.size() == static_cast<size_t>(NPREF)) {
		statetab[prefix].push_back(s);
		prefix.pop_front();
	}
	prefix.push_back(s);
}


// build: read input wrods, build state table
void build(Prefix& prefix, istream& in)
{
	string buf;
	while (in >> buf)
		add(prefix, buf);
}


// generate: produce output, one word per line
void generate(int nwords)
{
	Prefix prefix;
	int i;

	for (i = 0; i < NPREF; i++)     // reset initial prefix
		add(prefix, NONWORD);

	for (i = 0; i < nwords; i++) {
		vector<string>& suf = statetab[prefix];
		const string& w = suf[rand() % suf.size()];
		if (w == NONWORD)
			break;
		cout << w << "\n";
		prefix.pop_front();         // advance
		prefix.push_back(w);
	}
}


int main(void)
{
	srand(time(NULL));

	int nwords = MAXGEN;
	Prefix prefix;                      // current input prefix

	for (int i = 0; i < NPREF; i++)     // set up initial prefix
		add(prefix, NONWORD);
	build(prefix, cin);
	add(prefix, NONWORD);
	generate(nwords);
	return 0;
}
