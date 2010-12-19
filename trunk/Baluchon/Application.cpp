
#include <iostream>

#include "Engine.h"
#include "ServiceLayer.h"

#include "CameraCaptureService.h"

#include "ColorDetectionService.h"
#include "ColorDetector.h"

#include "PatternDetectionService.h"
#include "Pattern.h"

#include "ObjectDetectionService.h"
#include "BoxDetector.h"

#include "PoseEstimationService.h"

#include "PositioningService.h"
#include "PositioningVisitor.h"
#include "Translation.h"
#include "Rotation.h"
#include "Scaling.h"
#include "FrameCube.h"
#include "AnimatedSliding.h"
#include "AnimatedTranslation.h"
#include "AnimatedRotation.h"

#include "AugmentedInterfaceService.h"
#include "AugmentedColorButton.h"

#include "DisplayImageService.h"
#include "VideoWriterService.h"

#include "TestEventHandler.h"

using namespace baluchon::core::datas::animation;
using namespace baluchon::core::engine;
using namespace baluchon::core::services;
using namespace baluchon::core::services::capture;
using namespace baluchon::core::services::colordetection;
using namespace baluchon::core::services::display;
using namespace baluchon::core::services::patterndetection;
using namespace baluchon::core::services::poseestimation;
using namespace baluchon::core::services::positioning;
using namespace baluchon::core::services::objectdetection;
using namespace baluchon::core::services::augmentedinterface;

int main() {

	// Services
	ICaptureService* wCaptureService;
	IPatternDetectionService* wPatternDetectionService;
	IColorDetectionService* wColorDetectionService;
	IObjectDetectionService* wObjectDetectionService;
	IPoseEstimationService* wPoseEstimationService;
	IPositioningService* wPositioningService;
	IAugmentedInterfaceService* wAugmentedInterfaceService;
	IDisplayService* wDisplayImageService;
	//IServiceLayer* wWriterLayer;

	IPattern* aPattern;
	IPattern* arrowModPattern;

	// Layer 1
	IServiceLayer* wInputLayer = new ServiceLayer();
	{
		wCaptureService = new CameraCaptureService();
		{
			wCaptureService->setCapture(cvCreateCameraCapture(0));
		}

		wInputLayer->addService(wCaptureService);
	}

	// Layer 2
	IServiceLayer* wFilterLayer = new ServiceLayer();
	{
		wColorDetectionService = new ColorDetectionService();
		{
			ColorDetector* wColorDetector = new ColorDetector();
			{
				wColorDetector->addColor(CV_RGB(200, 45, 65), 40);
				wColorDetector->setMinimumSize(200);
			}

			wColorDetectionService->addDetector(wColorDetector);
            wColorDetectionService->disable();
		}
	
		wObjectDetectionService = new ObjectDetectionService();
		{
			BoxDetector* wBoxDetector = new BoxDetector();
			{
				wBoxDetector->setDistanceTolerance(25);
			}

			wObjectDetectionService->addDetector(wBoxDetector);
            wObjectDetectionService->disable();
		}

		wPatternDetectionService = new PatternDetectionService();
		{
			aPattern = new Pattern("a_pattern.jpg");
			arrowModPattern = new Pattern("arrow_pattern_mod.jpg");

			wPatternDetectionService->addPattern(aPattern);
			wPatternDetectionService->addPattern(arrowModPattern);
		}

		wFilterLayer->addService(wColorDetectionService);
		wFilterLayer->addService(wObjectDetectionService);
		wFilterLayer->addService(wPatternDetectionService);
	}
	
	// Layer 3
    IServiceLayer* wPoseLayer = new ServiceLayer();
	{
		wPoseEstimationService = new PoseEstimationService("intrinsic.xml", "distortion.xml");

		wPoseLayer->addService(wPoseEstimationService);
	}

	// Layer 4
    IServiceLayer* wPositioningLayer = new ServiceLayer();
	{
		wPositioningService = new PositioningService("intrinsic.xml", "distortion.xml"); 
		{
			AnimatedTransform* base = new AnimatedTransform();
			AnimatedTranslation* t = new AnimatedTranslation(cvPoint3D32f(0,0,0), 3.0f);
			AnimatedRotation* r = new AnimatedRotation(cvPoint3D32f(0,0,-1), 45.0f, 3.0f);
			AnimatedSliding* s = new AnimatedSliding(cvPoint3D32f(0,0,0), cvPoint3D32f(0,0,200), 5.0f);

			FrameCube *f = new FrameCube(cvPoint3D32f(50.0f, 50.0f, -300.0f), (float)(arrowModPattern->getWidth()-100), CV_RGB(0, 0, 255));
			IGraphic *f2 = new FrameCube(cvPoint3D32f(75.0f, 75.0f, -300.0f - arrowModPattern->getWidth()+150), (float)(arrowModPattern->getWidth()-150), CV_RGB(255, 0, 0));
			IGraphic *f3 = new FrameCube(cvPoint3D32f(100.0f, 100.0f, -300.0f - arrowModPattern->getWidth()+200 - arrowModPattern->getWidth()+150), (float)(arrowModPattern->getWidth()-200), CV_RGB(0, 255, 0));
			IGraphic *fArrow = new FrameCube(cvPoint3D32f(50.0f, 50.0f, -300.0f), (float)(arrowModPattern->getWidth()-100), CV_RGB(0, 0, 255));
			
			
			s->add(f);
			s->add(f2);
			s->add(f3);
			t->add(s);
			r->add(t);
			base->add(s);

			wPositioningService->addSceneGraph(arrowModPattern, base);
			wPositioningService->addSceneGraph(aPattern, fArrow);
		}

		wPositioningLayer->addService(wPositioningService);
	}

    // Interface layer
    IServiceLayer* wAugmentedInterfaceLayer = new ServiceLayer();
	{
		wAugmentedInterfaceService = new AugmentedInterfaceService();
		{
			IAugmentedComponent* component = new AugmentedColorButton(wColorDetectionService, cvPoint(50, 50), 50, 50);
			{
				component->addEventHandler(new TestEventHandler(wCaptureService));
			}

			//wAugmentedInterfaceService->addAugmentedComponent(component);
		}

		wAugmentedInterfaceLayer->addService(wAugmentedInterfaceService);
	}

	// Layer 6
    IServiceLayer* wDisplayLayer = new ServiceLayer();
	{
		wDisplayImageService = new DisplayImageService();
		{
			wDisplayImageService->setWindowName("Baluchon");
		}

		wDisplayLayer->addService(wDisplayImageService);
	}

	// Layer 7
    //wWriterLayer = new ServiceLayer();
	//{
		//IWriterService* wWriterService = new VideoWriterService();
		//{
			//wWriterService->disable();
		//}

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
        wEngine->addServiceLayer(wAugmentedInterfaceLayer);
        wEngine->addServiceLayer(wDisplayLayer);
		//wEngine->addServiceLayer(wWriterLayer);

		wEngine->init();
		wEngine->run();
		wEngine->dispose();
	}
	
	//std::cin.get();

	return EXIT_SUCCESS;
}