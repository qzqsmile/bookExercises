#include<string>
#include<algorithm>
#include<stdexcept>
#include<cstdlib>
#include<iostream>
#include<vector>
#include<map>
#include<list>

using std::logic_error;
using std::domain_error;
using std::vector;
using std::string;
using std::cout;
using std::cin;
using std::map;
using std::endl;
using std::istream;
using std::list;

typedef vector<string> Rule;
typedef vector<Rule>Rule_collection;
typedef map<string,Rule_collection> Grammar;

Grammar read_grammar(istream& in);
list<string> gen_sentence(const Grammar& g);
void gen_aux(const Grammar& g, const string& word, list<string>& ret);
bool bracketed(const string& s);
bool space(char c);
bool not_space(char c);
vector<string> split(const string& str);
int nrand(int n);

int main()
{
	list<string> sentence = gen_sentence(read_grammar(cin));

	list<string> :: const_iterator it = sentence.begin();
	if (!sentence.empty()){
		cout << *it;
		++it;
	}

	while (it != sentence.end()){
		cout << " " << *it;
		++it;
	}

	cout << endl;

	return 0;
}


Grammar read_grammar(istream& in)
{
	Grammar ret;
	string line;

	while (getline(in, line)){
		vector<string> entry = split(line);

		if (!entry.empty())
			ret[entry[0]].push_back(Rule(entry.begin() + 1, entry.end()));
	}

	return ret;
}

list<string> gen_sentence(const Grammar& g)
{
	list<string> ret;
	gen_aux(g, "<sentence>", ret);
	return ret;
}

bool bracketed(const string& s)
{
	return s.size() > 1 && s[0] == '<' && s[s.size() - 1] == '>';
}

void gen_aux(const Grammar& g, const string& word, list<string>& ret)
{
	if(!bracketed(word)){
		ret.push_back(word);
	}else{
		Grammar :: const_iterator it = g.find(word);
		if (it == g.end())
			throw logic_error("empty rule");
		const Rule_collection& c = it -> second;

		const Rule& r = c[nrand(c.size())];

		for(Rule::const_iterator i = r.begin(); i != r.end(); ++i)
			gen_aux(g, *i, ret);
	}
}

int nrand(int n)
{
	if (n <= 0 || n > RAND_MAX)
		throw domain_error("Argument to nrand is out of range");

	const int bucket_size = RAND_MAX / n;
	int r;

	do r = rand() / bucket_size;
	while (r >= n);

	return r;
}

bool space(char c)
{
	return isspace(c);
}

bool not_space(char c)
{
	return !isspace(c);
}

vector<string> split(const string& str)
{
	typedef string::const_iterator iter;
	vector<string> ret;

	iter i = str.begin();
	while(i != str.end()){
		i = find_if(i, str.end(), not_space);
		iter j = find_if(i, str.end(), space);

		if(i != str.end())
			ret.push_back(string(i, j));
		i = j;
	}

	return ret;
}
