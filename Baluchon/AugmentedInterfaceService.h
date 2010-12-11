#pragma once
#include "iaugmentedinterfaceservice.h"
#include "icaptureservice.h"

using namespace baluchon::core::services::capture;

namespace baluchon { namespace core { namespace services { namespace augmentedinterface {

class AugmentedInterfaceService :
    public IAugmentedInterfaceService
{
public:
    AugmentedInterfaceService(void);
    ~AugmentedInterfaceService(void);

    virtual void addAugmentedComponent(IAugmentedComponent* component);
    virtual void removeAugmentedComponent(IAugmentedComponent* component);

    virtual void init(void);
	virtual void initDone(void);
	virtual void execute(void);
	virtual void reset(void);
	virtual void dispose(void);

private:
    ICaptureService* mCaptureService;
    vector<IAugmentedComponent*> mAugmentedComponents;
};

}}}};