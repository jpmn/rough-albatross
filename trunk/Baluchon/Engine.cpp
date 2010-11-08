#include <iostream>
#include <time.h>
#include <highgui.h>

#include "Engine.h"

namespace Baluchon { namespace Core { namespace Engine { namespace Implementations {

Engine::Engine(void) {

}

Engine::~Engine(void) {

}

void Engine::Init(void) {
	// TODO : Initialiser les services
}

void Engine::Run(void) {
	char exitKey = 0;

	while (exitKey != mExitKey) {
		clock_t start = clock();

		// TODO : Executer les services

		exitKey = cvWaitKey(10);

		clock_t elapsed = clock() - start;
        long int timeMs = ((float)elapsed) / ((float)CLOCKS_PER_SEC) * 1000.0f;
		printf("Engine::FPS %f\n", 1000.0f / timeMs);
	}
}

void Engine::Reset(void) {

}

void Engine::Dispose(void) {

}

void Engine::SetExitKey(char exitKey) {
	mExitKey = exitKey;
}

void Engine::AddServiceLayer(IServiceLayer* serviceLayer) {
	serviceLayer->SetLowerLayer(mListServiceLayer.back());
	mListServiceLayer.push_back(serviceLayer);
}

}}}};