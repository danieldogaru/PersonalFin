#pragma once
#include "market_data_component.h"
#include "curve_interface.h"
#include "date.h"
#include <set>

struct CurvePoint
{
	Dates::Date _date;
	double _rate;

	CurvePoint() : _date(Dates::Date()), _rate(0.0) {};
	CurvePoint(Dates::Date Date, double Rate) : _date(Date), _rate(Rate) {};
};

struct CurvePointComparator
{
	bool operator()(const CurvePoint& Left, const CurvePoint& Right) const
	{
		return Dates::Date::Compare(Left._date, Right._date);
	}
};

struct MarketDataComponentComparator
{
	bool operator()(const MarketDataComponent& Left, const MarketDataComponent& Right) const
	{
		return MarketDataComponent::CompareTypes(const_cast<MarketDataComponent&>(Left), const_cast<MarketDataComponent&>(Right));
	}
};

class InterestRateCurve : public CurveInterface
{
	private:
		std::set< CurvePoint, CurvePointComparator > _points;
		std::set< MarketDataComponent, MarketDataComponentComparator > _marketData;

		CurveData::SCurveType _type;
		CurveData::SCurveInterpolationMethod _interpolationMethod;
		std::string _currency;
		std::string _index;
		Dates::Date _curveDate;
	public:
		InterestRateCurve();
		InterestRateCurve(const InterestRateCurve& ToCopy);
		void GenerateCurve();
		void Serialize();

		virtual ~InterestRateCurve();

};