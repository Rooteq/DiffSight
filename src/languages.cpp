#include "languages.h"

Languages::Languages(QWidget* parent) : QComboBox(parent) {
    addItem("English");
    addItem("Polski");
    addItem("Ślůnski");

    connect(this, SIGNAL(currentIndexChanged(int)), this, SLOT(onLanguageChanged(int)));
}

void Languages::onLanguageChanged(const int index)
{
    QString language = this->itemText(index);
    emit languageChanged(language);
}
