//
// Created by Sakura on 4/11/2021.
//

#include <limits>
#include <fstream>
#include "ConsoleUI.h"


ConsoleUI::ConsoleUI(ServiceAdmin& serviceAdmin, ServiceUser& serviceUser): _unicorns_exist{true},
                                                                            _serviceAdmin{serviceAdmin},
                                                                            _serviceUser{serviceUser}{}


std::string ConsoleUI::readString() {
    std::string input;
    std::getline(std::cin, input);
    return input;
}

void ConsoleUI::run() {
    while (this->_unicorns_exist){
        std::cout << "Choose a mode(HTML/CSV): ";
        std::string mode;
        mode = readString();
        if (mode == "CSV") {
            this->_serviceUser.setRepoAdopted(std::make_unique<RepositoryAdoptedCsv>());
            this->_unicorns_exist = false;
            continue;
        }
        else if (mode == "HTML"){
            this->_serviceUser.setRepoAdopted(std::make_unique<RepositoryAdoptedHtml>());
            this->_unicorns_exist = false;
            continue;
        }
        std::cout << "Wrong mode!";
    }
    this->_unicorns_exist = true;
    while (this->_unicorns_exist){
        std::cout << "Choose a mode(administrator/user): ";
        std::string mode;
        mode = readString();
        if (mode == "administrator" or mode == "admin") {
            this->runAdministrator();
            continue;
        }
        if (mode == "user") {
            this->runUser();
            continue;
        }
        std::cout << "Wrong mode!";
    }

}

void ConsoleUI::printMenuAdministrator() {
    std::string menu = "|-----------------------------------|\n"
                       "|   ~ Keep calm and adopt a pet ~   |\n"
                       "|-----------------------------------|\n"
                       "|         1. Add a new dog          |\n"
                       "|         2. Delete a dog           |\n"
                       "|         3. Update a dog           |\n"
                       "|         4. See all dogs           |\n"
                       "|         0. Exit                   |\n"
                       "|-----------------------------------|\n";
    std::cout << menu;

}

void ConsoleUI::printMenuUser() {
    std::string menu = "|-----------------------------------|\n"
                       "|   ~ Keep calm and adopt a pet ~   |\n"
                       "|-----------------------------------|\n"
                       "|         1. See the dogs           |\n"
                       "|         2. Adopt the dog          |\n"
                       "|         3. Don't adopt            |\n"
                       "|         5. See breed              |\n"
                       "|         4. See adoption list      |\n"
                       "|         0. Exit                   |\n"
                       "|-----------------------------------|\n";
    std::cout << menu;
}

// ------- ADMIN ------------
void ConsoleUI::runAdministrator() {
    this->_serviceAdmin.readFromShelterFile();
    while (this->_unicorns_exist){
        this->printMenuAdministrator();
        std::cout << ">>> ";
        std::string option;
        option = readString();
        if (option == "0") {
            this->_unicorns_exist = false;
            this->_serviceAdmin.saveShelterFile();
            continue;
        }
        if (option == "1") {
            this->addDogUi();
            continue;
        }
        if (option == "2") {
            this->removeDogUi();
            continue;
        }
        if(option == "3"){
            this->updateDogUi();
            continue;
        }
        if(option=="4"){
            this->listDogsUi();
            continue;
        }
        std::cout << "\nWrong command!\n";
    }
}

void ConsoleUI::addDogUi() {
    Dog dog;
    std::cin >> dog;
    try {
        this->_serviceAdmin.addDog(dog.get_name(), dog.get_breed(), dog.get_age(), dog.get_photograph());
        std::cout << "Dog added!\n";
    }catch(Exceptions &serviceException){
        std::cout << serviceException.get_msg();
    }
}

void ConsoleUI::removeDogUi() {
    std::string name;
    std::cout << "Name of the existing dog: ";
    name = readString();

    try {
        this->_serviceAdmin.removeDog(name);
        std::cout << "Yaaay it got adopted o(^_^)o!!!! \n";
    }catch(Exceptions &serviceException){
        std::cout << serviceException.get_msg();
    }
}

void ConsoleUI::updateDogUi() {
    std::string breed, name, photograph;
    int age;

    std::cout << "Name of the existing dog: "; name = readString();
    std::cout << "New Breed: "; breed = readString();
    std::cout << "New Age: ";
    while(!Validator::validateAge(std::cin)){
        std::cout << "Invalid numerical value (age)!\n";
        std::cout << "Correct age: "; std::cin >> age;
    }
    std::cout << "New Photograph: "; std::cin>> photograph;

    try {
        this->_serviceAdmin.updateDog(name, breed, age, photograph);
        std::cout << "Dog updated!\n";
    }catch(Exceptions &serviceException){
        std::cout << serviceException.get_msg();
    }
}

