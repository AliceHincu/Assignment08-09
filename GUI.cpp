//
// Created by Sakura on 5/4/2021.
//

#include <QMessageBox>
#include "GUI.h"

GUI::GUI(ServiceAdmin &aServiceAdmin, ServiceUser &aServiceUser, QWidget *parent): QWidget{parent}, serviceAdmin{aServiceAdmin}, serviceUser{aServiceUser}
{

    //this->serviceUser.setRepoAdopted(std::make_unique<RepositoryAdoptedCsv>());

    this->initGUI();
}

void GUI::initGUI() {
    auto* mainLayout = new QVBoxLayout{this};
    QFont font{ "Verdana", 15 };

    auto* introLabel = new QLabel{"~ Keep calm and adopt a pet ~"};
    introLabel->setAlignment(Qt::AlignCenter);
    introLabel->setFont(font);
    mainLayout->addWidget(introLabel);

    // user admin button
    auto* buttonsWidget = new QWidget{};
    auto* buttonsLayout = new QHBoxLayout{buttonsWidget};
    this->adminModeButton = new QPushButton("Admin Mode");
    this->userModeButton = new QPushButton("User Mode");
    buttonsLayout->addWidget(this->adminModeButton);
    buttonsLayout->addWidget(this->userModeButton);
    mainLayout->addWidget(buttonsWidget);

    // csv html edit
    auto* csvHtmlWidget = new QWidget{};
    auto* csvHtmlLayout = new QFormLayout{ csvHtmlWidget };
    auto* csvHtmlLabel = new QLabel{"&csv/html: "};
    this->csvHtmlEditWidget = new QLineEdit{};
    csvHtmlLabel->setBuddy(this->csvHtmlEditWidget);
    csvHtmlLabel->setFont(font);
    this->csvHtmlEditWidget->setFont(font);
    csvHtmlLayout->addRow(csvHtmlLabel, csvHtmlEditWidget);
    mainLayout->addWidget(csvHtmlWidget);

    QObject::connect(this->adminModeButton, &QPushButton::clicked, this, &GUI::adminGUI);
    QObject::connect(this->userModeButton, &QPushButton::clicked, this, &GUI::userGUI);
}

void GUI::populateDogsList() {
    // count() -> This property holds the number of items in the list including any hidden items.
    // clear() -> Removes all items and selections in the view.
    // clear the list, if there are elements in it

    if(this->dogsListWidget->count() > 0)
        this->dogsListWidget->clear();

    auto dogs = this->serviceAdmin.getDogs();
    for (auto &d: dogs){
        // fromStdString() -> Returns a copy of the str string
        QString itemInList = QString::fromStdString(d.get_name());
        QFont font{"Verdana", 10};

        auto* item = new QListWidgetItem{itemInList};
        item->setFont(font);
        this->dogsListWidget->addItem(item);
    }

    // set the selection on the first item in the list if it's not empty
    if (!dogs.empty())
        this->dogsListWidget->setCurrentRow(0);
}

void GUI::populateAdoptionList() {
    if(this->adoptionListWidget->count() > 0)
        this->adoptionListWidget->clear();
    auto dogs = this->serviceUser.getAdoptedDogs();

    for (auto &d: dogs){
        // fromStdString() -> Returns a copy of the str string
        QString itemInList = QString::fromStdString(d.get_name());
        QFont font{"Verdana", 10};

        auto* item = new QListWidgetItem{itemInList};
        item->setFont(font);
        this->adoptionListWidget->addItem(item);
    }

    // set the selection on the first item in the list if it's not empty
    if (!dogs.empty())
        this->adoptionListWidget->setCurrentRow(0);

}

