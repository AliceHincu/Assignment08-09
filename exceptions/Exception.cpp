//
// Created by Sakura on 4/13/2021.
//

#include "Exception.h"

Exceptions::Exceptions(std::string msg): std::exception(), _msg{std::move(msg)} {}

const std::string &Exceptions::get_msg() const {
    return this->_msg;
}