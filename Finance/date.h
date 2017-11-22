#pragma once
#include <string>
#include <assert.h>
#include <map>

#define MIN_DAY_IN_MONTH 1
#define MAX_DAY_IN_MONTH 31

namespace Dates
{
	enum EMonth
	{
		JANUARY = 1,
		FEBRUARY,
		MARCH,
		APRIL,
		MAY,
		JUNE,
		JULY,
		AUGUST,
		SEPTEMBER,
		OCTOBER,
		NOVEMBER,
		DECEMBER
	};

	enum EDaysInYear
	{
		STANDARD365 = 365
	};

	enum EDaysInMonth
	{
		STANDARD31
	};

	static const std::map< const EMonth, const std::string > DateStrings = {
		{JANUARY, "JAN"}, {FEBRUARY, "FEB"}, {MARCH, "MAR"}, {APRIL, "APR"},
		{MAY, "MAY"}, {JUNE, "JUN"}, {JULY, "JUL"}, {AUGUST, "AUG"}, {SEPTEMBER, "SEP"},
		{OCTOBER, "OCT"}, {NOVEMBER,"NOV"}, {DECEMBER,"DEC"}
	};

	static std::map<std::string, int> TermConventions = {
		{ "D", 1 }, { "M", 31 },{ "Y", 365 }
	};

	struct SDay
	{
		unsigned int _value;

		SDay()
		{
			_value = 1;
		}

		SDay(int Value)
		{
			assert(MIN_DAY_IN_MONTH >= _value && _value <= MAX_DAY_IN_MONTH);
			_value = Value;
		};
	};

	struct SMonth
	{
		EMonth _value;

		SMonth()
		{
			_value = Dates::EMonth::JANUARY;
		}

		SMonth(EMonth Month)
		{
			_value = Month;
		}

		std::string ToString()
		{
			auto dateStringIt = DateStrings.find(_value);
			assert(dateStringIt != DateStrings.end());

			return dateStringIt->second;
		}
	};

	enum EDateFormat
	{
		EUROPEAN = 0,
		AMERICAN
	};

	class Date
	{
		private:
			SDay   _day;
			SMonth _month;
			unsigned int _year;
			unsigned int _value;
			EDateFormat _format;

			std::string ToStr(bool StringMoth);

		public:
			Date();
			Date(const std::string& Term);
			Date(SDay Day, SMonth Month, unsigned int Year);
			Date(SDay Day, SMonth Month, unsigned int Year, EDateFormat Format);

			void AddOneDay();
			void AddOneMonth();
			void AddOneYear();
			
			std::string ToNumString();
			std::string	ToString();

			static bool Compare(const Date& Left, const Date& Right);
	};
}