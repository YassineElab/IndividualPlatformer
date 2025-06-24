#ifndef INDIVIDUALPLATFORMER_STOPWATCH_H

#include <memory>
#include <chrono>

#define INDIVIDUALPLATFORMER_STOPWATCH_H


class Stopwatch {
private:
    static std::shared_ptr<Stopwatch> instance;
    std::chrono::time_point<std::chrono::steady_clock> currFrame;
    std::chrono::time_point<std::chrono::steady_clock> prevFrame;
    float deltaTime;

public:
    Stopwatch();

    static std::shared_ptr<Stopwatch> getInstance();

    void nextFrame();

    float getDeltaTime() const;

    float getMovementMultiplier() const;
};

#endif // INDIVIDUALPLATFORMER_STOPWATCH_H