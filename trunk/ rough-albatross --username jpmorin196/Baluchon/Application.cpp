#include <iostream>

#include <cv.h>
#include <highgui.h>

#include <pthread.h>

#include "Engine.h"
#include "NamedWindow.h"
#include "ColorDetectionService.h"
#include "PatternDetectionService.h"

using namespace Baluchon::Core;

int main() {
	
	CNamedWindow* wWindow = new CNamedWindow();
	{
		wWindow->setName("Camera :: Query Frame");
		wWindow->setFlag(CV_WINDOW_AUTOSIZE);
		wWindow->init();
	}

	CColorDetectionService* wColorService = new CColorDetectionService();
	{
		wColorService->setColorTolerance(10);
	}

	CPatternDetectionService* wPatternService = new CPatternDetectionService();
	{

	}

	CEngine* wEngine = new CEngine();
	{
		// Properties
		wEngine->setNamedWindow(wWindow);
		wEngine->setExitKey('q');

		// Services
		wEngine->registerService(wColorService);
		wEngine->registerService(wPatternService);

		// Execution
		wEngine->init();
		wEngine->cycle();
		wEngine->dispose();
	}

	delete wEngine;
	delete wPatternService;
	delete wColorService;
	delete wWindow;

	std::cin.get();

	return EXIT_SUCCESS;
}