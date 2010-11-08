#include "ServiceLayer.h"

namespace Baluchon { namespace Core { namespace Services {

ServiceLayer::ServiceLayer(void) {
	
}

ServiceLayer::~ServiceLayer(void) {

}

void ServiceLayer::SetLowerLayer(ServiceLayer* serviceLayer) {
	mLowerServiceLayer = serviceLayer;
}

void ServiceLayer::AddService(IService* service) {
	mListServices.push_back(service);
}

IService* ServiceLayer::FindServiceInLowerLayer(IService* service) {
	return NULL;
}

}}};