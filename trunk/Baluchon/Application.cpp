
#include <iostream>

#include "Engine.h"

using namespace baluchon::core::engine::implementations;

int main() {

	printf("Hello World!");

	Engine* wEngine = new Engine();

	std::cin.get();

	return EXIT_SUCCESS;
}