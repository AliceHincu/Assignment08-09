//
// Created by Sakura on 4/13/2021.
//

#ifndef A67_913ALICEHINCU_EXCEPTION_H
#define A67_913ALICEHINCU_EXCEPTION_H


#include <exception>
#include <string>

class Exceptions : public std::exception {
private:
    std::string _msg;
public:
    Exceptions(std::string  msg);
    const std::string& get_msg() const;
};


#endif //A67_913ALICEHINCU_EXCEPTION_H
