QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++23

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bishop.cpp \
    castling_logic.cpp \
    checks_logic.cpp \
    chessboard.cpp \
    colordialog.cpp \
    drawofferwindow.cpp \
    fen.cpp \
    game.cpp \
    king.cpp \
    knight.cpp \
    main.cpp \
    mainwindow.cpp \
    movedialog.cpp \
    pawn.cpp \
    piece.cpp \
    promotiondialog.cpp \
    queen.cpp \
    rook.cpp \
    settingswindow.cpp \
    square.cpp

HEADERS += \
    bishop.h \
    castling_logic.h \
    checks_logic.h \
    chessboard.h \
    colordialog.h \
    drawofferwindow.h \
    fen.h \
    game.h \
    king.h \
    knight.h \
    mainwindow.h \
    movedialog.h \
    pawn.h \
    piece.h \
    promotiondialog.h \
    properties.h \
    queen.h \
    rook.h \
    settingswindow.h \
    square.h

FORMS += \
    drawofferwindow.ui \
    mainwindow.ui \
    settingswindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
