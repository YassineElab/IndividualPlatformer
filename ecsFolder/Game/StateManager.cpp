#include "StateManager.h"

StateManager::StateManager() {
    add = false;
    remove = false;
    topReplacement = false;
}

void StateManager::addState(shared_ptr<State> newState1, bool topReplacement1) {
    add = true;
    topReplacement = topReplacement1;
    newState = std::move(newState1);
}

void StateManager::removeState() {
    remove = true;
}

void StateManager::stateChanges() {
    if(add){
        if(!states.empty() and topReplacement){
            states.pop();
        }
        states.push(newState);
        states.top()->init();
        add = false;
    }
    if(!states.empty() and remove){
        states.pop();
        remove = false;
    }

}

shared_ptr<State> StateManager::getActiveState() {
    return states.top();
}