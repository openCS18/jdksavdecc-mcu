#pragma once

/*
Copyright (c) 2014, Jeff Koftinoff
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "JDKSAvdeccMCU_World.hpp"
#include "JDKSAvdeccMCU_RawSocket.hpp"
#include "JDKSAvdeccMCU_PcapFileReader.hpp"
#include "JDKSAvdeccMCU_PcapFileWriter.hpp"

#if JDKSAVDECCMCU_ENABLE_RAWSOCKETPCAPFILE && JDKSAVDECCMCU_ENABLE_PCAPFILE
namespace JDKSAvdeccMCU
{
class RawSocketPcapFile : public RawSocket
{
    uint16_t m_ethertype;
    jdksavdecc_eui48 m_my_mac;
    jdksavdecc_eui48 m_default_dest_mac;
    jdksavdecc_eui48 m_join_multicast;
    PcapFileReader m_pcap_file_reader;
    PcapFileWriter m_pcap_file_writer;
    jdksavdecc_timestamp_in_milliseconds m_current_time;
    jdksavdecc_timestamp_in_milliseconds m_time_granularity_in_ms;
    FrameWithSize<1500> m_next_incoming_frame;

    RawSocketPcapFile( RawSocketPcapFile const &other );

  public:
    /**
    *  Open a raw socket connected to the specified interface name and join the
    *  specified multicast address
    */
    RawSocketPcapFile(
        uint16_t ethertype,
        jdksavdecc_eui48 my_mac,
        jdksavdecc_eui48 default_dest_mac,
        jdksavdecc_eui48 *join_multicast,
        const std::string &input_file,
        const std::string &output_file,
        jdksavdecc_timestamp_in_milliseconds time_granularity_in_ms );

    ~RawSocketPcapFile();

    virtual jdksavdecc_timestamp_in_milliseconds getTimeInMilliseconds();

    virtual bool recvFrame( Frame *frame );

    virtual bool sendFrame( Frame const &frame,
                            uint8_t const *data1,
                            uint16_t len1,
                            uint8_t const *data2,
                            uint16_t len2 );

    virtual bool sendReplyFrame( Frame &frame,
                                 uint8_t const *data1,
                                 uint16_t len1,
                                 uint8_t const *data2,
                                 uint16_t len2 );

    virtual bool joinMulticast( const jdksavdecc_eui48 &multicast_mac );

    virtual void setNonblocking();

    virtual filedescriptor_type getFd() const;

    virtual const jdksavdecc_eui48 &getMACAddress() const;

  private:
    bool readNextIncomingFrame();
};
}
#endif
