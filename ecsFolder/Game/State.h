#ifndef INDIVIDUALPLATFORMER_STATE_H

#define INDIVIDUALPLATFORMER_STATE_H

class State{
public:
    virtual void draw() = 0;
    virtual void update() = 0;
    virtual void init() = 0;
    virtual void inputController() = 0;
};

#endif //INDIVIDUALPLATFORMER_STATE_H
