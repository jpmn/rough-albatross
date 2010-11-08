#include "ServiceLayer.h"

namespace baluchon { namespace core { namespace services {

ServiceLayer::ServiceLayer(void) {
	
}

ServiceLayer::~ServiceLayer(void) {

}

void ServiceLayer::setLowerLayer(IServiceLayer* serviceLayer) {
	mLowerServiceLayer = serviceLayer;
}

void ServiceLayer::addService(IService* service) {
	mListServices.push_back(service);
}

IService* ServiceLayer::findService(IService* service) {

	// TODO : looper dans les lower layers jusqu'au bout

	vector<IService*> wListLowerServices = mLowerServiceLayer->getServices();

	for (int i = 0; i < wListLowerServices.size(); i++) {
		if (typeid(wListLowerServices[i]) == typeid(service))
			return wListLowerServices[i];
	}

	return NULL;
}

vector<IService*> ServiceLayer::getServices() {
	return mListServices;
}

}}};