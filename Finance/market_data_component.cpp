#include "market_data_component.h"
#include <assert.h>

MarketDataComponent::MarketDataComponent()
{
	_data = { {"1D", 0.55}, {"3M", 0.66}, {"1Y", 1.45}, {"5Y", 2.33} };
}

MarketDataComponent::MarketDataComponent(MarketDataAPI::EMarketComponentType Type)
{
	assert(_type > MarketDataAPI::EMarketComponentType::NO_MARKET_COMPONENT && _type < MarketDataAPI::EMarketComponentType::MAX_MARKET_COMPONENT);
	_type = Type;
}

MarketDataComponent::MarketDataComponent(const MarketDataComponentVector& Data) :
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
	_data.push_back(TermRatePair(Term, Rate));

}

void MarketDataComponent::Clear()
{
	_data.clear();
}

TermRatePair MarketDataComponent::GetItemAt(int Index) const
{
	assert(Index >= 0 && Index < _data.size());
	return _data[Index];
}

int MarketDataComponent::GetSize() const
{
	return (int)_data.size();
}

MarketDataAPI::EMarketComponentType MarketDataComponent::GetType()
{
	return _type;
}

bool MarketDataComponent::CompareTypes(MarketDataComponent& Left,  MarketDataComponent& Right)
{
	return (int) Left.GetType() < (int) Right.GetType();
}