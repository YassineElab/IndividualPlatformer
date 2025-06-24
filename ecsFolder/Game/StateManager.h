#ifndef INDIVIDUALPLATFORMER_STATEMANAGER_H

#include "stack"
#include "memory"
#include "State.h"

#define INDIVIDUALPLATFORMER_STATEMANAGER_H


using namespace std;

class StateManager{
private:
    stack<shared_ptr<State>> states;
    shared_ptr<State> newState;

    bool add = false;
    bool remove = false;
    bool topReplacement = false;

public:
    StateManager();
    void addState(shared_ptr<State> newState1, bool topReplacement1 = true);
    void removeState();
    void stateChanges();
    shared_ptr<State> getActiveState();
};

#endif //INDIVIDUALPLATFORMER_STATEMANAGER_H
