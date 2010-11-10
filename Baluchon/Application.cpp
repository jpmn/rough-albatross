
#include <iostream>

#include "CameraCaptureService.h"
#include "DisplayImageService.h"
#include "PatternDetectionService.h"
#include "Engine.h"
#include "ServiceLayer.h"

using namespace baluchon::core::engine;
using namespace baluchon::core::services;
using namespace baluchon::core::services::capture;
using namespace baluchon::core::services::display;
using namespace baluchon::core::services::patterndetection;

int main() {

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

    IPatternDetectionService* wPatternDetectionService = new PatternDetectionService();
	{
        wPatternDetectionService->addPattern("a_pattern.jpg");
        wPatternDetectionService->addPattern("arrow_pattern.jpg");
	}

	ServiceLayer* wFilterLayer = new ServiceLayer();
	{
		wFilterLayer->addService(wPatternDetectionService);
	}

    ServiceLayer* wDisplayLayer = new ServiceLayer();
	{
		wDisplayLayer->addService(wDisplayImageService);
	}

	Engine* wEngine = new Engine();
	{
		wEngine->setExitKey('q');

		wEngine->addServiceLayer(wInputLayer);
		wEngine->addServiceLayer(wFilterLayer);
        wEngine->addServiceLayer(wDisplayLayer);

		wEngine->init();
		wEngine->run();
		wEngine->dispose();
	}
	
	std::cin.get();

	return EXIT_SUCCESS;
}