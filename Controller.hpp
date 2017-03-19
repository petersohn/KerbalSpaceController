#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

class Joystick_;

template<typename Processor>
void processElements(Joystick_& joystick, Processor elements[]) {
    for (Processor* element = elements; element->isValid(); ++element) {
        element->process(joystick);
    }
}

#endif // CONTROLLER_HPP
