#ifndef RADIO_H
#define RADIO_H

#include "rep_radio_source.h"

#include <gnuradio/top_block.h>

#include "gr/weaver.h"

class Radio : public RadioSimpleSource
{
    Q_OBJECT

    gr::top_block_sptr m_top_block;
    gr::sm6wjm::weaver::sptr m_weaver;

public:
    Radio(QObject *parent = nullptr);
    ~Radio();

signals:

public slots:
    void setFrequency(float frequency);
    void setFrequencyOffset(float frequencyOffset);
};

#endif // RADIO_H