void GUI::adminGUI() {
    this->adminWidget = new QWidget;
    this->adminWidget->show();
    this->adminWidget->setWindowTitle("Admin Mode ^_^");
    this->hide();

    this->serviceAdmin.readFromShelterFile();

    //General layout of the window
    auto* layout = new QHBoxLayout{ this->adminWidget };

    // ------ LEFT SIDE -------  - just the list
    this->dogsListWidget = new QListWidget{};
    this->dogsListWidget->setMinimumWidth(300);
    this->dogsListWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    layout->addWidget(this->dogsListWidget);

    // ------ RIGHT SIDE ------ - dog information + buttons
    // The QWidget class is the base class of all user interface objects
    auto* rightSide = new QWidget{};
    rightSide->setMinimumWidth(600);
    auto* vLayout = new QVBoxLayout{ rightSide };   // new vertical layout

    // --- dog information ---
    auto* dogDataWidget = new QWidget{};
    auto* formLayout = new QFormLayout{ dogDataWidget };
    // The QLineEdit widget is a one-line text editor.
    // The QTextEdit class provides a widget that is used to edit and display both plain and rich text
    this->dogNameEditWidget = new QLineEdit{};
    this->dogBreedEditWidget = new QLineEdit{};
    this->dogAgeEditWidget = new QLineEdit{};
    this->dogLinkEditWidget = new QTextEdit{};
    QFont font{ "Verdana", 15 };
    // The QLabel widget provides a text or image display.
    auto* dogNameLabel = new QLabel{ "&Dog name: " };
    dogNameLabel->setBuddy(this->dogNameEditWidget);
    dogNameLabel->setFont(font);
    this->dogNameEditWidget->setFont(font);

    auto* dogBreedLabel = new QLabel{ "&Dog breed: " };
    dogBreedLabel->setBuddy(this->dogBreedEditWidget);
    dogBreedLabel->setFont(font);
    this->dogBreedEditWidget->setFont(font);

    auto* dogAgeLabel = new QLabel{ "&Age: " };
    dogAgeLabel->setBuddy(this->dogAgeEditWidget);
    dogAgeLabel->setFont(font);
    this->dogAgeEditWidget->setFont(font);

    auto* dogLinkLabel = new QLabel{"&Link: "};
    dogLinkLabel->setBuddy(this->dogLinkEditWidget);
    dogLinkLabel->setFont(font);
    this->dogLinkEditWidget->setFont(font);

    formLayout->addRow(dogNameLabel, this->dogNameEditWidget);
    formLayout->addRow(dogBreedLabel, this->dogBreedEditWidget);
    formLayout->addRow(dogAgeLabel, this->dogAgeEditWidget);
    formLayout->addRow(dogLinkLabel, this->dogLinkEditWidget);

    vLayout->addWidget(dogDataWidget);

    // --- buttons ---
    auto* buttonsWidget = new QWidget{};

    auto* hLayout = new QGridLayout{ buttonsWidget };
    this->addDogButton = new QPushButton("Add Dog");
    this->addDogButton->setFont(font);
    this->deleteDogButton = new QPushButton("Delete Dog");
    this->deleteDogButton->setFont(font);
    this->updateDogButton = new QPushButton("Update Dog");
    this->updateDogButton->setFont(font);
    this->saveAndExitButton = new QPushButton("Save and exit");
    this->saveAndExitButton->setFont(font);

    QObject::connect(this->addDogButton, &QPushButton::clicked, this, &GUI::addDogButtonHandler);
    QObject::connect(this->deleteDogButton, &QPushButton::clicked, this, &GUI::deleteDogButtonHandler);
    QObject::connect(this->updateDogButton, &QPushButton::clicked, this, &GUI::updateDogButtonHandler);
    QObject::connect(this->saveAndExitButton, &QPushButton::clicked, this, &GUI::saveAndExitButtonHandler);
    // add a connection: function listItemChanged() will be called when an item in the list is selected
    QObject::connect(this->dogsListWidget, &QListWidget::itemSelectionChanged, this, [this]() {this->listItemChanged(); });
    hLayout->addWidget(this->addDogButton, 0, 0);
    hLayout->addWidget(this->deleteDogButton, 0, 1);
    hLayout->addWidget(this->updateDogButton, 1, 0);
    hLayout->addWidget(this->saveAndExitButton, 1, 1);

    vLayout->addWidget(buttonsWidget);

    // add everything to the big layout
    layout->addWidget(this->dogsListWidget);
    layout->addWidget(rightSide);

    this->populateDogsList();

}

