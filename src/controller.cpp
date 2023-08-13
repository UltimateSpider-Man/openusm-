#include "controller.h"

controller::controller()
{

}

void controller::kill() {
    this->field_4 = false;
}

void controller::resurrect() {
    this->field_4 = true;
}
