#include "ServiceLayer.h"

namespace baluchon { namespace core { namespace services {

ServiceLayer::ServiceLayer(void) {
	
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
}

IService* ServiceLayer::findService(IService* service) {

	// TODO : looper dans les lower layers jusqu'au bout

	vector<IService*> wListLowerServices;
	IServiceLayer* wServiceLayer = mLowerServiceLayer;

	while (wServiceLayer != NULL) {
		wListLowerServices = mLowerServiceLayer->getServices();

		for (unsigned int i = 0; i < wListLowerServices.size(); i++) {
			if (typeid(wListLowerServices[i]) == typeid(service)) {
				delete service;
				return wListLowerServices[i];
			}
		}

		wServiceLayer = wServiceLayer->getLowerLayer();
	}

	delete service;
	return NULL;
}

vector<IService*> ServiceLayer::getServices() {
	return mListServices;
}

}}};