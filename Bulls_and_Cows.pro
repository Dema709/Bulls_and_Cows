QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14
#CONGID += sanitazer sanitize_address sanitize_memory sanitize_thread sanitize_undefined

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Bulls_and_Cows/bulls_and_cows.cpp \
    Bulls_and_Cows/settingswidget.cpp \
    Common/QTextTableWidget.cpp \
    main.cpp

HEADERS += \
    Bulls_and_Cows/bulls_and_cows.h \
    Bulls_and_Cows/settingswidget.h \
    Common/QTextTableWidget.h \
    Common/random.hpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


#Работает при добавлении для сборки параметра make: install
install_it.path = $$OUT_PWD
install_it.files = Bulls_and_Cows/bulls_and_cows_rules.txt
INSTALLS += install_it
