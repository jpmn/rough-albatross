#include <iostream>
#include <time.h>
#include <highgui.h>

#include "Engine.h"

namespace baluchon { namespace core { namespace engine {

Engine::Engine(void) {

}

Engine::~Engine(void) {

}

void Engine::init(void) {

	// Initialization
	for (unsigned int i = 0; i < mListServiceLayers.size(); i++) {
		vector<IService*> wServices = mListServiceLayers[i]->getServices();

		for (unsigned int j = 0; j < wServices.size(); j++) {
			wServices[j]->init();
		}
	}

	// Initialization Done
	for (unsigned int i = 0; i < mListServiceLayers.size(); i++) {
		vector<IService*> wServices = mListServiceLayers[i]->getServices();

		for (unsigned int j = 0; j < wServices.size(); j++) {
			wServices[j]->initDone();
		}
	}
}

void Engine::run(void) {
	char exitKey = 0;

	while (exitKey != mExitKey) {
		clock_t start = clock();

		for (unsigned int i = 0; i < mListServiceLayers.size(); i++) {
			vector<IService*> wServices = mListServiceLayers[i]->getServices();

			for (unsigned int j = 0; j < wServices.size(); j++) {

				if (wServices[j]->isEnabled())
					wServices[j]->execute();
			}
		}

		exitKey = cvWaitKey(10);

		clock_t elapsed = clock() - start;
        long int timeMs = (long) (((float)elapsed) / ((float)CLOCKS_PER_SEC) * 1000.0f);
		printf("Engine::FPS %f\n", 1000.0f / timeMs);
	}
}

void Engine::reset(void) {
	
	for (unsigned int i = 0; i < mListServiceLayers.size(); i++) {
		vector<IService*> wServices = mListServiceLayers[i]->getServices();

		for (unsigned int j = 0; j < wServices.size(); j++) {
			wServices[j]->reset();
		}
	}
}

void Engine::dispose(void) {

	for (unsigned int i = 0; i < mListServiceLayers.size(); i++) {
		vector<IService*> wServices = mListServiceLayers[i]->getServices();

		for (unsigned int j = 0; j < wServices.size(); j++) {
			wServices[j]->dispose();
		}
	}
}

void Engine::setExitKey(char exitKey) {
	mExitKey = exitKey;
}

void Engine::addServiceLayer(IServiceLayer* serviceLayer) {
    if(!mListServiceLayers.empty())
    {
        serviceLayer->setLowerLayer(mListServiceLayers.back());
    }
	mListServiceLayers.push_back(serviceLayer);
}

}}};