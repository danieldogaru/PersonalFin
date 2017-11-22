#include "curve_factory.h"
#include "curve_ir.h"
#include <string>

#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/document.h"

static CurveMaker<InterestRateCurve> irCurveMaker(std::string("InterestRate"));

InterestRateCurve::InterestRateCurve()
{
	_type = { CurveData::SCurveType::ECurveType::CURVE_TYPE_IR };
	_interpolationMethod = { CurveData::SCurveInterpolationMethod::ECurveInterpolationMethod::INTERPOLATION_LINEAR };

	_currency = "EUR";
	_index = "LIBOR";
	_curveDate = Dates::Date();
}

InterestRateCurve::InterestRateCurve(const InterestRateCurve& ToCopy) :
	_points(ToCopy._points), 
	_type(ToCopy._type), 
	_interpolationMethod(ToCopy._interpolationMethod),
	_currency(ToCopy._currency),
	_index(ToCopy._index), 
	_curveDate(ToCopy._curveDate)
{
}

void InterestRateCurve::GenerateCurve()
{

}

InterestRateCurve::~InterestRateCurve()
{

}

void InterestRateCurve::Serialize()
{
	rapidjson::Document document;
	document.SetObject();

	rapidjson::StringBuffer stringBuffer;
	rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(stringBuffer);

	writer.StartObject();

	writer.Key("CurveHeader");

	writer.StartObject();
		writer.Key("Type");
		writer.String(_type.ToString().c_str());

		writer.Key("InterpolationMethod");
		writer.String(_interpolationMethod.ToString().c_str());

		writer.Key("Currency");
		writer.String(_currency.c_str());

		writer.Key("Index");
		writer.String(_index.c_str());
	
		writer.Key("CurveDate");
		std::string curveDate = _curveDate.ToNumString();
		writer.String(curveDate.c_str());
	writer.EndObject();

	writer.EndObject();

	//document.Accept(writer);

	printf(stringBuffer.GetString());
}