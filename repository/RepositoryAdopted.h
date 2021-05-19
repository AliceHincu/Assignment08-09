//
// Created by Sakura on 4/23/2021.
//

#ifndef A67_913ALICEHINCU_REPOSITORYADOPTED_H
#define A67_913ALICEHINCU_REPOSITORYADOPTED_H


#include <vector>
#include "../domain/Dog.h"

class RepositoryAdopted {
protected:
    std::vector<Dog> _adoptedDogs;
public:
    // get the list of the adopted dogs
    std::vector<Dog> getAdoptedDogsRepo();

    // add to the list an adopted dog
    void addToAdoptedList(const Dog& dog);

    virtual void write(){}

    virtual void display(){}
};

class RepositoryAdoptedCsv : public RepositoryAdopted{
public:
    void write() override;

    void display() override;

};


class RepositoryAdoptedHtml : public RepositoryAdopted{
public:
    void write() override;

    void display() override;

};

#endif //A67_913ALICEHINCU_REPOSITORYADOPTED_H
