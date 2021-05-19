//
// Created by Sakura on 4/22/2021.
//

#include <limits>
#include "Validator.h"

bool Validator::validateExistenceOfDog(const std::vector<Dog>& dogs, const std::string &name) {
    for (auto & i : dogs){
        if (name == i.get_name()) {
            return true;
        }
    }
    return false;
}

bool Validator::validateAge(std::istream &is) {
    if (is.fail()) {
        is.clear();
        is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }
    return true;
}