void GUI::addDogButtonHandler() {
    // read data from the text boxes and add the new gene
    QString dogName = this->dogNameEditWidget->text();
    QString dogBreed = this->dogBreedEditWidget->text();
    QString dogAge = this->dogAgeEditWidget->text();
    QString dogLink = this->dogLinkEditWidget->toPlainText();

    // emit the addDogSignal signal
    emit addDogSignal(dogName.toStdString(), dogBreed.toStdString(), dogAge.toStdString(), dogLink.toStdString());
}

void GUI::addDogSignal(const std::string &name, const std::string &breed, const std::string &age, const std::string &link) {
    //std::cout << name << " " << breed << " " << age << " " << link << std::endl;
    try {
        this->serviceAdmin.addDog(name, breed, std::stoi(age), link);
    } catch(Exceptions& Error)
    {
        QMessageBox::critical(this, "Error", QString::fromStdString(Error.get_msg()));
        return;
    } catch(std::exception& Error)
    {
        QMessageBox::critical(this, "Error", Error.what());
        return;
    }
    this->populateDogsList();
}

void GUI::deleteDogButtonHandler() {
    if (this->dogsListWidget->count() == 0) {
        QMessageBox::critical(this, "Error", "No more dogs to delete!");
        return;
    }
    // get name of dog
    auto dogDetails = this->getSelectedItem()->text().toStdString();

    this->serviceAdmin.removeDog(dogDetails);
    this->populateDogsList();
}

void GUI::updateDogButtonHandler() {
    if (this->dogsListWidget->count() == 0) {
        QMessageBox::critical(this, "Error", "No more dogs to update!");
        return;
    }
    QString dogName = this->dogNameEditWidget->text();
    QString newDogBreed = this->dogBreedEditWidget->text();
    QString newDogAge = this->dogAgeEditWidget->text();
    QString newDogLink = this->dogLinkEditWidget->toPlainText();

    auto dogDetails = this->getSelectedItem()->text().toStdString();

    try {
        this->serviceAdmin.updateDog(
                dogName.toStdString(),
                newDogBreed.toStdString(),
                std::stoi(newDogAge.toStdString()),
                newDogLink.toStdString());
    } catch(Exceptions& Error)
    {
        QMessageBox::critical(this, "Error", QString::fromStdString(Error.get_msg()));
        return;
    } catch(std::exception& Error)
    {
        QMessageBox::critical(this, "Error", Error.what());
        return;
    }
}

void GUI::saveAndExitButtonHandler(){
    this->serviceAdmin.saveShelterFile();
    QApplication::quit();
}

void GUI::saveAndExitButtonHandler2(){
    this->serviceUser.saveShelterFile();
    this->serviceUser.saveAdoptedFile();
    QApplication::quit();
}

void GUI::listItemChanged()
{
    QModelIndexList selectedIndexes = this->dogsListWidget->selectionModel()->selectedIndexes();
    if(selectedIndexes.empty())
    {
        this->dogNameEditWidget->clear();
        this->dogBreedEditWidget->clear();
        this->dogAgeEditWidget->clear();
        this->dogLinkEditWidget->clear();
    }
    else {
        int selectedIndex = selectedIndexes.at(0).row();
        Dog selectedObject = this->serviceAdmin.getDogs()[selectedIndex];
        this->dogNameEditWidget->setText(QString::fromStdString(selectedObject.get_name()));
        this->dogBreedEditWidget->setText(QString::fromStdString(selectedObject.get_breed()));
        this->dogAgeEditWidget->setText(QString::fromStdString(std::to_string(selectedObject.get_age())));
        this->dogLinkEditWidget->setText(QString::fromStdString(selectedObject.get_photograph()));
    }

}

