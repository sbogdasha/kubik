#include <iostream>
#include <ctype.h>
#include <cassert>
#include <stdexcept>

using namespace std;

double evaluate(const char* const e);

struct expression
{
	virtual ~expression() {};
	virtual double operator()() const = 0;
};

struct number_token : public expression
{
	double value_;
	number_token(const int value = 0) : value_(value) {}
	double operator()() const {
		return value_;
	}
};

struct binary_predicate : public expression
{
	expression* left_;
	expression* right_;

	binary_predicate(expression* const left = 0, expression* const right = 0)
		: left_(left), right_(right)
	{}
};

struct plusS : public binary_predicate
{
	plusS(expression* const left, expression* const right)
		: binary_predicate(left, right)
	{}

	double operator()() const {
		return (*left_)() + (*right_)();
	}
};

struct minusS : public binary_predicate
{
	minusS(expression* const left, expression* const right)
		: binary_predicate(left, right)
	{}

	double operator()() const {
		return (*left_)() - (*right_)();
	}
};

struct mulS : public binary_predicate
{
	mulS(expression* const left, expression* const right)
		: binary_predicate(left, right)
	{}

	double operator()() const {
		return (*left_)() * (*right_)();
	}
};

struct divS : public binary_predicate
{
	divS(expression* const left, expression* const right)
		: binary_predicate(left, right)
	{}

	double operator()() const {
		return (*left_)() / (*right_)();
	}
};

struct powS : public binary_predicate
{
	powS(expression* const left, expression* const right)
		: binary_predicate(left, right)
	{}

	double operator()() const {
		return pow((*left_)(), (*right_)());
	}
};

struct sinS : public binary_predicate
{
	sinS(expression* const left, expression* const right)
		: binary_predicate(left, 0)
	{}

	double operator()() const {
		return sin((*left_)());
	}
};

struct cosS : public binary_predicate
{
	cosS(expression* const left, expression* const right)
		: binary_predicate(left, 0)
	{}

	double operator()() const {
		return cos((*left_)());
	}
};

class evaluator
{
public:
	const expression* parse(const char*);                   ///< Parse an expression

private:
	expression* parse_number(const char*&);                 ///< Parse numeric constants
	expression* parse_sin(char* s);
	expression* parse_cos(char* s);
	expression* parse_atom(const char*&);                   ///< Parse nested expression
	expression* parse_summands(const char*&);               ///< Parse '+' and '-' operations
	expression* parse_factors(const char*&);                ///< Parse '*' and '/' operations
};

expression* evaluator::parse_number(const char*& s)
{
	assert("Sanity check" && s && isdigit(*s));
	number_token* nt = new number_token(0);
	// Convert number...
	while (*s && isdigit(*s))
	{
		nt->value_ = nt->value_ * 10 + *s++ - '0';
		if (*s == '.')
		{
			s++;
			int count = 1;
			while (*s && isdigit(*s))
			{
				int t1 = (*s++ - '0');
				double t = t1 * pow(0.1, count++);
				nt->value_ = t + nt->value_;
			}
		}
	}
	return nt;
}

expression* evaluator::parse_sin(char* s)
{
	number_token* nt = new number_token(0);

	nt->value_ = evaluate(s);
	nt->value_ = sin(nt->value_);

	return nt;
}

expression* evaluator::parse_cos(char* s)
{
	number_token* nt = new number_token(0);

	nt->value_ = evaluate(s);
	nt->value_ = cos(nt->value_);

	return nt;
}

expression* evaluator::parse_atom(const char*& s)
{
	assert("Sanity check" && s);
	if (*s == 0)
	{
		throw std::runtime_error("Atom parse error: unexpected EOS");
	}
	else if (*s == '(')
	{
		s++;
		expression* atom = parse_summands(s);
		if (*s == ')')
		{
			s++;
			return atom;
		}
		throw std::runtime_error("Atom parse error: unbalanced brackets");

	}
	else if (isdigit(*s) || *s == 's' || *s == 'c')
	{
		if (*s == 's')
		{
			s += 2;
			int count = 0, j = 0;
			char temp[100];
			while (count != -1)
			{
				temp[j++] = *const_cast<char*>(s);
				s++;
				if (*s == '(')
					count++;
				else if (*s == ')')
					count--;
			}
			temp[j] = '\0';
			expression* atom = parse_sin(temp);
			if (*s == ')')
			{
				s++;
				return atom;
			}
			throw std::runtime_error("Atom parse error: unbalanced brackets");
		}
		else if (*s == 'c')
		{
			s += 2;
			int count = 0, j = 0;
			char temp[100];
			while (count != -1)
			{
				temp[j++] = *const_cast<char*>(s);
				s++;
				if (*s == '(')
					count++;
				else if (*s == ')')
					count--;
			}
			temp[j] = '\0';
			expression* atom = parse_cos(temp);
			if (*s == ')')
			{
				s++;
				return atom;
			}
			throw std::runtime_error("Atom parse error: unbalanced brackets");
		}

		expression* atom = parse_number(s);
		return atom;
	}
	throw std::runtime_error("Atom parse error: unexpected char");
}

expression* evaluator::parse_factors(const char*& s)
{
	assert("Sanity check" && s);
	expression* left = parse_atom(s);
	while (*s)
	{
		if (*s == '*')
		{
			s++;
			expression* right = parse_atom(s);
			left = new mulS(left, right);
			continue;
		}
		else if (*s == '/')
		{
			s++;
			expression* right = parse_atom(s);
			left = new divS(left, right);
			continue;
		}
		else if (*s == '^')
		{
			s++;
			expression* right = parse_atom(s);
			left = new powS(left, right);
			continue;
		}
		return left;
	}
	return left;
}

expression* evaluator::parse_summands(const char*& s)
{
	assert("Sanity check" && s);
	expression* left = parse_factors(s);
	while (*s)
	{
		if (*s == '+')
		{
			s++;
			expression* right = parse_factors(s);
			left = new plusS(left, right);
			continue;
		}
		else if (*s == '-')
		{
			s++;
			expression* right = parse_factors(s);
			left = new minusS(left, right);
			continue;
		}
		return left;
	}
	return left;
}

const expression* evaluator::parse(const char* s)
{
	return parse_summands(s);
}

double evaluate(const char* const e)
{
	evaluator ev;
	const expression* const ex = ev.parse(e);
	assert("Sanity check" && ex);
	return (*ex)();
}

// s= evaluate(“(4+3)*2/5” );
// s= evaluate(“((12+9)/2)*5”);
int main()
{

	char expression[100], temp[100];

	cin.getline(expression, 100);

	int j = 0;

	for (int i = 0; expression[i] != '\0'; i++)
		if (expression[i] != ' ')
			temp[j++] = expression[i];

	temp[j] = '\0';
	
	try
	{
		double a = evaluate(temp);
		cout << "Result = " << a << endl;
	}

	catch (exception e)
	{
		cout << e.what() << endl;
	}
	

	return 0;
}