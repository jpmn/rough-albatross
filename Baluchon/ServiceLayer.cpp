#include "ServiceLayer.h"

namespace baluchon { namespace core { namespace services {

ServiceLayer::ServiceLayer(void) {
	mLowerServiceLayer = 0;
}

ServiceLayer::~ServiceLayer(void) {

}

void ServiceLayer::setLowerLayer(IServiceLayer* serviceLayer) {
	mLowerServiceLayer = serviceLayer;
}

IServiceLayer* ServiceLayer::getLowerLayer(void) {
	return mLowerServiceLayer;
}

void ServiceLayer::addService(IService* service) {
	mListServices.push_back(service);
    service->setServiceLayer(this);
}

IService* ServiceLayer::findService(IService* service) {

	// TODO : looper dans les lower layers jusqu'au bout

	vector<IService*> wListLowerServices;
	IServiceLayer* wServiceLayer = mLowerServiceLayer;

	while (wServiceLayer != 0) {
		wListLowerServices = wServiceLayer->getServices();

		for (unsigned int i = 0; i < wListLowerServices.size(); i++) {
			if (typeid(*wListLowerServices[i]) == typeid(*service)) {
				delete service;
				return wListLowerServices[i];
			}
		}

		wServiceLayer = wServiceLayer->getLowerLayer();
	}

	delete service;
	return 0;
}

vector<IService*> ServiceLayer::getServices() {
	return mListServices;
}

}}};