void GUI::userGUI() {
    this->userWidget = new QWidget;
    this->userWidget->show();
    this->userWidget->setWindowTitle("User Mode ^_^");
    this->hide();
    if(this->csvHtmlEditWidget->text().toStdString() == "html")
        this->serviceUser.setRepoAdopted(std::make_unique<RepositoryAdoptedHtml>());
    else
        this->serviceUser.setRepoAdopted(std::make_unique<RepositoryAdoptedCsv>());

    this->serviceUser.readFromAdoptedFile();
    this->serviceUser.readFromShelterFile();
    this->dogList = this->serviceUser.getShelterDogs();

    // generate layout for the window
    auto* layout = new QHBoxLayout{this->userWidget};

    // --- LEFT SIDE --- - adoption list
    auto* leftSide = new QWidget;
    auto* leftLayout = new QVBoxLayout{leftSide};
    // label
    auto* adoptionListLabel = new QLabel{"Adoption list"};
    QFont font{"Verdana", 15};
    adoptionListLabel->setAlignment(Qt::AlignCenter);
    adoptionListLabel->setFont(font);
    leftLayout->addWidget(adoptionListLabel);
    // list
    this->adoptionListWidget = new QListWidget;
    this->adoptionListWidget->setMinimumWidth(300);
    this->adoptionListWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    leftLayout->addWidget(this->adoptionListWidget);

    auto* csvHtmlButton = new QPushButton("Open list");
    csvHtmlButton->setFont(font);
    this->saveAndExitButton = new QPushButton("Save and exit");
    this->saveAndExitButton->setFont(font);
    this->saveAndExitButton->setFixedWidth(400);

    leftLayout->addWidget(csvHtmlButton);
    QObject::connect(csvHtmlButton, &QPushButton::clicked, this, &GUI::csvButtonHandler);
    // --- RIGHT SIDE --- - dog info
    auto* rightSide = new QWidget{};
    rightSide->setMaximumWidth(500);
    auto* rightLayout = new QVBoxLayout{ rightSide };   // new vertical layout
    // -- label --
    auto* dogInfoLabel = new QLabel{"Current dog information"};
    dogInfoLabel->setAlignment(Qt::AlignHCenter);
    dogInfoLabel->setFont(font);
    dogInfoLabel->setMaximumHeight(50);
    rightLayout->addWidget(dogInfoLabel);
    // --- dog information ---
    auto* dogDataWidget = new QWidget{};
    auto* formLayout = new QFormLayout{ dogDataWidget };

    auto* dogNameLabel = new QLabel{"Name: "};
    this->dogNameLabelInfo = new QLabel{"-"};
    dogNameLabel->setFont(font);
    this->dogNameLabelInfo->setFont(font);
    this->dogNameLabelInfo->setAlignment(Qt::AlignHCenter);

    auto* dogBreedLabel = new QLabel{"Breed: "};
    this->dogBreedLabelInfo = new QLabel{"-"};
    dogBreedLabel->setFont(font);
    this->dogBreedLabelInfo->setFont(font);
    this->dogBreedLabelInfo->setAlignment(Qt::AlignHCenter);

    auto* dogAgeLabel = new QLabel{"Age: "};
    this->dogAgeLabelInfo = new QLabel{"-"};
    dogAgeLabel->setFont(font);
    this->dogAgeLabelInfo->setFont(font);
    this->dogAgeLabelInfo->setAlignment(Qt::AlignHCenter);

    formLayout->addRow(dogNameLabel, this->dogNameLabelInfo);
    formLayout->addRow(dogBreedLabel, this->dogBreedLabelInfo);
    formLayout->addRow(dogAgeLabel, this->dogAgeLabelInfo);
    rightLayout->addWidget(dogDataWidget);

    // --- buttons ---

    auto* buttonsWidget = new QWidget{};

    auto* hLayout = new QGridLayout{ buttonsWidget };
    auto* adoptButton = new QPushButton("Adopt Dog");
    adoptButton->setFont(font);
    adoptButton->setFixedWidth(200);
    auto* nextButton = new QPushButton("Next Dog");
    nextButton->setFont(font);
    nextButton->setFixedWidth(200);
    this->saveAndExitButton = new QPushButton("Save and exit");
    this->saveAndExitButton->setFont(font);
    this->saveAndExitButton->setFixedWidth(400);

    hLayout->addWidget(adoptButton, 0, 0);
    hLayout->addWidget(nextButton, 0, 1);
    hLayout->addWidget(this->saveAndExitButton, 1, 0, 1, 2);
    rightLayout->addWidget(buttonsWidget);

    // for sort
    auto* sortingWidget = new QWidget;
    auto* formLayoutSort = new QFormLayout{ sortingWidget };
    this->breedSortEditWidget = new QLineEdit{};
    this->ageSortEditWidget = new QLineEdit{};

    auto* breedSortLabel = new QLabel{"&Breed: "};
    breedSortLabel->setBuddy(this->breedSortEditWidget);
    breedSortLabel->setFont(font);
    this->breedSortEditWidget->setFont(font);

    auto* ageSortLabel = new QLabel{"&Maximum age: "};
    ageSortLabel->setBuddy(this->ageSortEditWidget);
    ageSortLabel->setFont(font);
    this->ageSortEditWidget->setFont(font);

    formLayoutSort->addRow(breedSortLabel, this->breedSortEditWidget);
    formLayoutSort->addRow(ageSortLabel, this->ageSortEditWidget);

    auto* sortButton = new QPushButton{"Sort"};
    sortButton->setFont(font);
    sortButton->setFixedWidth(400);
    formLayoutSort->addRow(sortButton);

    rightLayout->addWidget(sortingWidget);

    layout->addWidget(leftSide);
    layout->addWidget(rightSide);

    this->populateAdoptionList();
    this->userShowDog();
    QObject::connect(adoptButton, &QPushButton::clicked, this, &GUI::userAdoptDog);
    QObject::connect(nextButton, &QPushButton::clicked, this, &GUI::userNextDog);
    QObject::connect(sortButton, &QPushButton::clicked, this, &GUI::userSortDog);
    QObject::connect(this->saveAndExitButton, &QPushButton::clicked, this, &GUI::saveAndExitButtonHandler2);
}

