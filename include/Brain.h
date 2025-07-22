#pragma once
#include <string>

class Brain {
public:
    Brain();
    ~Brain();

    void loadModel(const std::string& path);

    void processInput(const std::string& input);

    std::string generateResponse();

private:
    std::string lastInput;

    void mockSendToCoreBrain(const std::string& message);

    std::string mockReceiveFromCoreBrain();

    std::string lastCoreBrainResponse;
};
