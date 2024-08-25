//
// Created by gerw on 8/21/24.
//

#include "Mountable.h"

void Mountable::unmount() {
    mounted = false;
}

bool Mountable::isMounted() const {
    return mounted;
}

void Mountable::mountToParent() {
    mounted = true;
}
