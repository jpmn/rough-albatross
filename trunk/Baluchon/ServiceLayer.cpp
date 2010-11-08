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
	mListservices.push_back(service);
}

IService* ServiceLayer::findServiceInLowerLayer(IService* service) {
	return NULL;
}

}}};