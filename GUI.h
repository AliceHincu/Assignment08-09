//
// Created by Sakura on 5/4/2021.
//

#ifndef A89_913ALICEHINCU_GUI_H
#define A89_913ALICEHINCU_GUI_H


#include <ServiceAdmin.h>
#include <ServiceUser.h>
#include <qwidget.h>
#include <QListWidget>
#include <QFormLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QLabel>
#include <QApplication>


class GUI: public QWidget {
        //for any non-templated classes that derive from QObject (ex:signals and slots)
        //Q_OBJECT
private:
    ServiceAdmin& serviceAdmin;
    ServiceUser& serviceUser;

    // widget for showing the list of dogs (only name + breed)
    QListWidget* dogsListWidget{};
    QListWidget* adoptionListWidget{};
    QWidget* adminWidget{};
    QWidget* userWidget{};
    QWidget* userSortWidget{};
    QLineEdit* dogNameEditWidget{};
    QLineEdit* dogBreedEditWidget{};
    QLineEdit* dogAgeEditWidget{};
    QLineEdit* breedSortEditWidget{};
    QLineEdit* ageSortEditWidget{};
    QLineEdit* csvHtmlEditWidget;
    QTextEdit* dogLinkEditWidget{};
    QLabel* dogNameLabelInfo{};
    QLabel* dogNameLabelInfoSort{};
    QLabel* dogBreedLabelInfo{};
    QLabel* dogBreedLabelInfoSort{};
    QLabel* dogAgeLabelInfo{};
    QLabel* dogAgeLabelInfoSort{};

    QPushButton* adminModeButton{};
    QPushButton* userModeButton{};
    QPushButton* addDogButton{};
    QPushButton* deleteDogButton{};
    QPushButton* updateDogButton{};
    QPushButton* saveAndExitButton{};
    QPushButton* exitButton{};

    std::vector<Dog> dogList;
    std::vector<Dog>::iterator it;
    // --- ADMIN ---
    void adminGUI();
    void userGUI();

    // function for when the add button is pressed. It reads data from the text boxes and emits a signal named "AddDogSignal"
    void addDogButtonHandler();
    // function to delete the selected dog from the list. Opens a message box in case there are no more dogs.
    void deleteDogButtonHandler();
    // function to update a dog. Opens a message box in case there are no more dogs or the dog doesn't exist.
    void updateDogButtonHandler();
    // function to save the changes to the text file and exit the program
    void saveAndExitButtonHandler();
    //
    int getSelectedIndex();
    // returns the item that is selected from the list at that moment
    QListWidgetItem* getSelectedItem();
    // everytime admin selects something from the list, the info on the right side is updated. In case is empy, the right side
    // also empties.
    void listItemChanged();
    // function to show the current dog. In case all dogs got adopted, show message.
    void userShowDog();
    void userShowDogFiltered();
    // function to adopt dog.
    void userAdoptDog();
    void userAdoptDogFiltered();
    // function to show next dog
    void userNextDog();
    void userNextDogFiltered();
    // create another window for another list with the dogs sorted.
    void userSortDog();
    // exit de window for the sorted list
    void userSortExit();

public:
    //constructor
    GUI(ServiceAdmin&, ServiceUser&, QWidget *parent = nullptr);
    //destructor
    ~GUI();

    //call other functions when gui is beginning
    void initGUI();

    //add items to the widget list
    void populateDogsList();

signals:
    // calls the service to add dog. Opens a message box with the exception if it's the case
    void addDogSignal(const std::string&, const std::string&, const std::string&, const std::string&);

    void populateAdoptionList();

    void saveAndExitButtonHandler2();

    void csvButtonHandler();

    void htmlButtonHandler();
};


#endif //A89_913ALICEHINCU_GUI_H
