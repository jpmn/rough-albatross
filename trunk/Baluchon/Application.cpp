
#include <iostream>

#include "CameraCaptureService.h"
#include "ColorDetectionService.h"
#include "PatternDetectionService.h"
#include "VideoWriterService.h"
#include "DisplayImageService.h"

#include "Engine.h"
#include "ServiceLayer.h"

using namespace baluchon::core::engine;
using namespace baluchon::core::services;
using namespace baluchon::core::services::capture;
using namespace baluchon::core::services::colordetection;
using namespace baluchon::core::services::display;
using namespace baluchon::core::services::patterndetection;

int main() {

	// Layer 1
	ICaptureService* wCaptureService = new CameraCaptureService();
	{
		wCaptureService->setCapture(cvCreateCameraCapture(0));
	}

	IServiceLayer* wInputLayer = new ServiceLayer();
	{
		wInputLayer->addService(wCaptureService);
	}

	// Layer 2
	IColorDetectionService* wColorDetectionService = new ColorDetectionService();
	{
		wColorDetectionService->setColorTolerance(10);
		wColorDetectionService->setMaxMarkerCount(2);
	}

	IPatternDetectionService* wPatternDetectionService = new PatternDetectionService();
	{
        wPatternDetectionService->addPattern("a_pattern.jpg");
        wPatternDetectionService->addPattern("arrow_pattern.jpg");
	}

	IServiceLayer* wFilterLayer = new ServiceLayer();
	{
		wFilterLayer->addService(wColorDetectionService);
		wFilterLayer->addService(wPatternDetectionService);
	}

	// Layer 3
	IDisplayService* wDisplayImageService = new DisplayImageService();
	{
		wDisplayImageService->setWindowName("Baluchon");
	}

    IServiceLayer* wDisplayLayer = new ServiceLayer();
	{
		wDisplayLayer->addService(wDisplayImageService);
	}

	// Layer 4
	//IWriterService* wWriterService = new VideoWriterService();
	//{
	//	wWriterService->disable();
	//}

    //IServiceLayer* wWriterLayer = new ServiceLayer();
	//{
	//	wWriterLayer->addService(wWriterService);
	//}

	// Engine
	IEngine* wEngine = new Engine();
	{
		wEngine->setExitKey('q');

		wEngine->addServiceLayer(wInputLayer);
		wEngine->addServiceLayer(wFilterLayer);
        wEngine->addServiceLayer(wDisplayLayer);
		//wEngine->addServiceLayer(wWriterLayer);

		wEngine->init();
		wEngine->run();
		wEngine->dispose();
	}
	
	//std::cin.get();

	return EXIT_SUCCESS;
}