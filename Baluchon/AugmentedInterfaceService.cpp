#include "AugmentedInterfaceService.h"
#include "CameraCaptureService.h"
#include "IServiceLayer.h"

namespace baluchon { namespace core { namespace services { namespace augmentedinterface {

AugmentedInterfaceService::AugmentedInterfaceService(void)
{
}


AugmentedInterfaceService::~AugmentedInterfaceService(void)
{
}

void AugmentedInterfaceService::addAugmentedComponent(IAugmentedComponent* component)
{
    mAugmentedComponents.push_back(component);
}

void AugmentedInterfaceService::removeAugmentedComponent(IAugmentedComponent* component)
{
    bool found = false;
    unsigned int cpt = 0;
    while(!found && cpt < mAugmentedComponents.size())
    {
        if(mAugmentedComponents[cpt] == component)
        {
            found = true;
        }
        else
        {
            cpt++;
        }
    }
    if(found)
    {
        mAugmentedComponents.erase(mAugmentedComponents.begin()+cpt);
    }
}

void AugmentedInterfaceService::init(void) {
	mCaptureService = new CameraCaptureService();
	mCaptureService = (ICaptureService*) mServiceLayer->findService(mCaptureService);
}

void AugmentedInterfaceService::initDone(void) {

}

void AugmentedInterfaceService::execute(void) {
	for(unsigned int i = 0; i < mAugmentedComponents.size(); i++)
    {
        mAugmentedComponents[i]->execute();
        mAugmentedComponents[i]->draw(mCaptureService->getImage());
    }
}

void AugmentedInterfaceService::reset(void) {

}

void AugmentedInterfaceService::dispose(void) {
	
}

}}}};