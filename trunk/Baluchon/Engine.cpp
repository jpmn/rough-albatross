#include <iostream>
#include <time.h>
#include <highgui.h>

#include "Engine.h"

namespace baluchon { namespace core { namespace engine { namespace implementations {

Engine::Engine(void) {

}

Engine::~Engine(void) {

}

void Engine::init(void) {
	// TODO : initialiser les services
}

void Engine::run(void) {
	char exitKey = 0;

	while (exitKey != mExitKey) {
		clock_t start = clock();

		// TODO : executer les services

		exitKey = cvWaitKey(10);

		clock_t elapsed = clock() - start;
        long int timeMs = ((float)elapsed) / ((float)CLOCKS_PER_SEC) * 1000.0f;
		printf("Engine::FPS %f\n", 1000.0f / timeMs);
	}
}

void Engine::reset(void) {

}

void Engine::dispose(void) {

}

void Engine::setExitKey(char exitKey) {
	mExitKey = exitKey;
}

void Engine::addServiceLayer(IServiceLayer* serviceLayer) {
	serviceLayer->setLowerLayer(mListServiceLayer.back());
	mListServiceLayer.push_back(serviceLayer);
}

}}}};