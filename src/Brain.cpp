#include "Brain.h"

Brain::Brain() {}

Brain::~Brain() {}

void Brain::loadModel(const std::string& modelPath) {
    (void)modelPath;
}

void Brain::processInput(const std::string& input) {
    lastInput = input;
    mockSendToCoreBrain(input);
}

std::string Brain::generateResponse() {
    return mockReceiveFromCoreBrain();
}

void Brain::mockSendToCoreBrain(const std::string& message) {
    lastCoreBrainResponse = "Placeholder response from local brain: " + message;
}

std::string Brain::mockReceiveFromCoreBrain() {
    return lastCoreBrainResponse;
}
