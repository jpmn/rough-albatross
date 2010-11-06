#pragma once

#include <vector>
#include "IEngine.h"

using namespace std;

namespace Baluchon { namespace Core { namespace Engine {

class CEngine : implements IEngine
{
public:
	CEngine(void);
	~CEngine(void);

	void init(void);
	void cycle(void);
	void dispose(void);
	void registerServiceForProcessing(IProcessingService* s);
	void registerServiceForRendering(IRenderingService* s);

	void setNamedWindow(INamedWindow* nw);
	void setExitKey(char key);
	void setCycleDuration(int ms);

private:
	INamedWindow* mNamedWindow;
	int mCycleCount;
	char mExitKey;
	int mCycleDuration;
	vector<IProcessingService*> mListProcessingServices;
	vector<IRenderingService*> mListRenderingServices;
};

}}};

