#pragma once
#include <string>
#include <assert.h>
#include <map>
#include "date.h"

namespace CurveData
{
	struct SCurveType
	{
		enum ECurveType
		{
			CURVE_TYPE_NONE = 0,
			CURVE_TYPE_IR,
			CURVE_TYPE_MAX_TYPE
		};

		ECurveType _data;
		std::string ToString()
		{
			std::string returnValue;
			switch (_data)
			{
				case CURVE_TYPE_IR:
					returnValue = "InterestRate";
					break;
				default:
					returnValue = "None";
					break;
			}

			return returnValue;
		}
	};

	struct SCurveInterpolationMethod
	{
		enum ECurveInterpolationMethod
		{
			INTERPOLATION_NONE = 0,
			INTERPOLATION_LINEAR,
			INTERPOLATION_SPLINE
		};

		ECurveInterpolationMethod _data;

		std::string ToString()
		{
			std::string returnValue;

			switch (_data)
			{
				case INTERPOLATION_LINEAR:
					returnValue = "LinearInterpolation";
					break;

				case INTERPOLATION_SPLINE:
					returnValue = "SplineInterpolation";
					break;

				default:
					returnValue = "None";
					break;
			}

			return returnValue;
		}
	};

	enum EFrequency
	{
		DAILY = 1,
		MONTHLY = 31,
		QUATERLY = 3 * MONTHLY,
		SEMIANNUALLY = 6 * MONTHLY,
		ANNUALY = 12 * MONTHLY
	};

	struct CurvePoint
	{
		Dates::Date _date;
		double _rate;

		CurvePoint() : _date(Dates::Date()), _rate(0.0) {};
		CurvePoint(Dates::Date Date, double Rate) : _date(Date), _rate(Rate) {};

		friend bool operator ==(const CurvePoint& P1, const CurvePoint& P2)
		{
			return Dates::Date::Compare(P1._date,P2._date) == 0;
		}
	};
};

class CurveInterface
{
	public:
		virtual void GenerateCurve() = 0;
		virtual void Serialize() = 0;

		virtual ~CurveInterface() {};
};

