#include<iostream>
#include<ctime>
#include<string>
#include<vector>
#include<iomanip>
#include<stdexcept>
#include<ios>
#include<cstdlib>
#include<algorithm>

#define N 10000

using std::istream;
using std::cin;
using std::cout;
using std::domain_error;
using std::endl;
using std::max;
using std::setprecision;
using std::sort;
using std::streamsize;
using std::string;
using std::vector;
using std::srand;
using std::time;
using std::rand;

struct Student_info {
	std::string name;
	double midterm, final;	
	std::vector < double >homework;
};
bool compare(const Student_info &, const Student_info &);
bool fgrade(const Student_info& s);
std::istream & read(std::istream &, Student_info  &);
std::istream & read_hw(std::istream &, std::vector < double >&);
double grade(double, double, double);
double grade(double, double, const std::vector < double >&);
double grade(const Student_info &);
double median(std::vector < double >);
vector<Student_info> extract_fails(vector<Student_info>& students);
void init_test(vector<Student_info>& students, int n);
double random_num(int i);

int main()
{
	vector < Student_info > students;
	vector < Student_info > fail;
	Student_info record;
	string::size_type maxlen = 0;

    students.resize(N);
	init_test(students, N);
    for (int i = 0; i < students.size(); i++)
    {
        maxlen = max(maxlen, students[i].name.size());     
    }
	sort(students.begin(), students.end(), compare);
	fail =	extract_fails(students);

	for (vector < Student_info >::size_type i = 0;
	     i != students.size(); ++i) {
		cout << students[i].name << string(maxlen + 1 -
						   students[i].name.size(),
						   ' ');
		try {
			double final_grade = grade(students[i]);
			streamsize prec = cout.precision();
			cout << setprecision(3) << final_grade <<
			    setprecision(prec);
		} catch(domain_error e) {
			cout << e.what();
		}
		cout << endl;
	}

	cout << "The fail students grade is" << endl;

	for (vector<Student_info>::size_type i = 0; i != fail.size(); ++i)
	{
		cout << fail[i].name << string(maxlen + 1 - fail[i].name.size(),' ');

		double final_grade = grade(fail[i]);
		streamsize prec = cout.precision();
		cout << setprecision(3) << final_grade <<
			setprecision(prec) << endl;
	}

	return 0;
}

bool compare(const Student_info & x, const Student_info & y)
{
	return x.name < y.name;
}

istream & read(istream & is, Student_info & s)
{
	is >> s.name >> s.midterm >> s.final;
	read_hw(is, s.homework);

	return is;
}

istream & read_hw(istream & in, vector < double >&hw)
{
	if (in) {
		hw.clear();

		double x;
		while (in >> x)
			hw.push_back(x);

		in.clear();
	}

	return in;
}

double grade(double midterm, double final, double homework)
{
	return 0.2 * midterm + 0.4 * final + 0.4 * homework;
}

double grade(double midterm, double final, const std::vector < double >&hw)
{
	if (hw.size() == 0)
		throw domain_error("Student has done no homework");
	return grade(midterm, final, median(hw));
}

double grade(const Student_info & s)
{
	return grade(s.midterm, s.final, s.homework);
}

double median(std::vector < double >vec)
{
	typedef vector < double >::size_type vec_sz;

	vec_sz size = vec.size();
	if (0 == size)
		throw domain_error("median of an empty vector");

	sort(vec.begin(), vec.end());

	vec_sz mid = size / 2;

	return size % 2 == 0 ? (vec[mid] + vec[mid - 1]) / 2 : vec[mid];
}


bool fgrade(const Student_info& s)
{
	return grade(s) < 60;
}

// vector version
vector<Student_info> extract_fails(vector<Student_info>& students)
{
	vector<Student_info> fail;
	vector<Student_info> :: iterator iter = students.begin();

	while(iter != students.end()){
		if(fgrade(*iter)){
			fail.push_back(*iter);
			iter = students.erase(iter);	
		}else
			++iter;
	}
	
	return fail;
}

void init_test(vector<Student_info>& students, int n)
{
	for (int i = 0; i < n; i++){
		students[i].name.assign(2,'a');
		students[i].midterm = random_num(i);
		students[i].final = random_num(i);
		
		for (vector<double>::size_type j = 0; j < 4; j++){
			students[i].homework.push_back(random_num(j)); 
		}
	}
}

double random_num(int i)
{
	double num;

	srand(time(0) + i);
	num = (double) (rand() % 100);

	return num;
}