void ConsoleUI::listDogsUi() {
    auto dogs = this->_serviceAdmin.getDogs();
    for (auto & i : dogs){
        std::cout << i;
    }
}

// -------- USER ------------
void ConsoleUI::runUser(){
    this->_serviceUser.readFromShelterFile();
    this->_serviceUser.readFromAdoptedFile();
    while (this->_unicorns_exist){
        this->printMenuUser();
        std::cout << ">>> ";
        std::string option;
        std::cin >> option;
        if (option == "0") {
            this->_unicorns_exist = false;
            this->_serviceUser.saveShelterFile();
            this->_serviceUser.saveAdoptedFile();
            continue;
        }
        if (option == "1") {
            this->userShowDogUI(this->_serviceUser.getShelterDogs());
            continue;
        }
        if (option == "2") {
            this->userAdoptDogUi();
            continue;
        }
        if(option == "3"){
            this->UserNextDogUi(this->_serviceUser.getShelterDogs());
            continue;
        }
        if(option == "4"){
            this->userAdoptionListUi();
            continue;
        }
        if(option == "5"){
            std::vector<Dog> filteredList = this->sortByBreedUi();
            std::cout << "\n0. Exit list\n1. Adopt\n2. Don't adopt\n3. See adoption List\n";
            for (auto it=filteredList.begin(); it!=filteredList.end(); ++it){
                std::cout << "   Current dog\n"<< *it;
                system(("start " + it->get_photograph()).c_str());
                std::cout << ">>> ";
                std::string option2;
                std::cin >> option2;

                if (option2 == "0") {
                    break;
                }
                if (option2 == "1") {
                    Dog dog = *it;
                    this->userAdoptDogUIFiltered(dog, filteredList);
                    it--;
                    if (filteredList.empty()){
                        std::cout << "All dogs from this list got adopted!\n";
                    }
                    continue;
                }
                if (option2 == "2") {
                    if(it == (filteredList.end()-1))
                        it = filteredList.begin()-1;
                    continue;
                }
                if (option2 == "3") {
                    this->userAdoptionListUi();
                    it--;
                    continue;
                }
            }
            continue;
        }
        std::cout << "\nWrong command!\n";
    }
}

void ConsoleUI::userShowDogUI(const std::vector<Dog>& dogs){
    if (dogs.empty()){
        std::cout << "\nAll dogs got adopted!!\n";
        return;
    }

    int currentIndex = this->_serviceUser.getCurrentIndex();
    Dog dog = this->_serviceUser.getDogAtPosition(currentIndex, dogs);
    std::cout << dog;
    system(("start " + dog.get_photograph()).c_str());
}

void ConsoleUI::userAdoptDogUi() {
    if (this->_serviceUser.getShelterDogs().empty()){
        std::cout << "\nAll dogs got adopted yaay!!!\n";
        return;
    }

    this->_serviceUser.adoptDogFromShelter();
    std::cout << "Dog adopted!\n"; //then go the next dog
}

void ConsoleUI::UserNextDogUi(const std::vector<Dog>& dogs) {
    if (dogs.empty()){
        std::cout << "\nAll dogs got adopted yaay!!!\n";
        return;
    }

    this->_serviceUser.next();
    int currentIndex = this->_serviceUser.getCurrentIndex();
    Dog dog = this->_serviceUser.getDogAtPosition(currentIndex, dogs);
    std::cout << "\nNext dog:\n";
    std::cout << dog;

    system(("start " + dog.get_photograph()).c_str());

}

void ConsoleUI::userAdoptionListUi() {
    std::cout<<"   Adoption list:\n";
    auto dogs = this->_serviceUser.getAdoptedDogs();

    this->_serviceUser.getRepoAdopted()->write();
    this->_serviceUser.getRepoAdopted()->display();
}

std::vector<Dog> ConsoleUI::sortByBreedUi() {
    std::cout << "See all the dogs of a given breed, having an age less than a given number. If no breed is"
                 " provided, then all the dogs will be considered. The functionalities outlined above apply "
                 "again in this case.\n";
    std::cout << "Input breed: ";
    std::string breed;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    breed = readString();
    int age;
    std::cout << "Age: ";
    while(!(std::cin >> age)){
        std::cout << "Invalid numerical value (age)!\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Age: ";
    }

    auto filteredList = this->_serviceUser.getFilteredDogs(breed, age);
    return filteredList;
}

void ConsoleUI::userAdoptDogUIFiltered(Dog& dog, std::vector<Dog> &filteredList) {
    if (filteredList.empty()){
        std::cout << "\nAll dogs got adopted yaay!!!\n";
        return;
    }

    this->_serviceUser.adoptDogFromShelterAndFiltered(dog, filteredList);
    std::cout << "Dog adopted!\n"; //then go the next dog
}

ConsoleUI::~ConsoleUI() = default;
