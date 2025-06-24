#include "Stopwatch.h"

Stopwatch::Stopwatch() : deltaTime(0.016f) {
    prevFrame = std::chrono::steady_clock::now();
}

std::shared_ptr<Stopwatch> Stopwatch::getInstance() {
    if (!instance) {
        instance = std::make_shared<Stopwatch>();
    }
    return instance;
}

void Stopwatch::nextFrame() {
    currFrame = std::chrono::steady_clock::now();
    std::chrono::duration<float> duration = currFrame - prevFrame;
    deltaTime = duration.count();
    prevFrame = currFrame;

    if (deltaTime > 0.1f) {
        deltaTime = 0.016f;
    }
}

float Stopwatch::getDeltaTime() const {
    return deltaTime;
}

float Stopwatch::getMovementMultiplier() const {
    return deltaTime * 60.0f;
}