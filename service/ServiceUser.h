//
// Created by Sakura on 4/23/2021.
//

#ifndef A67_913ALICEHINCU_SERVICEUSER_H
#define A67_913ALICEHINCU_SERVICEUSER_H


#include <memory>
#include "../repository/RepositoryShelter.h"
#include "../repository/RepositoryAdopted.h"

class ServiceUser {
private:
    std::unique_ptr<RepositoryAdopted> _repoAdopted;
    RepositoryShelter& _repoShelter;
    int currentIndex = 0;
public:
    // constructor
    ServiceUser(RepositoryShelter&);

    // -- getters --
    // return the list of dogs at the shelter
    std::vector<Dog> getShelterDogs();
    // return the list of adopted dogs
    std::vector<Dog> getAdoptedDogs();

    // get current position from the vector
    int getCurrentIndex() const;

    // get the dog from a position from the list of dogs
    Dog getDogAtPosition(int position, std::vector<Dog> dogs);

    // -- setters --
    // increase the current index. if index = size, go back at the first position
    void next();

    // -- functions --
    // remove the dog from the shelter list and add it to the adoption list
    void adoptDogFromShelter();

    // return position of the dog from the given list
    int searchDogFromList(const std::string &name, const std::vector<Dog> &dogs);

    // removes the dog from the given list
    void removeDogFromList(const std::string &name, std::vector<Dog> &dogs);

    // -- files --
    void readFromShelterFile();
    void saveShelterFile();
    void readFromAdoptedFile();
    void saveAdoptedFile();

    std::vector<Dog> getFilteredDogs(const std::string &, int);

    void adoptDogFromShelterAndFiltered(const Dog &, std::vector<Dog>&);

    void setRepoAdopted(std::unique_ptr<RepositoryAdopted>);

    const std::unique_ptr<RepositoryAdopted> &getRepoAdopted() const;
};


#endif //A67_913ALICEHINCU_SERVICEUSER_H
