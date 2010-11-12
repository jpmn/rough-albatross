#pragma once

#include "IMarker.h"

namespace baluchon { namespace core { namespace services { namespace colordetection {

class Marker : public IMarker
{
public:
	Marker(void);
	~Marker(void);

	virtual void addBlob(IBlob*);
	virtual vector<IBlob*> getBlobs(void);
	virtual void clearBlobs(void);

private:
	vector<IBlob*> mBlobs;
};

}}}};