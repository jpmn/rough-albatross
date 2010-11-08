#pragma once

#include <vector>

#include "IService.h"
#include "IServiceLayer.h"

using namespace std;

namespace Baluchon { namespace Core { namespace Services {

class ServiceLayer : implements IServiceLayer
{
public:
	ServiceLayer(void);
	~ServiceLayer(void);

	virtual void SetLowerLayer(ServiceLayer* serviceLayer);
	virtual void AddService(IService* service);
	virtual IService* FindServiceInLowerLayer(IService* service);

private:
	ServiceLayer* mLowerServiceLayer;
	vector<IService*> mListServices;
};

}}};