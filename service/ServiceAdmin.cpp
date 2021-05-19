//
// Created by Sakura on 4/11/2021.
//

#include "ServiceAdmin.h"
#include "iostream"
#include "fstream"

ServiceAdmin::ServiceAdmin(RepositoryShelter& repo): _repo{repo} {}

void ServiceAdmin::addDog(const std::string &name, const std::string &breed, int age, const std::string &photograph) {
    // create the dog
    Dog dog{name, breed, age, photograph};

    // validate
    if (Validator::validateExistenceOfDog(this->_repo.getDogsRepo(), dog.get_name()))
            throw Exceptions("Dog already exists!\n\n");


    // add the dog
    this->_repo.addDogRepo(dog);
}

int ServiceAdmin::searchDog(const std::string &name) {
    int position = 0;

    auto dogs = this->_repo.getDogsRepo();
    for (auto & i : dogs){
        if (name == i.get_name())
            break;
        else
            position ++;
    }

    return position;
}


void ServiceAdmin::removeDog(const std::string &name) {
    // validate
    if (!Validator::validateExistenceOfDog(this->_repo.getDogsRepo(), name))
        throw Exceptions("Dog does not exist!\n\n");

    // get position of the dog
    int position = searchDog(name);

    // remove the dog
    this->_repo.removeDogRepo(position);
}


void ServiceAdmin::updateDog(const std::string& name, const std::string& newBreed, int newAge, const std::string& newPhoto) {
    // validate
    if (!Validator::validateExistenceOfDog(this->_repo.getDogsRepo(), name))
        throw Exceptions("Dog does not exist!\n\n");

    // get position of the dog
    int position = searchDog(name);

    // update the dog
    Dog dog{name, newBreed, newAge, newPhoto};
    this->_repo.updateDogRepo(dog, position);
}


std::vector<Dog> ServiceAdmin::getDogs() {
    return this->_repo.getDogsRepo();
}

void ServiceAdmin::readFromShelterFile(){
    // Read from the text file
    std::ifstream myReadFile("ShelterDogs.txt");
    Dog dog;

    if(myReadFile.is_open()) {
        while (myReadFile.good()){
            myReadFile >> dog;
            this->_repo.addDogRepo(dog);
        }
    }
    // Close the file
    myReadFile.close();
}

void ServiceAdmin::saveShelterFile(){
    // Create and open a text file
    std::ofstream MyFile("ShelterDogs.txt");

    auto dogs = this->_repo.getDogsRepo();
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
ServiceAdmin::~ServiceAdmin() = default;
