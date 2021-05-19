//
// Created by Sakura on 4/11/2021.
//

#ifndef A67_913ALICEHINCU_CONSOLEUI_H
#define A67_913ALICEHINCU_CONSOLEUI_H


#include "../service/ServiceAdmin.h"
#include "../service/ServiceUser.h"

class ConsoleUI {
private:
    // for the while loop
    bool _unicorns_exist = true;
    std::string _typeOfFile = "";

    // the service
    ServiceAdmin& _serviceAdmin;
    ServiceUser& _serviceUser;

    // for reading string with spaces
    std::string readString();

    // menu admin
    static void printMenuAdministrator();

    // menu user
    void printMenuUser();

    // run the loop for admin mode
    void runAdministrator();

    // run the loop for user mode
    void runUser();

    // ----------- ADMIN MODE -----------
    void addDogUi();

    void removeDogUi();

    void listDogsUi();

    void updateDogUi();

    // ----------- USER MODE -----------
    void userShowDogUI(const std::vector<Dog> &);

    void userAdoptDogUi();

    void UserNextDogUi(const std::vector<Dog> &dogs);

    void userAdoptionListUi();

    /*void userListDogsUi();

    void userAdoptDogUi();

    void UserNotAdoptDogUi();

    void sortByBreedUi();

    void userAdoptionListUi();*/

public:
    // constructor;
    explicit ConsoleUI(ServiceAdmin&, ServiceUser&);

    // main loop;
    void run();

    // destructor
    ~ConsoleUI();

    std::vector<Dog> sortByBreedUi();

    void userAdoptDogUIFiltered(Dog &dog, std::vector<Dog> &vector);
};



#endif //A67_913ALICEHINCU_CONSOLEUI_H
