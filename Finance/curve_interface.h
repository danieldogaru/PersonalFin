#pragma once
#include <string>
#include <assert.h>
#include <map>

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
};

class CurveInterface
{
	public:
		virtual void GenerateCurve() = 0;
		virtual void Serialize() = 0;

		virtual ~CurveInterface() {};
};

