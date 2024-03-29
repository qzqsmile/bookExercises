#include<iostream>
#include<stdexcept>
#include<numeric>
#include<algorithm>
#include<string>
#include<vector>

using std::vector;
using std::domain_error;
using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::transform;
using std::istream;
using std::ostream;

struct Student_info {
	std::string name;
	double midterm, final;
	std::vector < double >homework;
};


bool did_all_hw(const Student_info & s);
void write_analysis(ostream & out, const string & name,
		    double analysis(const vector < Student_info > &),
		    const vector < Student_info > &did,
		    const vector < Student_info > &didnt);
double median_analysis(const vector < Student_info > &students);
double grade_aux(const Student_info & s);
double average(const vector < double >&v);
double average_grade(const Student_info & s);
double average_analysis(const vector < Student_info > &students);
double grade(double, double, double);
double grade(double, double, const std::vector < double >&);
double grade(const Student_info &);
double median(std::vector < double >vec);
double optimistic_median(const Student_info & s);
double optimistic_median_analysis(const vector < Student_info > &students);
istream & read(istream & is, Student_info & s);
istream & read_hw(istream & in, vector < double >&hw);
void sort_student(const vector<Student_info>& students, vector<Student_info>& did,vector<Student_info>& didnt);

int main(void)
{
	vector < Student_info > did, didnt;

	Student_info student;
	vector<Student_info> students;
	while (read(cin, student)) {
		students.push_back(student);
	}
	sort_student(students, did, didnt);

	if (did.empty()) {
		cout << "No student did all the homework!" << endl;
		return 1;
	}
	if (didnt.empty()) {
		cout << "Every student did all the homework!" << endl;
		return 1;
	}

	write_analysis(cout, "median", median_analysis, did, didnt);
	write_analysis(cout, "average", average_analysis, did, didnt);
	write_analysis(cout, "median of homework turned in",
		       optimistic_median_analysis, did, didnt);

	return 0;
}

bool did_all_hw(const Student_info & s)
{
	return ((find(s.homework.begin(), s.homework.end(), 0)) ==
		s.homework.end());
}

double median_analysis(const vector < Student_info > &students)
{
	vector < double >grades;

	transform(students.begin(), students.end(), back_inserter(grades),
		  grade_aux);

	return median(grades);
}

double grade_aux(const Student_info & s)
{
	try {
		return grade(s);
	}
	catch(domain_error) {
		return grade(s.midterm, s.final, 0);
	}
}


void write_analysis(ostream & out, const string & name,
		    double analysis(const vector < Student_info > &),
		    const vector < Student_info > &did,
		    const vector < Student_info > &didnt)
{
	out << name << ": median(did) = " << analysis(did) <<
	    ", median(didnt) = " << analysis(didnt) << endl;
}

double average(const vector < double >&v)
{
	return accumulate(v.begin(), v.end(), 0.0) / v.size();
}

double average_grade(const Student_info & s)
{
	return grade(s.midterm, s.final, average(s.homework));
}

double average_analysis(const vector < Student_info > &students)
{
	vector < double >grades;

	transform(students.begin(), students.end(), back_inserter(grades),
		  average_grade);

	return median(grades);
}

istream & read(istream & is, Student_info & s)
{
	is >> s.name >> s.midterm >> s.final;
	read_hw(is, s.homework);

	return is;
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

double optimistic_median(const Student_info & s)
{
	vector < double >nonzero;
	remove_copy(s.homework.begin(), s.homework.end(),
		    back_inserter(nonzero), 0);

	if (nonzero.empty())
		return grade(s.midterm, s.final, 0);
	else
		return grade(s.midterm, s.final, median(nonzero));
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

double optimistic_median_analysis(const vector < Student_info > &students)
{
	vector < double >grades;

	transform(students.begin(), students.end(), back_inserter(grades),
		  optimistic_median);

	return median(grades);
}

void sort_student(const vector<Student_info>& students, vector<Student_info>& did,vector<Student_info>& didnt)
{
	for (vector<Student_info>::size_type i = 0; i < students.size(); i++)
	{
		if (did_all_hw(students[i]))
			did.push_back(students[i]);
		else
			didnt.push_back(students[i]);
	}
}
