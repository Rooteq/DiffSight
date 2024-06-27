/**
 * @file languages.h
 * @author Marcin
 * @brief Handles languages through a QComboBox.
 * @version 0.1
 *
 * This header file defines the Languages class, which is a subclass of QComboBox.
 * It provides functionality to handle language changes through the selection
 * of language options in the combo box.
 *
 * The class emits a signal languageChanged() whenever the user selects a new language
 * from the combo box.
 */

#ifndef LANGUAGES_H
#define LANGUAGES_H

#include <QComboBox>
#include <QWidget>

/**
 * @class Languages
 * @brief A widget that enables user to change current language.
 *
 * The Languages class manages the dynamic change of application's current language.
 */
class Languages : public QComboBox {
    Q_OBJECT
public:
    /**
     * @brief Constructs a Languages object.
     * @param[in] parent - The parent widget.
     */
    Languages(QWidget* parent = nullptr);

public slots:
    /**
     * @brief Slot to handle language changes.
     * @param[in] index - The index of the selected language in the combo box.
     *
     * This slot is automatically called when the user selects a new language
     * from the combo box. It emits the languageChanged signal with the selected
     * language as an argument.
     */
    void onLanguageChanged(const int index);

signals:
    /**
     * @brief Signal emitted when the user changes the selected language.
     * @param language The newly selected language.
     *
     * This signal is emitted whenever the user selects a new language from the
     * combo box. It provides the selected language as a QString argument.
     */
    void languageChanged(const QString &language);
};

#endif // LANGUAGES_H