void GUI::userSortDog(){
    this->userSortWidget = new QWidget();
    this->userSortWidget->show();
    this->userSortWidget->setWindowTitle("User Sort Mode ^_^");
    this->userSortWidget->setMaximumWidth(400);
    this->userSortWidget->setMaximumHeight(400);

    QFont font{"Verdana", 15};
    auto* layout = new QVBoxLayout{ this->userSortWidget };   // new vertical layout
    // -- label --
    auto* dogInfoLabel = new QLabel{"Current dog information-sorted list"};
    dogInfoLabel->setAlignment(Qt::AlignHCenter);
    dogInfoLabel->setFont(font);
    dogInfoLabel->setMaximumHeight(50);
    layout->addWidget(dogInfoLabel);
    // --- dog information ---
    auto* dogDataWidget = new QWidget{};
    auto* formLayout = new QFormLayout{ dogDataWidget };

    auto* dogNameLabel = new QLabel{"Name: "};
    this->dogNameLabelInfoSort = new QLabel{"-"};
    dogNameLabel->setFont(font);
    this->dogNameLabelInfoSort->setFont(font);
    this->dogNameLabelInfoSort->setAlignment(Qt::AlignHCenter);

    auto* dogBreedLabel = new QLabel{"Breed: "};
    this->dogBreedLabelInfoSort = new QLabel{"-"};
    dogBreedLabel->setFont(font);
    this->dogBreedLabelInfoSort->setFont(font);
    this->dogBreedLabelInfoSort->setAlignment(Qt::AlignHCenter);

    auto* dogAgeLabel = new QLabel{"Age: "};
    this->dogAgeLabelInfoSort = new QLabel{"-"};
    dogAgeLabel->setFont(font);
    this->dogAgeLabelInfoSort->setFont(font);
    this->dogAgeLabelInfoSort->setAlignment(Qt::AlignHCenter);

    formLayout->addRow(dogNameLabel, this->dogNameLabelInfoSort);
    formLayout->addRow(dogBreedLabel, this->dogBreedLabelInfoSort);
    formLayout->addRow(dogAgeLabel, this->dogAgeLabelInfoSort);
    layout->addWidget(dogDataWidget);

    // --- buttons ---

    auto* buttonsWidget = new QWidget{};

    auto* hLayout = new QGridLayout{ buttonsWidget };
    auto* adoptButton = new QPushButton("Adopt Dog");
    adoptButton->setFont(font);
    adoptButton->setFixedWidth(200);
    auto* nextButton = new QPushButton("Next Dog");
    nextButton->setFont(font);
    nextButton->setFixedWidth(200);
    this->exitButton = new QPushButton("Exit");
    this->exitButton->setFont(font);
    this->exitButton->setFixedWidth(400);

    hLayout->addWidget(adoptButton, 0, 0);
    hLayout->addWidget(nextButton, 0, 1);
    hLayout->addWidget(this->exitButton, 1, 0, 1, 2);
    layout->addWidget(buttonsWidget);

    // for sort
    //layout->addWidget(rightSide);

    this->populateAdoptionList();
    this->userShowDog();
    QObject::connect(adoptButton, &QPushButton::clicked, this, &GUI::userAdoptDogFiltered);
    QObject::connect(nextButton, &QPushButton::clicked, this, &GUI::userNextDogFiltered);
    QObject::connect(exitButton, &QPushButton::clicked, this, &GUI::userSortExit);

    QString breed = this->breedSortEditWidget->text();
    QString age = this->ageSortEditWidget->text();
    this->dogList = this->serviceUser.getFilteredDogs(breed.toStdString(), std::stoi(age.toStdString()));
    it = dogList.begin();
    this->userShowDogFiltered();

}

