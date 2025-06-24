#ifndef INDIVIDUALPLATFORMER_CONTROLLERV_H

#include <string>

#define INDIVIDUALPLATFORMER_CONTROLLERV_H

class ControllerV {
public:
    virtual ~ControllerV() = default;
    virtual bool isOpen() = 0;
    virtual void checkForClose() = 0;
};

#endif //INDIVIDUALPLATFORMER_CONTROLLERV_H
