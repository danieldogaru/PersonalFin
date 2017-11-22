#include "date.h"
#include <sstream>
using namespace Dates;

Dates::Date::Date()
{
	_day = SDay();
	_month = SMonth();
	_year = 2000;
	_format = Dates::EDateFormat::EUROPEAN;
	_value = 0;
}

Dates::Date::Date(const std::string& Term)
{
	(*this) = Date();

	std::string data = Term.substr(0, Term.length() - 1);
	int intData = std::stoi(data);

	std::string termType = Term.substr(Term.length() - 1, 1);

	if (termType == "D")
	{
		_day._value += intData;

		int months = (int) _month._value;

		while (_day._value > 31)
		{
			_day._value -= 31;
			months++;
		}

		while (months > 12)
		{
			months -= 12;
			_year++;
		}

		_month = EMonth(months);
	}
	else if (termType == "M")
	{
		int months = (int)_month._value + intData;

		while (months > 12)
		{
			months -= 12;
			_year++;
		}

		_month = EMonth(months);
	}
	else if (termType == "Y")
	{
		_year += intData;
	}
	else
	{
		assert(false);
	}
}

Dates::Date::Date(SDay Day, SMonth Month, unsigned int Year) :
	_day(Day), _month(Month), _year(Year), _format(Dates::EDateFormat::EUROPEAN)
{
	//_value = _year * STANDARD365 + ( (int) _month._value * (int) STANDARD31 ) + _day._value;
	//value = 0;
}

Dates::Date::Date(SDay Day, SMonth Month, unsigned int Year, EDateFormat Format) :
   _day(Day), _month(Month), _year(Year), _format(Format)
{
	//_value = _year * STANDARD365 + ( (int) _month._value * (int) STANDARD31 ) + _day._value;
	//value = 0;
}

std::string Dates::Date::ToStr(bool StringMoth)
{
	std::string out;
	std::ostringstream outStream;

	bool isEuropean = (_format == Dates::EDateFormat::EUROPEAN);
	std::string month = StringMoth ? _month.ToString() : std::to_string(int(_month._value));

	if (isEuropean)
	{
		outStream << (int)_day._value;
		outStream << "/";
		outStream << month;
	}
	else
	{
		outStream << month;
		outStream << "/";
		outStream << _day._value;
	}

	outStream << "/";
	outStream << _year;

	out = outStream.str();

	return out;
}

std::string Dates::Date::ToNumString()
{
	return ToStr(false);
}

std::string Dates::Date::ToString()
{
	return ToStr(true);
}

bool Dates::Date::Compare(const Date& Left, const Date& Right)
{
	if (Left._year < Right._year)
	{
		return true;
	}
	else if (Left._year == Right._year)
	{
		if (Left._month._value < Right._month._value)
		{
			return true;
		}
		else if (Left._month._value == Right._month._value)
		{
			if (Left._day._value < Right._day._value)
			{
				return true;
			}
		}
	}

	return false;
}

void Dates::Date::AddOneDay()
{
	_day._value++;

	if (_day._value > 31)
	{
		_day._value = 1;
		AddOneMonth();
	}
}

void Dates::Date::AddOneMonth()
{
	int month = (int)_month._value + 1;

	if (month > 12)
	{
		_year++;
		month = 1;
	}

	_month = EMonth(month);
	
}

void Dates::Date::AddOneYear()
{
	_year++;
}