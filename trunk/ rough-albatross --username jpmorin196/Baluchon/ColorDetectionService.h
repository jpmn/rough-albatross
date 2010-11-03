#pragma once

#include <vector>

#include "IService.h"
#include "INamedWindow.h"
#include "Color.h"

using namespace std;
using namespace Baluchon::Core::Components;
using namespace Baluchon::Core::Data;

namespace Baluchon { namespace Core { namespace Services {

class CColorDetectionService : implements IService
{
public:
	static void onMouseClick(int event, int x, int y, int flags, void* param);

public:
	CColorDetectionService(void);
	~CColorDetectionService(void);

	void execute(IplImage* img);
	void initialize(void);
	void initializeDone(void);
	void reset(void);

	void addColor(CColor color);
	void setColorTolerance(int t);

	IplImage* getLastImage(void);

private:
	INamedWindow* mWinThreshold;
	vector<CColor> mListColors;
	int mColorTolerance;
	IplImage* mLastImage;
};

}}};