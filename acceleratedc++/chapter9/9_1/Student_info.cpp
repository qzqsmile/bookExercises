#include"Student_info.h"
#include"grade.h"

std::istream& Student_info::read(std::istream& in)
{
	in >> n >> midterm >> final;
	read_hw(in, homework);
	final_grade = ::grade(midterm, final, homework);
	
	return in;
}

double Student_info::grade() const
{
	return final_grade;
}

bool compare(const Student_info& x, const Student_info& y)
{
	return x.name() < y.name();
}

std::istream& read_hw(std::istream& in, std::vector<double>& hw)
{
	if (in){
		hw.clear();
		
		double x;
		while (in >> x)
			hw.push_back(x);

		in.clear();
	}

	return in;
}

Student_info::Student_info(): midterm(0), final(0), final_grade(0) { }
