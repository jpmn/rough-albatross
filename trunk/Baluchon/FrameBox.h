#pragma once
#include "IGraphic.h"
#include "IVisitor.h"
#include "IColorable.h"
#include "BoxPrism.h"

using namespace baluchon::core::datas;
using namespace baluchon::core::datas::detection;

namespace baluchon { namespace core { namespace services { namespace positioning { 

class FrameBox : public IGraphic, public IColorable
{
public:
	FrameBox(BoxPrism* box, CvScalar color);
	~FrameBox(void);

    void accept(IVisitor* v);
	vector<CvPoint> getListPoints();

private:
	vector<CvPoint> mListPoints;
};

}}}};