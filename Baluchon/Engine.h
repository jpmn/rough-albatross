#pragma once

#include <vector>

#include "IEngine.h"
#include "IServiceLayer.h"

using namespace std;
using namespace baluchon::core::engine;
using namespace baluchon::core::services;

namespace baluchon { namespace core { namespace engine {

class Engine : public IEngine
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

}}};