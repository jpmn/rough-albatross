#pragma once

#include "IBlob.h"

namespace baluchon { namespace core { namespace services { namespace colordetection {

class Blob : public IBlob
{
public:
	Blob(void);
	~Blob(void);

	virtual void setContours(CvSeq* contours);
	virtual CvSeq* getContours(void);

private:
	CvSeq* mContours;
	CvMemStorage* mStorage;
};

}}}};