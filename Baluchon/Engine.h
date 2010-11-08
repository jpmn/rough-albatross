#pragma once

#include <vector>

#include "Engine.h"
#include "IServiceLayer.h"

using namespace std;
using namespace Baluchon::Core::Services;

namespace Baluchon { namespace Core { namespace Engine { namespace Implementations {

class Engine
{
public:
	Engine(void);
	~Engine(void);

	virtual void Init(void);
	virtual void Run(void);
	virtual void Reset(void);
	virtual void Dispose(void);

	virtual void SetExitKey(char exitKey);
	virtual void AddServiceLayer(IServiceLayer* serviceLayer);

private:
	char mExitKey;
	vector<IServiceLayer*> mListServiceLayer;
};

}}}};