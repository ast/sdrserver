#include "radio.h"

#include <gnuradio/audio/sink.h>
#include <gnuradio/analog/sig_source_f.h>
#include <fcdproplus/fcdproplus.h>
#include <gnuradio/filter/firdes.h>
#include <gnuradio/filter/freq_xlating_fir_filter_ccf.h>
#include <gnuradio/blocks/complex_to_mag.h>


#include "gr/qtfft.h"
#include "gr/qtfft_sink.h"
#include "gr/fm_demod.h"

Radio::Radio(QObject *parent) : RadioSimpleSource(parent)
{
    m_top_block = gr::make_top_block("top_block");

    auto fcd = gr::fcdproplus::fcdproplus::make("FUNcube Dongle V2.0");
    fcd->set_freq(14000000.+192./2);

    m_weaver = gr::sm6wjm::weaver::make(192000., 4, 0);

    //auto taps = gr::filter::firdes::low_pass(1.0, 192000.0, 10000.0, 100.0);
    //auto taps = gr::filter::firdes::low_pass(1.0, 192000.0, 2000.0, 100.0);
    //auto xfir = gr::filter::freq_xlating_fir_filter_ccf::make(4, taps, 0, 192000.0);

    //auto fm_demod = gr::sm6wjm::fm_demod::make(192000.0, 4, 75000.0, 15000.0, 1.0);

    //auto a_sink = gr::audio::sink::make(48000, "hw:0,1");
    auto a_sink = gr::audio::sink::make(48000, "hw:1,0");

    const int fft_size = 2048;
    auto qfft = gr::sm6wjm::qtfft::make(fft_size);
    auto qfft_sink = gr::sm6wjm::qtfft_sink::make(fft_size);

    // FFT chain
    m_top_block->connect(fcd, 0, qfft, 0);
    m_top_block->connect(qfft, 0, qfft_sink, 0);

    // Audio chain
    m_top_block->connect(fcd, 0, m_weaver, 0);
    m_top_block->connect(m_weaver, 0, a_sink, 0);

    // Audio chain
    //m_top_block->connect(fcd, 0, fm_demod, 0);
    //m_top_block->connect(fm_demod, 0, a_sink, 0);

    m_top_block->start();
}

Radio::~Radio() {
    m_top_block->stop();
    m_top_block->wait();
}

void Radio::setFrequency(float frequency) {

}

void Radio::setFrequencyOffset(float frequencyOffset) {
    m_weaver->set_center_frequency(frequencyOffset);
    qDebug() << "offset" << frequencyOffset;
}
