#include "curve_factory.h"
#include <assert.h>
#include <string>

void CurveFactory::RegisterMaker(const std::string& MakerKey, CurveMakerInterface * CurveMaker)
{
	assert(_curveMakers.find(MakerKey) == _curveMakers.end());
	_curveMakers[MakerKey] = CurveMaker;
}

CurveFactory& CurveFactory::Instance()
{
	static CurveFactory curveFactory;
	return curveFactory;
}

CurveInterface * CurveFactory::Create(const std::string& Type)
{
	auto makerIt = _curveMakers.find(Type);
	assert(makerIt != _curveMakers.end());

	CurveMakerInterface * maker = makerIt->second;
	return maker->Create();
}