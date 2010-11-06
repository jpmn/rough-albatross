#pragma once

#include <vector>

#include "IProcessingService.h"
#include "INamedWindow.h"
#include "Color.h"

using namespace std;
using namespace Baluchon::Core::Components::Windows;
using namespace Baluchon::Core::Data;

namespace Baluchon { namespace Core { namespace Services {

class CColorDetectionService : implements IProcessingService
{
public:
	static void onMouseClick(int event, int x, int y, int flags, void* param);

public:
	CColorDetectionService(void);
	~CColorDetectionService(void);

	void execute(const IplImage* imgIn, IplImage* imgOut);
	void initialize(void);
	void initializeDone(void);
	void reset(void);

	void addColor(CColor color);
	void setColorTolerance(int t);
	void setMaxColorCount(int c);

	const IplImage* getLastImage(void);

private:
	INamedWindow* mWinThreshold;
	vector<CColor> mListColors;
	int mColorTolerance;
	int mMaxColorCount;
	const IplImage* mLastImage;
	IplConvKernel* mMorphKernel;
};

}}};