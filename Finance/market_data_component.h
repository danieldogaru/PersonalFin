#pragma once
#include <string>
#include <set>
#include "date.h"
#include <vector>

typedef std::pair< std::string, double > TermRatePair;

namespace MarketDataAPI
{
	enum EMarketComponentType
	{
		NO_MARKET_COMPONENT = 0,
		MARKET_MONEY_MARKET,
		MAX_MARKET_COMPONENT
	};

	/*struct TermRatePairComparator
	{
		bool operator()(const TermRatePair& Left, const TermRatePair& Right) const
		{
			std::string leftTerm = Left.first.substr(Left.first.size() - 1, 1);
			std::string rightTerm = Right.first.substr(Right.first.size() - 1, 1);

			std::string leftDataStr = Left.first.substr(0, Left.first.size() - 1);
			std::string rightDataStr = Right.first.substr(0, Right.first.size() - 1);

			int leftData = std::stoi(leftDataStr);
			int rightData = std::stoi(rightDataStr);

			int leftTermInt  = (int) Dates::TermConventions[leftTerm];
			int rightTermInt = (int) Dates::TermConventions[rightTermInt];

			if (leftTermInt == rightTermInt)
			{
				return leftData < rightData;
			}

			return leftTermInt < rightTermInt;
		}
	};*/
};

//typedef std::set< TermRatePair, MarketDataAPI::TermRatePairComparator > MarketDataComponentSet;
typedef std::vector< TermRatePair > MarketDataComponentVector;

class MarketDataComponent
{
	public:	
		MarketDataComponentVector _data;
		MarketDataAPI::EMarketComponentType _type;

	public:
		MarketDataComponent();
		MarketDataComponent(MarketDataAPI::EMarketComponentType Type);
		MarketDataComponent(const MarketDataComponentVector & Data);
		MarketDataComponent(const MarketDataComponent& ToCopy);

		MarketDataComponent operator=(const MarketDataComponent& ToAssign);
		virtual ~MarketDataComponent();

		void AddItem(std::string Term, double Rate);

		TermRatePair GetItemAt(int Index) const;
		int GetSize() const;
		MarketDataAPI::EMarketComponentType GetType();

		static bool CompareTypes( MarketDataComponent& Left, MarketDataComponent& Right);
		void Clear();		
};