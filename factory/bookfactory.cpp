#include "bookfactory.h"
#include <QDate>

AbstractMedia* BookFactory::createMedia() {
    return new Book(0, "New Book", QDate::currentDate(), "", "", "", "", "", 0, "");
}

QWidget* BookFactory::createEditDialog() {
    return viewStrategy.createEditView(nullptr);
}

QString BookFactory::getMediaType() const {
    return "Book";
}