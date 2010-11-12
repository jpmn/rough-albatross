#pragma once

namespace baluchon { namespace core { namespace services {

class IServiceLayer;

class IService 
{
public:
	virtual ~IService() {}

	virtual void init(void) = 0;
	virtual void initDone(void) = 0;
	virtual void execute(void) = 0;
	virtual void reset(void) = 0;
	virtual void dispose(void) = 0;

	void setServiceLayer(IServiceLayer* serviceLayer) {
		mServiceLayer = serviceLayer;
	}

	virtual void enable(void) {
		mIsEnabled = true;
	}

	virtual void disable(void) {
		mIsEnabled = false;
	}

	virtual bool isEnabled(void) {
		return mIsEnabled;
	}

protected:
	IServiceLayer* mServiceLayer;
	bool mIsEnabled;
};

}}};