//
// Created by Sakura on 4/23/2021.
//

#include "ServiceUser.h"
#include <iostream>
#include "fstream"
#include "algorithm"
#include "../validation/Validator.h"

ServiceUser::ServiceUser(RepositoryShelter &repoShelter):
        _repoShelter{repoShelter} {}

std::vector<Dog> ServiceUser::getShelterDogs() {
    return this->_repoShelter.getDogsRepo();
}

std::vector<Dog> ServiceUser::getAdoptedDogs() {
    return this->_repoAdopted->getAdoptedDogsRepo();
}

int ServiceUser::getCurrentIndex() const{
    return this->currentIndex;
}

Dog ServiceUser::getDogAtPosition(int position, std::vector<Dog> dogs){
    return dogs.at(position);
}

void ServiceUser::next() {
    if (this->currentIndex == this->_repoShelter.getNumberOfDogs()-1)
        this->currentIndex = 0;
    else
        this->currentIndex++;
}

void ServiceUser::adoptDogFromShelter() {
    int index = this->getCurrentIndex();
    auto dogs = this->getShelterDogs();
    Dog dog = this->getDogAtPosition(index, dogs);
    this->_repoShelter.removeDogRepo(index);
    this->_repoAdopted->addToAdoptedList(dog);

}

int ServiceUser::searchDogFromList(const std::string &name, const std::vector<Dog>& dogs) {
    int position = 0;

    for (auto & i : dogs){
        if (name == i.get_name())
            break;
        else
            position ++;
    }

    return position;
}


void ServiceUser::removeDogFromList(const std::string &name, std::vector<Dog>& dogs) {
    // get position of the dog
    int position = this->searchDogFromList(name, dogs);

    // remove the dog
    dogs.erase(dogs.begin() + position);
}

std::vector<Dog> ServiceUser::getFilteredDogs(const std::string &breed, int age){
    auto dogs = this->getShelterDogs();
    std::string breedToCompare = breed;
    int ageToCompare = age;

    std::vector<Dog> dogsBreed;
    std::vector<Dog>::iterator it;
    if (!breed.empty()){
        copy_if(dogs.begin(), dogs.end(), std::back_inserter(dogsBreed), [breedToCompare, ageToCompare](const Dog& d)
        {return d.get_age()<ageToCompare && d.get_breed() == breedToCompare;});
    }else{
        copy_if(dogs.begin(), dogs.end(), dogsBreed.begin(), [age](const Dog& d){return d.get_age()<age;});
    }

    return dogsBreed;

}

void ServiceUser::readFromShelterFile(){
    // Read from the text file
    std::ifstream myReadFile("ShelterDogs.txt");
    Dog dog;

    if(myReadFile.is_open()) {
        while (myReadFile.good()){
            myReadFile >> dog;
            this->_repoShelter.addDogRepo(dog);
        }
    }
    // Close the file
    myReadFile.close();
}

void ServiceUser::saveShelterFile(){
    // Create and open a text file
    std::ofstream MyFile("ShelterDogs.txt");

    auto dogs = this->_repoShelter.getDogsRepo();
    int position = 0;
    for (auto const & d : dogs) {
        if (position == 0)
            MyFile << d.get_name() << '\n' << d.get_breed() << '\n' << d.get_age() << '\n' << d.get_photograph();
        else
            MyFile << '\n' << d.get_name() << '\n' << d.get_breed() << '\n' << d.get_age() << '\n' << d.get_photograph();
        position++;
    }
    // Close the file
    MyFile.close();
}

void ServiceUser::readFromAdoptedFile(){
    // Read from the text file
    std::ifstream myReadFile("AdoptedDogs.txt");
    Dog dog;

    if(myReadFile.is_open()) {
        while (myReadFile.good()){
            myReadFile >> dog;
            this->_repoAdopted->addToAdoptedList(dog);
        }
    }
    // Close the file
    myReadFile.close();
}

void ServiceUser::saveAdoptedFile(){
    // Create and open a text file
    std::ofstream MyFile("AdoptedDogs.txt");

    auto dogs = this->_repoAdopted->getAdoptedDogsRepo();
    int position = 0;
    for (auto & d : dogs) {
        if (position == 0)
            MyFile << d.get_name() << '\n' << d.get_breed() << '\n' << d.get_age() << '\n' << d.get_photograph();
        else
            MyFile << '\n' << d.get_name() << '\n' << d.get_breed() << '\n' << d.get_age() << '\n' << d.get_photograph();
        position++;
    }
    // Close the file
    MyFile.close();
}

void ServiceUser::adoptDogFromShelterAndFiltered(const Dog &dog, std::vector<Dog> &filteredList) {
    std::string nameDog = dog.get_name();
    this->removeDogFromList(dog.get_name(), filteredList);
    int index = this->searchDogFromList(nameDog, this->getShelterDogs());
    this->_repoShelter.removeDogRepo(index);
    this->_repoAdopted->addToAdoptedList(dog);
}

void ServiceUser::setRepoAdopted(std::unique_ptr<RepositoryAdopted> repoAdopted) {
    _repoAdopted = std::move(repoAdopted);
}

const std::unique_ptr<RepositoryAdopted> &ServiceUser::getRepoAdopted() const {
    return _repoAdopted;
}

