//
// Created by Sakura on 4/11/2021.
//

#include "RepositoryShelter.h"


RepositoryShelter::RepositoryShelter() = default;

void RepositoryShelter::addDogRepo(const Dog& dog) {
    this->_elems.push_back(dog);
}

void RepositoryShelter::updateDogRepo(const Dog &dog, int position) {
    this->_elems.at(position) = dog;
}

void RepositoryShelter::removeDogRepo(int position) {
    this->_elems.erase(this->_elems.begin() + position);
}

std::vector<Dog> RepositoryShelter::getDogsRepo() {
    return this->_elems;
}

int RepositoryShelter::getNumberOfDogs() {
    return this->_elems.size();
}

RepositoryShelter::~RepositoryShelter() = default;