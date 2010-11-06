#include <iostream>

#include <cv.h>
#include <highgui.h>

#include "Engine.h"
#include "NamedWindow.h"
#include "ColorDetectionService.h"
#include "PatternDetectionService.h"
#include "VideoWriterService.h"

using namespace Baluchon::Core::Engine;

int main() {
	
	CNamedWindow* wWindow = new CNamedWindow();
	{
		wWindow->setName("Camera :: Query Frame");
		wWindow->setFlag(CV_WINDOW_AUTOSIZE);
		wWindow->init();
	}

	CColorDetectionService* wColorService = new CColorDetectionService();
	{
		wColorService->setColorTolerance(25);
		wColorService->setMaxColorCount(3);
	}

	//CColorDetectionService* wColorService2 = new CColorDetectionService();
	//{
	//	wColorService->setColorTolerance(50);
	//	wColorService->setMaxColorCount(2);
	//}

	//CPatternDetectionService* wPatternService = new CPatternDetectionService();
	//{

	//}

	CVideoWriterService* wVideoService = new CVideoWriterService();
	//{

	//}

	CEngine* wEngine = new CEngine();
	{
		// Properties
		wEngine->setNamedWindow(wWindow);
		wEngine->setExitKey('q');

		// Services
		wEngine->registerServiceForProcessing(wColorService);
		//wEngine->registerService(wColorService2);
		//wEngine->registerService(wPatternService);
		wEngine->registerServiceForRendering(wVideoService);

		// Execution
		wEngine->init();
		wEngine->cycle();
		wEngine->dispose();
	}

	delete wEngine;
	delete wVideoService;
	//delete wPatternService;
	delete wColorService;
	//delete wColorService2;
	delete wWindow;

	std::cin.get();

	return EXIT_SUCCESS;
}