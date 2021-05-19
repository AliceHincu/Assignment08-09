//
// Created by Sakura on 4/11/2021.
//

#ifndef A67_913ALICEHINCU_DOG_H
#define A67_913ALICEHINCU_DOG_H


#include <string>
#include <iostream>

class Dog{
private:
    std::string _breed;
    std::string _name;
    int _age;
    std::string _photograph;

public:
    //constructor
    Dog();

    Dog(const std::string &, const std::string &, int, const std::string &);

    //operators
    Dog &operator=(const Dog &);

    bool operator==(const Dog &) const;

    //ostream = orice fel de string de output
    //trb sa fie prieteni ca sa acceseze din clasele alea
    friend std::ostream &operator<<(std::ostream &, const Dog &);

    friend std::istream &operator>>(std::istream &, Dog &);

    //constructor de copiere
    Dog(const Dog &);

    //getters
    int get_age() const;

    const std::string &get_name() const;

    const std::string &get_breed() const;

    const std::string &get_photograph() const;

    //setters - name must not be modified
    void set_photograph(const std::string &);

    void set_age(int age);


    //destructor
    ~Dog();
};

#endif //A67_913ALICEHINCU_DOG_H
