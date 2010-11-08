
#include <iostream>

#include "CameraCaptureService.h"
#include "DisplayImageService.h"
#include "Engine.h"
#include "ServiceLayer.h"

using namespace baluchon::core::engine;
using namespace baluchon::core::engine::implementations;
using namespace baluchon::core::services;
using namespace baluchon::core::services::implementations;

int main() {

	printf("Hello World!");
	
	CameraCaptureService* wCameraCaptureService = new CameraCaptureService();
	{
		wCameraCaptureService->setCapture(cvCreateCameraCapture(0));
	}

	ServiceLayer* wInputLayer = new ServiceLayer();
	{
		wInputLayer->addService(wCameraCaptureService);
	}

	DisplayImageService* wDisplayImageService = new DisplayImageService();
	{
		wDisplayImageService->setWindowName("Baluchon");
	}

	ServiceLayer* wDisplayLayer = new ServiceLayer();
	{
		wDisplayLayer->addService(wDisplayImageService);
	}

	Engine* wEngine = new Engine();
	{
		wEngine->setExitKey('q');

		wEngine->addServiceLayer(wInputLayer);
		wEngine->addServiceLayer(wDisplayLayer);

		wEngine->init();
		wEngine->run();
		wEngine->dispose();
	}
	
	std::cin.get();

	return EXIT_SUCCESS;
}