void GUI::userShowDog()
{
    auto dogs = this->serviceUser.getShelterDogs();
    if (dogs.empty()){
        QMessageBox::critical(this, "Error", QString::fromStdString("All dogs got adopted!!"));
        this->dogNameLabelInfo->setText(QString::fromStdString("-"));
        this->dogBreedLabelInfo->setText(QString::fromStdString("-"));
        this->dogAgeLabelInfo->setText(QString::fromStdString("-"));
        return;
    }

    int currentIndex = this->serviceUser.getCurrentIndex();
    if (currentIndex == this->dogList.size())
        currentIndex = 0;
    Dog dog = this->serviceUser.getDogAtPosition(currentIndex, dogs);
    this->dogNameLabelInfo->setText(QString::fromStdString(dog.get_name()));
    this->dogBreedLabelInfo->setText(QString::fromStdString(dog.get_breed()));
    this->dogAgeLabelInfo->setText(QString::fromStdString(std::to_string(dog.get_age())));
    system(("start " + dog.get_photograph()).c_str());
}

void GUI::userShowDogFiltered()
{
    if (this->dogList.empty()){
        QMessageBox::critical(this, "Error", QString::fromStdString("All dogs got adopted from this list!!"));
        this->dogNameLabelInfoSort->setText(QString::fromStdString("-"));
        this->dogBreedLabelInfoSort->setText(QString::fromStdString("-"));
        this->dogAgeLabelInfoSort->setText(QString::fromStdString("-"));
        return;
    }
    Dog dog = *it;
    this->dogNameLabelInfoSort->setText(QString::fromStdString(dog.get_name()));
    this->dogBreedLabelInfoSort->setText(QString::fromStdString(dog.get_breed()));
    this->dogAgeLabelInfoSort->setText(QString::fromStdString(std::to_string(dog.get_age())));
    system(("start " + dog.get_photograph()).c_str());
}

