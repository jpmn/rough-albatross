#pragma once

#include <cv.h>

#include "CppInterface.h"
#include "INamedWindow.h"

namespace Baluchon { namespace Core { namespace Components { namespace Windows {

class CNamedWindow : implements INamedWindow
{
public:
	CNamedWindow(void);
	~CNamedWindow(void);

	void init(void);
	void show(void);

	void setName(const char* name);
	void setFlag(int flag);
	void setImage(const IplImage* image);

	const char* getName(void);
	const IplImage* getImage(void);

private:
	const char* mName;
	int mFlag;
	const IplImage* mImage;
};

}}}};