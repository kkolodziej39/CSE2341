TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        avlindex.cpp \
        docparse.cpp \
        document.cpp \
        hashindex.cpp \
        indexword.cpp \
        main.cpp \
        stemfunctionality.cpp \
        query.cpp \
        user.cpp

HEADERS += \
    HEAD \
    avl.h \
    avlindex.h \
    avlnode.h \
    common_lang_constants.h \
    debug_logic.h \
    docparse.h \
    document.h \
    english_stem.h \
    hash.h \
    hashindex.h \
    index.h \
    indexword.h \
    json.hpp \
    query.h \
    safe_math.h \
    stemfunctionality.h \
    stemming.h \
    string_util.h \
    user.h \
    utilities.h


DISTFILES +=
    ../build-Final-Desktop_Qt_5_10_0_GCC_64bit-Debug/StopWords