void GUI::userAdoptDog()
{
    auto dogs = this->serviceUser.getShelterDogs();
    if (dogs.empty()){
        QMessageBox::critical(this, "Error", QString::fromStdString("All dogs got adopted!!"));
        this->dogNameLabelInfo->setText(QString::fromStdString("-"));
        this->dogBreedLabelInfo->setText(QString::fromStdString("-"));
        this->dogAgeLabelInfo->setText(QString::fromStdString("-"));
        return;
    }

    this->serviceUser.adoptDogFromShelter();
    QMessageBox::information(this, "Info", QString::fromStdString("Dog adopted!"));
    this->userShowDog();
    this->populateAdoptionList();
}

void GUI::userAdoptDogFiltered()
{
    auto dogs = this->dogList;
    if (dogs.empty()){
        QMessageBox::critical(this, "Error", QString::fromStdString("All dogs got adopted!!"));
        this->dogNameLabelInfo->setText(QString::fromStdString("-"));
        this->dogBreedLabelInfo->setText(QString::fromStdString("-"));
        this->dogAgeLabelInfo->setText(QString::fromStdString("-"));
        return;
    }
    Dog dog = *it;
    this->serviceUser.adoptDogFromShelterAndFiltered(dog, this->dogList);
    QMessageBox::information(this, "Info", QString::fromStdString("Dog adopted!"));
    this->userShowDogFiltered();
}

void GUI::userNextDog()
{
    auto dogs = this->serviceUser.getShelterDogs();
    if (dogs.empty()){
        QMessageBox::critical(this, "Error", QString::fromStdString("All dogs got adopted!!"));
        this->dogNameLabelInfo->setText(QString::fromStdString("-"));
        this->dogBreedLabelInfo->setText(QString::fromStdString("-"));
        this->dogAgeLabelInfo->setText(QString::fromStdString("-"));
        return;
    }

    this->serviceUser.next();
    int currentIndex = this->serviceUser.getCurrentIndex();
    Dog dog = this->serviceUser.getDogAtPosition(currentIndex, dogs);
    this->userShowDog();
}

void GUI::userNextDogFiltered(){
    if (this->dogList.empty()){
        QMessageBox::critical(this, "Error", QString::fromStdString("All dogs got adopted!!"));
        this->dogNameLabelInfo->setText(QString::fromStdString("-"));
        this->dogBreedLabelInfo->setText(QString::fromStdString("-"));
        this->dogAgeLabelInfo->setText(QString::fromStdString("-"));
        return;
    }

    ++this->it;
    if(this->it == (this->dogList.end()))
        this->it = this->dogList.begin();
    this->userShowDogFiltered();
}

void GUI::userSortExit(){
    this->dogList = this->serviceUser.getShelterDogs();
    this->userSortWidget->hide();
    this->populateAdoptionList();
    this->userShowDog();
}

int GUI::getSelectedIndex()
{
    if (this->dogsListWidget->count() == 0)
        return -1;

    // get selected index
    QModelIndexList index = this->dogsListWidget->selectionModel()->selectedIndexes();
    if (index.empty())
    {
        this->dogNameEditWidget->clear();
        this->dogBreedEditWidget->clear();
        this->dogAgeEditWidget->clear();
        this->dogLinkEditWidget->clear();
        return -1;
    }

    int idx = index.at(0).row();
    return idx;
}

void GUI::csvButtonHandler(){
    this->serviceUser.getRepoAdopted()->write();
    this->serviceUser.getRepoAdopted()->display();
}

void GUI::htmlButtonHandler(){
    this->serviceUser.getRepoAdopted()->write();
    this->serviceUser.getRepoAdopted()->display();
}

QListWidgetItem* GUI::getSelectedItem() {
    return this->dogsListWidget->selectedItems()[0];
}

GUI::~GUI() = default;
