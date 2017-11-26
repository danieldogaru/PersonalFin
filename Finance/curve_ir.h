#pragma once
#include "market_data_component.h"
#include "curve_interface.h"
#include "date.h"
#include <set>

using namespace CurveData;
/*
struct CurvePointComparator
{
	bool operator()(const CurvePoint& Left, const CurvePoint& Right) const
	{
		return Dates::Date::Compare(Left._date, Right._date);
	}
};*/

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
		std::vector< CurvePoint > _points;
		std::set< MarketDataComponent, MarketDataComponentComparator > _marketData;

		CurveData::SCurveType _type;
		CurveData::SCurveInterpolationMethod _interpolationMethod;
		CurveData::EFrequency _frequency;
		
		std::string _currency;
		std::string _index;
		Dates::Date _curveDate;

		CurvePoint LinearInterpolation(CurvePoint& First, CurvePoint& Second, Dates::Date& TargetDate);
		void LinearInterpolationRange(CurvePoint& Left, CurvePoint& Right);
	public:
		InterestRateCurve();
		InterestRateCurve(const InterestRateCurve& ToCopy);
		void GenerateCurve();
		void Serialize();

		virtual ~InterestRateCurve();

};