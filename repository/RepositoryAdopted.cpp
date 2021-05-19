//
// Created by Sakura on 4/23/2021.
//

#include "RepositoryAdopted.h"
#include "fstream"

void RepositoryAdopted::addToAdoptedList(const Dog& dog) {

    this->_adoptedDogs.push_back(dog);

}

std::vector<Dog> RepositoryAdopted::getAdoptedDogsRepo() {
    return this->_adoptedDogs;
}

void RepositoryAdoptedCsv::write() {
    remove( "adoptionList.csv" );
    std::ofstream fout("adoptionList.csv", std::ios::app);

    for (auto & i : this->_adoptedDogs){
        fout << i.get_name() << ", " << i.get_breed() << ", " << i.get_age() << ", " << i.get_photograph() << "\n";
    }
    fout.close();
}

void RepositoryAdoptedCsv::display() {
    system("start adoptionList.csv");
}

void RepositoryAdoptedHtml::write() {
    remove( "adoptionList.html" );
    std::ofstream fout("adoptionList.html", std::ios::app);
    fout << "<!DOCTYPE html>" << std::endl;
    fout << "<html>" << std::endl;
    fout << "<head>" << std::endl;
    fout << "    <title>Adoption List</title>" << std::endl;
    fout << "</head>" << std::endl;
    fout << "<body>" << std::endl;
    fout << "<table border=\"1\">" << std::endl;

    for (auto & i : this->_adoptedDogs){
        fout << "    <tr>" << std::endl;
        fout << "        <td>"+i.get_name()+"</td>" << std::endl;
        fout << "        <td>"+i.get_breed()+"</td>" << std::endl;
        fout << "        <td>" << i.get_age() << "</td>" << std::endl;
        fout << "        <td><a href=\""+i.get_photograph()+"\">Link</a></td>" << std::endl;
        fout << "    </tr>" << std::endl;
    }

    fout << "</table>" << std::endl;
    fout << "</body>" << std::endl;
    fout << "</html>" << std::endl;
    fout.close();
}

void RepositoryAdoptedHtml::display() {
    system("start adoptionList.html");
}
