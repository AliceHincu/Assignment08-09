//
// Created by Sakura on 4/22/2021.
//

#ifndef A67_913ALICEHINCU_VALIDATOR_H
#define A67_913ALICEHINCU_VALIDATOR_H

#include "../service/ServiceAdmin.h"
#include "vector"

class Validator {
private:
    //
public:
    // validates the dog given (called from the service)
    // if the dog exists, it will return true. If the dog doesn't exist, it will return false
    static bool validateExistenceOfDog(const std::vector<Dog>&, const std::string &);

    // validates if the age is Integer
    // if not, return false
    // if it is integer, return true
    static bool validateAge(std::istream &);
};


#endif //A67_913ALICEHINCU_VALIDATOR_H
