QT -= gui

CONFIG += c++14
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
CONFIG += link_pkgconfig
PKGCONFIG += opencv4
# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp

INCLUDEPATH += /home/apokerce/Desktop/Deblurringcodes/libtorch-cxx11-abi-shared-with-deps-1.12.1+cu102/libtorch/include/torch/csrc/api/include
INCLUDEPATH += /home/apokerce/Desktop/Deblurringcodes/libtorch-cxx11-abi-shared-with-deps-1.12.1+cu102/libtorch/include
DEPENDPATH += /home/apokerce/Desktop/Deblurringcodes/libtorch-cxx11-abi-shared-with-deps-1.12.1+cu102/libtorch/include/torch/csrc/api/include
DEPENDPATH += /home/apokerce/Desktop/Deblurringcodes/libtorch-cxx11-abi-shared-with-deps-1.12.1+cu102/libtorch/include
LIBS += -L/home/apokerce/Desktop/Deblurringcodes/libtorch-cxx11-abi-shared-with-deps-1.12.1+cu102/libtorch/lib -lc10 \
        -lc10_cuda \
        -ltorch_cpu \
        -ltorch \
        -lc10d_cuda_test \
        -lcaffe2_nvrtc \
        -lfmt \
        -lnvrtc-builtins \
        -lshm \
        -ltensorpipe \
        -ltorch_cuda

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

QMAKE_CXXFLAGS += -DGLIBCXX_USE_CXX11_ABI=0
