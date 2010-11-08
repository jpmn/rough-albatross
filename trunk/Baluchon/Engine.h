#pragma once

#include <vector>

#include "Engine.h"
#include "IServiceLayer.h"

using namespace std;
using namespace baluchon::core::services;

namespace baluchon { namespace core { namespace engine { namespace implementations {

class Engine
{
public:
	Engine(void);
	~Engine(void);

	virtual void init(void);
	virtual void run(void);
	virtual void reset(void);
	virtual void dispose(void);

	virtual void setExitKey(char exitKey);
	virtual void addServiceLayer(IServiceLayer* serviceLayer);

private:
	char mExitKey;
	vector<IServiceLayer*> mListServiceLayers;
};

}}}};