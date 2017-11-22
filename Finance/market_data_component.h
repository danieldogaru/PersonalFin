#pragma once
#include <string>
#include <set>

typedef std::pair< std::string, double > TermRatePair;

namespace MarketDataAPI
{
	enum EMarketComponentType
	{
		NO_MARKET_COMPONENT = 0,
		MARKET_MONEY_MARKET,
		MAX_MARKET_COMPONENT
	};

	struct TermRatePairComparator
	{
		bool operator()(const TermRatePair& Left, const TermRatePair& Right) const
		{
			std::string leftTerm = Left.first.substr(Left.first.size() - 1, 1);
			std::string rightTerm = Right.first.substr(Right.first.size() - 1, 1);

			std::string leftDataStr = Left.first.substr(0, Left.first.size() - 1);
			std::string rightDataStr = Right.first.substr(0, Right.first.size() - 1);

			int leftData = std::stof(leftDataStr);
			int rightData = std::stof(rightDataStr);

			int leftTermInt  = Dates::TermConventions[leftTerm];
			int rightTermInt = Dates::TermConventions[rightTermInt];

			if (leftTermInt == rightTermInt)
			{
				return leftData < rightData;
			}

			return leftTermInt < rightTermInt;
		}
	};
};

class MarketDataComponent
{
	private:	
		std::set< TermRatePair, MarketDataAPI::TermRatePairComparator > _data;
		MarketDataAPI::EMarketComponentType _type;

	public:
		MarketDataComponent();
		MarketDataComponent(MarketDataAPI::EMarketComponentType Type);
		MarketDataComponent(const std::set< TermRatePair > & Data);
		MarketDataComponent(const MarketDataComponent& ToCopy);

		MarketDataComponent operator=(const MarketDataComponent& ToAssign);
		virtual ~MarketDataComponent();

		void AddItem(std::string Term, double Rate);
		MarketDataAPI::EMarketComponentType GetType();

		static bool CompareTypes( MarketDataComponent& Left, MarketDataComponent& Right);
		void Clear();
		
};