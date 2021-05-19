//
// Created by Sakura on 4/11/2021.
//

#ifndef A67_913ALICEHINCU_REPOSITORYSHELTER_H
#define A67_913ALICEHINCU_REPOSITORYSHELTER_H


#include <vector>
#include "../domain/Dog.h"

class RepositoryShelter {
private:
    std::vector<Dog> _elems;
public:
    // constructor
    RepositoryShelter();

    // ----------- ADMIN MODE -----------
    void addDogRepo(const Dog&);
    void removeDogRepo(int);
    void updateDogRepo(const Dog&, int);
    std::vector<Dog> getDogsRepo();
    int getNumberOfDogs();

    // destructor
    ~RepositoryShelter();
};


#endif //A67_913ALICEHINCU_REPOSITORYSHELTER_H
