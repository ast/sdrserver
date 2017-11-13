QT -= gui
CONFIG += c++11 console
CONFIG -= app_bundle

DEFINES += QT_DEPRECATED_WARNINGS

QT += remoteobjects
REPC_SOURCE += radio.rep

INCLUDEPATH += /usr/local/include

SOURCES += main.cpp \
    gr/qtfft_impl.cpp \
    gr/qtfft_sink_impl.cpp \
    gr/fm_demod_impl.cpp \
    gr/weaver_impl.cpp \
    radio.cpp

LIBS += -lboost_system -lgnuradio-fcdproplus
LIBS += -lgnuradio-runtime -lgnuradio-analog -lgnuradio-blocks -lgnuradio-audio -lgnuradio-filter
LIBS += -lgnuradio-pmt -lgnuradio-fft

HEADERS += \
    gr/qtfft.h \
    gr/qtfft_impl.h \
    gr/qtfft_sink.h \
    gr/qtfft_sink_impl.h \
    gr/fm_demod_impl.h \
    gr/fm_demod.h \
    gr/weaver_impl.h \
    gr/weaver.h \
    radio.h
