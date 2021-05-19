//
// Created by Sakura on 4/11/2021.
//

#include <limits>
#include "Dog.h"
#include "../validation/Validator.h"


Dog::Dog(): _name{""}, _breed{""}, _age{-1}, _photograph{""} {}


Dog::Dog(const std::string &name, const std::string &breed, int age, const std::string &photograph):
        _breed{breed}, _name{name}, _age{age}, _photograph{photograph}{}


Dog::Dog(const Dog &d): _breed{d._breed}, _name{d._name}, _age{d._age}, _photograph{d._photograph} {}

Dog &Dog::operator=(const Dog &other) {
    this->_name = other._name;
    this->_breed = other._breed;
    this->_age = other._age;
    this->_photograph = other._photograph;
    return *this;
}

bool Dog::operator==(const Dog &other) const {
    return this->_name == other._name;
}

std::ostream &operator<<(std::ostream &os, const Dog &d) {
    os << "---- Doggy ----\n";
    os << "Name: " << d._name << "\nBreed: " << d._breed << "\nAge: " << d._age << "\nPhoto: " << d._photograph << "\n";
    os << "---------------\n\n";
    return os;
}

std::istream &operator>>(std::istream &is, Dog &d) {
    if (&is == &std::cin)
        std::cout << "Name: ";
    std::getline(is, d._name);
    //d._name.pop_back(); // "get rid of \r

    if (&is == &std::cin)
        std::cout << "Breed: ";
    std::getline(is, d._breed);
    //d._breed.pop_back();

    if (&is == &std::cin)
        std::cout << "Age: ";
    is >> d._age;

    if(!Validator::validateAge(is)){
        while(!Validator::validateAge(is)) {
            std::cout << "Invalid numerical value (age)!\n";
            std::cout << "Correct age: ";
            is >> d._age;
        }
    }
    is.clear();
    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (&is == &std::cin)
        std::cout << "Photo: ";
    std::getline(is, d._photograph);
    //d._photograph.pop_back();

    return is;
}

int Dog::get_age() const {
    return this->_age;
}

const std::string &Dog::get_name() const {
    return this->_name;
}

const std::string &Dog::get_breed() const {
    return this->_breed;
}

const std::string &Dog::get_photograph() const {
    return this->_photograph;
}

void Dog::set_photograph(const std::string &photo) {
    this->_photograph = photo;
}

void Dog::set_age(int age) {
    this->_age = age;
}

Dog::~Dog() = default;
