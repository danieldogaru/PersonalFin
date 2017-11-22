#pragma once
#include <string>
#include <map>
#include "curve_interface.h"

class CurveMakerInterface;
class CurveFactory;

class CurveMakerInterface
{
	public:
		virtual CurveInterface * Create() const = 0;
		virtual ~CurveMakerInterface() {};
};


class CurveFactory
{
	public:
		static CurveFactory& Instance();
		
		void RegisterMaker(const std::string& MakerKey, CurveMakerInterface * CurveMaker);
		CurveInterface * Create(const std::string& Type);
	private:
		std::map< std::string, CurveMakerInterface* > _curveMakers;
};

template< class T >
class CurveMaker : public CurveMakerInterface
{
public:
	CurveMaker(std::string MakerKey)
	{
		CurveFactory::Instance().RegisterMaker(MakerKey, this);
	}

	virtual CurveInterface * Create() const
	{
		return new T();
	}
};