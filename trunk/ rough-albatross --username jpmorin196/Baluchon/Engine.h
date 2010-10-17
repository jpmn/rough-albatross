#pragma once

#include <vector>
#include "IEngine.h"

using namespace std;

namespace Baluchon { namespace Core {

class CEngine : implements IEngine
{
public:
	CEngine(void);
	~CEngine(void);

	void init(void);
	void cycle(void);
	void dispose(void);
	void registerService(IService* s);
	void unregisterService(IService* s);

	void setNamedWindow(INamedWindow* nw);
	void setExitKey(char key);
	void setCycleDuration(int ms);

private:
	INamedWindow* mNamedWindow;
	int mCycleCount;
	char mExitKey;
	int mCycleDuration;
	vector<IService*> mListServices;
};

}};

