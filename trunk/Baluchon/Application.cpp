
#include <iostream>

#include "CameraCaptureService.h"
#include "ColorDetectionService.h"
#include "PatternDetectionService.h"
#include "ObjectDetectionService.h"
#include "VideoWriterService.h"
#include "DisplayImageService.h"

#include "PoseEstimationService.h"
#include "PositioningService.h"
#include "Engine.h"
#include "Pattern.h"
#include "ServiceLayer.h"

#include "Translation.h"
#include "Rotation.h"
#include "FrameCube.h"
#include "PositioningVisitor.h"

using namespace baluchon::core::engine;
using namespace baluchon::core::services;
using namespace baluchon::core::services::capture;
using namespace baluchon::core::services::colordetection;
using namespace baluchon::core::services::display;
using namespace baluchon::core::services::patterndetection;
using namespace baluchon::core::services::poseestimation;
using namespace baluchon::core::services::positioning;
using namespace baluchon::core::services::objectdetection;

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
		wColorDetectionService->setMaxMarkerCount(2);
	}

    IPattern* aPattern = new Pattern("a_pattern.jpg");
    IPattern* arrowModPattern = new Pattern("arrow_pattern_mod.jpg");

    IPatternDetectionService* wPatternDetectionService = new PatternDetectionService();
	{
        wPatternDetectionService->addPattern(aPattern);
        wPatternDetectionService->addPattern(arrowModPattern);
	}


    IPoseEstimationService* wPoseEstimationService = new PoseEstimationService("intrinsic.xml", "distortion.xml");

    IPositioningService* wPositioningService = new PositioningService("intrinsic.xml", "distortion.xml");
    Transform *base = new Transform();
    Translation *t = new Translation(400,0,0);
    Rotation *r = new Rotation(45,0,0,-1);
    IGraphic *f = new FrameCube(cvPoint3D32f(50.0f, 50.0f, -300.0f), (float)(arrowModPattern->getWidth()-100));
    IGraphic *f2 = new FrameCube(cvPoint3D32f(50.0f, 50.0f, -300.0f), (float)(arrowModPattern->getWidth()-100));
    r->add(f);
    //t->add(f);
    base->add(r);
    wPositioningService->addSceneGraph(arrowModPattern, r);
    wPositioningService->addSceneGraph(aPattern, f2);

	/*IObjectDetectionService* wObjectDetectionService = new ObjectDetectionService();
	{
		wObjectDetectionService->setCornerTolerance(25);
	}*/

	IServiceLayer* wFilterLayer = new ServiceLayer();
	{
		wFilterLayer->addService(wColorDetectionService);
		wFilterLayer->addService(wPatternDetectionService);
		//wFilterLayer->addService(wObjectDetectionService);
	}

    IServiceLayer* wPoseLayer = new ServiceLayer();
	{
		wPoseLayer->addService(wPoseEstimationService);
	}

    IServiceLayer* wPositioningLayer = new ServiceLayer();
	{
		wPositioningLayer->addService(wPositioningService);
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
        wEngine->addServiceLayer(wPoseLayer);
        wEngine->addServiceLayer(wPositioningLayer);
        wEngine->addServiceLayer(wDisplayLayer);
		//wEngine->addServiceLayer(wWriterLayer);

		wEngine->init();
		wEngine->run();
		wEngine->dispose();
	}
	
	//std::cin.get();

	return EXIT_SUCCESS;
}