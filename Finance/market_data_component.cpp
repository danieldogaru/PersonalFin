#include "market_data_component.h"
#include <assert.h>

MarketDataComponent::MarketDataComponent()
{

}

MarketDataComponent::MarketDataComponent(MarketDataAPI::EMarketComponentType Type)
{
	assert(_type > MarketDataAPI::EMarketComponentType::NO_MARKET_COMPONENT && _type < MarketDataAPI::EMarketComponentType::MAX_MARKET_COMPONENT);
	_type = Type;

}

MarketDataComponent::MarketDataComponent(const std::set< TermRatePair>& Data) :
	_data(Data), _type(MarketDataAPI::EMarketComponentType::NO_MARKET_COMPONENT)
{

}

MarketDataComponent::MarketDataComponent(const MarketDataComponent& ToCopy)
{
	_data = ToCopy._data;
	_type = ToCopy._type;
}

MarketDataComponent MarketDataComponent::operator=(const MarketDataComponent& ToAssign)
{
	_data = ToAssign._data;
	_type = ToAssign._type;

	return *this;
}

MarketDataComponent::~MarketDataComponent()
{

}

void MarketDataComponent::AddItem(std::string Term, double Rate)
{
	assert(!Term.empty());
	_data.insert(TermRatePair(Term, Rate));

}

void MarketDataComponent::Clear()
{
	_data.clear();
}

MarketDataAPI::EMarketComponentType MarketDataComponent::GetType()
{
	return _type;
}

bool MarketDataComponent::CompareTypes(MarketDataComponent& Left,  MarketDataComponent& Right)
{
	return (int) Left.GetType() < (int) Right.GetType();
}