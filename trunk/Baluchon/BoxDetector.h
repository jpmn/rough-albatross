#pragma once

#include "IDetector.h"
#include "BoxPrism.h"
#include "PrismFactory.h"
#include "RectangleDetector.h"

using namespace baluchon::core::datas::detection;

namespace baluchon { namespace core { namespace services { namespace objectdetection {

class BoxDetector : public IDetector
{
public:
	BoxDetector(void);
	virtual ~BoxDetector(void);

	vector<IDetectable*> find(IplImage* img, IplImage* src);
	
	void setDistanceTolerance(double distanceTolerance);

private:
	PrismFactory* mPrismFactory;
	RectangleDetector* mRectangleDetector;
	double mDistanceTolerance;
};

}}}};