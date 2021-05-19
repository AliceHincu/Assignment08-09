//
// Created by Sakura on 4/11/2021.
//

#ifndef A67_913ALICEHINCU_SERVICEADMIN_H
#define A67_913ALICEHINCU_SERVICEADMIN_H



#include <string>
#include "../repository/RepositoryShelter.h"
#include "../exceptions/Exception.h"
#include "../validation/Validator.h"

class ServiceAdmin {
private:
    RepositoryShelter& _repo;
public:
    // constructor
    explicit ServiceAdmin(RepositoryShelter& repo);

    // ----------- ADMIN MODE -----------
    // validate if the dog exists.
    // if it doesn't exist, add the dog
    // if it exists, throw exception
    void addDog(const std::string&, const std::string&, int, const std::string&);

    // search for a dog by its name.
    // precondition : dog has to exists
    // returns the position of the dog from the vector
    int searchDog(const std::string &name);

    // validate the dog
    // if the dog exists, remove it from list
    // if not, throw exception
    void removeDog(const std::string&);

    // validate the dog
    // if dog exists, update the dog
    // if not, throw exception
    void updateDog(const std::string&, const std::string&, int, const std::string&);

    // return the vector of dogs
    std::vector<Dog> getDogs();

    // destructor
    ~ServiceAdmin();

    void readFromShelterFile();

    void saveShelterFile();
};


#endif //A67_913ALICEHINCU_SERVICEADMIN_H
