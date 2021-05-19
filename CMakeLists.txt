cmake_minimum_required(VERSION 3.17)
project(a89_913AliceHincu)

set(CMAKE_CXX_STANDARD 14)

include_directories(console)
include_directories(domain)
include_directories(exceptions)
include_directories(repository)
include_directories(service)
include_directories(validation)

set(CMAKE_PREFIX_PATH "C:\\Qt\\5.15.2\\mingw81_64\\lib\\cmake")
find_package(Qt5Widgets REQUIRED)

add_executable(a89_913AliceHincu
        console/ConsoleUI.cpp
        console/ConsoleUI.h
        domain/Dog.cpp
        domain/Dog.h
        exceptions/Exception.cpp
        exceptions/Exception.h
        repository/RepositoryAdopted.cpp
        repository/RepositoryAdopted.h
        repository/RepositoryShelter.cpp
        repository/RepositoryShelter.h
        service/ServiceAdmin.cpp
        service/ServiceAdmin.h
        service/ServiceUser.cpp
        service/ServiceUser.h
        validation/Validator.cpp
        validation/Validator.h
        ShelterDogs.txt
        main.cpp GUI.cpp GUI.h)

target_link_libraries(a89_913AliceHincu Qt5::Widgets)