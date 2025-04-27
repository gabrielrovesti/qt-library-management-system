QT += core gui widgets

TARGET = LibraryManager
TEMPLATE = app

CONFIG += c++17

SOURCES += \
    main.cpp \
    model/abstractmedia.cpp \
    model/book.cpp \
    model/movie.cpp \
    model/magazine.cpp \
    model/ebook.cpp \
    persistence/jsonpersistencemanager.cpp \
    view/mainwindow.cpp \
    view/medialistwidget.cpp \
    view/mediadetailwidget.cpp \
    view/mediaeditwidget.cpp \
    visitor/mediarenderervisitor.cpp \
    visitor/mediaexportvisitor.cpp \
    strategy/bookviewstrategy.cpp \
    strategy/movieviewstrategy.cpp \
    strategy/magazineviewstrategy.cpp \
    factory/mediafactory.cpp

HEADERS += \
    model/abstractmedia.h \
    model/book.h \
    model/movie.h \
    model/magazine.h \
    model/ebook.h \
    persistence/jsonpersistencemanager.h \
    view/mainwindow.h \
    view/medialistwidget.h \
    view/mediadetailwidget.h \
    view/mediaeditwidget.h \
    visitor/mediavisitor.h \
    visitor/mediarenderervisitor.h \
    visitor/mediaexportvisitor.h \
    strategy/mediaviewstrategy.h \
    strategy/bookviewstrategy.h \
    strategy/movieviewstrategy.h \
    strategy/magazineviewstrategy.h \
    factory/mediafactory.h

RESOURCES += \
    resources.qrc