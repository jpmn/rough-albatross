#pragma once

#include "IService.h"
#include "IServiceLayer.h"

using namespace std;

namespace baluchon { namespace core { namespace services {

class ServiceLayer : public IServiceLayer
{
public:
	ServiceLayer(void);
	~ServiceLayer(void);

	virtual void setLowerLayer(IServiceLayer* serviceLayer);
	virtual IServiceLayer* getLowerLayer(void) = 0;
	virtual void addService(IService* service);
	virtual IService* findService(IService* service);
	virtual vector<IService*> getServices(void);

private:
	IServiceLayer* mLowerServiceLayer;
	vector<IService*> mListServices;
};

}}};