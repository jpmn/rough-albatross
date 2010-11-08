#pragma once

#include <vector>

#include "IService.h"
#include "IServiceLayer.h"

using namespace std;

namespace baluchon { namespace core { namespace services {

class ServiceLayer : implements IServiceLayer
{
public:
	ServiceLayer(void);
	~ServiceLayer(void);

	virtual void setLowerLayer(ServiceLayer* serviceLayer);
	virtual void addService(IService* service);
	virtual IService* findServiceInLowerLayer(IService* service);

private:
	ServiceLayer* mLowerServiceLayer;
	vector<IService*> mListservices;
};

}}};