#include "curve_factory.h"
#include "curve_ir.h"
#include "market_data_component.h"
#include <string>
#include <set>

#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/document.h"

static CurveMaker<InterestRateCurve> irCurveMaker(std::string("InterestRate"));

InterestRateCurve::InterestRateCurve()
{
	_type = { CurveData::SCurveType::ECurveType::CURVE_TYPE_IR };
	_interpolationMethod = { CurveData::SCurveInterpolationMethod::ECurveInterpolationMethod::INTERPOLATION_LINEAR };
	_frequency = CurveData::DAILY;
	_currency = "EUR";
	_index = "LIBOR";
	_curveDate = Dates::Date();
	_marketData = { MarketDataComponent() };
}

InterestRateCurve::InterestRateCurve(const InterestRateCurve& ToCopy) :
	_points(ToCopy._points), 
	_type(ToCopy._type), 
	_interpolationMethod(ToCopy._interpolationMethod),
	_currency(ToCopy._currency),
	_index(ToCopy._index), 
	_curveDate(ToCopy._curveDate),
	_frequency(ToCopy._frequency)
{
}

void InterestRateCurve::GenerateCurve()
{
	// Default curve length to 5Y
	std::vector< CurvePoint > marketDataPoints;
	std::string frequencyAsTerm;

	switch (_frequency)
	{
		case DAILY:
			frequencyAsTerm = "1D";
			break;
		case MONTHLY:
			frequencyAsTerm = "1M";
			break;
		case QUATERLY:
			frequencyAsTerm = "3M";
			break;
		case SEMIANNUALLY:
			frequencyAsTerm = "6M";
			break;
		case ANNUALY:
			frequencyAsTerm = "1Y";
			break;
		default:
			assert(false);
			break;
	}

	for (auto marketComponentIt = _marketData.begin(); marketComponentIt != _marketData.end(); ++marketComponentIt)
	{
		int componentSize = marketComponentIt->GetSize();

		for (int termIndex = 0; termIndex < componentSize; ++termIndex)
		{
			const TermRatePair marketPoint = marketComponentIt->GetItemAt(termIndex);
			Dates::Date termDate(marketPoint.first);

			CurvePoint point(termDate, marketPoint.second);
			marketDataPoints.push_back(point);
		}	
	}

	_points.push_back(CurvePoint());
	//today curve point
	for (int i = 0; i <= 365*5; i++)
	{
		CurvePoint lastPoint( _points[_points.size() - 1]);
		lastPoint._date.AddTerm(frequencyAsTerm);

		_points.push_back(lastPoint);
	}

	for (int curvePointIdx = 0; curvePointIdx < _points.size(); ++curvePointIdx)
	{
		CurvePoint * currentPoint = &_points[curvePointIdx];
		// For each point, find its neighbours
		int leftNeighborPosition = -1;
		int rightNeighborPosition = -1;

		for (int marketPointPosition = 0; marketPointPosition < marketDataPoints.size(); ++marketPointPosition)
		{
			CurvePoint * currentMktPoint = &marketDataPoints[marketPointPosition];

			if ( Dates::Date::Compare(currentMktPoint->_date, currentPoint->_date) <= 0 )
			{
				leftNeighborPosition = marketPointPosition;
			}
			else
			{
				// If found, break
				rightNeighborPosition = marketPointPosition;
				break;
			}
		}

		if (leftNeighborPosition == -1 || rightNeighborPosition == -1)
		{
			continue;
		}

		_points[curvePointIdx] = LinearInterpolation(marketDataPoints[leftNeighborPosition], marketDataPoints[rightNeighborPosition], currentPoint->_date);
	}

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

		// add frequency
		writer.Key("Currency");
		writer.String(_currency.c_str());

		writer.Key("Index");
		writer.String(_index.c_str());
	
		writer.Key("CurveDate");
		std::string curveDate = _curveDate.ToNumString();
		writer.String(curveDate.c_str());
	writer.EndObject();

	writer.Key("CurvePoints");
		writer.StartArray();
		for (int i = 0; i < _points.size(); i++)
		{
			writer.StartObject();
				writer.Key("Date");
				std::string pointDate = _points[i]._date.ToNumString();
				writer.String(pointDate.c_str());

				writer.Key("Rate");
				std::string rate = std::to_string(_points[i]._rate);
				writer.String(rate.c_str());
			writer.EndObject();
		};
		writer.EndArray();
	writer.EndObject();

	//document.Accept(writer);

	printf(stringBuffer.GetString());
}

CurvePoint InterestRateCurve::LinearInterpolation(CurvePoint& First, CurvePoint& Second, Dates::Date& TargetDate)
{
	CurvePoint retPoint(TargetDate, 0.0);

	if (Dates::Date::Compare(First._date, TargetDate) == 0)
	{
		retPoint._rate = First._rate;
		return retPoint;
	}

	if (Dates::Date::Compare(Second._date, TargetDate) == 0)
	{
		retPoint._rate = Second._rate;
		return retPoint;
	}

	double firstInDays  = (double) First._date.ToNumDays();
	double secondInDays = (double) Second._date.ToNumDays();
	double targetInDays = (double) TargetDate.ToNumDays();

	retPoint._rate = (double) ( (Second._rate - First._rate) * ((targetInDays - firstInDays) / (secondInDays - firstInDays)));
	retPoint._rate += First._rate;
	return retPoint;
}

void InterestRateCurve::LinearInterpolationRange(CurvePoint & Left, CurvePoint & Right)
{
	// Get the number of days between the left point and the right point
	int leftPointsDays = Left._date.ToNumDays();
	int rightPointDays = Right._date.ToNumDays();
	int daysDiff = rightPointDays - leftPointsDays;

	// Insert left point into curve if not already added
	if (_points[_points.size() - 1]._date.ToNumDays() != leftPointsDays)
	{
		_points.push_back(Left);
	}

	// If succeeding points, add the right one
	// Otherwise interpolate everything in between

	if (daysDiff == 1)
	{
		_points.push_back(Right);
		return;
	}

	for (int pointIndex = 1; pointIndex < daysDiff - 1; ++pointIndex)
	{
		//Get the date of the last point;
		Dates::Date targetDate = Dates::Date(Left._date);
			//CurvePoint target = LinearInterpolation(Left, Right);
	}

}
