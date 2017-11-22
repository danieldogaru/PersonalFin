#pragma once
#include "market_data_component.h"
#include <vector>

class MarketData
{
	private:
		std::vector< MarketDataComponent > _components;

	public:
		MarketData();
		MarketData(const MarketData& ToCopy);
		
		virtual ~MarketData();
		void AddComponent(const MarketDataComponent& ToAdd);

		int GetNumComponents();
		MarketDataComponent GetComponentAt();
		
};
