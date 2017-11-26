#include "curve_interface.h"
#include "curve_factory.h"
#include "date.h"

int main()
{
	/*Dates::Date date("2M");
	Dates::Date date32("32D");
	Dates::Date month15("15M");

	assert(date.ToNumString() == "1/3/2000");
	assert(date32.ToNumString() == "2/2/2000");
	assert(month15.ToNumString() == "1/4/2001");*/

	auto curve = CurveFactory::Instance().Create("InterestRate");
	curve->GenerateCurve();
	curve->Serialize();

	return 0;
}