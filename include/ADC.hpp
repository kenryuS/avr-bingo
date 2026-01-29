#ifndef __ADC_HPP__
#define __ADC_HPP__

#include <stdint.h>

/** Single Ended 10 bits ADC.
 */
class ADCC {
    public:
        /*! ADC channel enumerations.
         * Represents ADC0~7 which is mapped to PORTA.
         */
        enum Channel {
            channel_0,
            channel_1,
            channel_2,
            channel_3,
            channel_4,
            channel_5,
            channel_6,
            channel_7
        };

        /*! ADC voltage reference type enumerations.
         * Represents available voltage reference types for ADC.
         */
        enum VRef {
            vref_vcc,
            vref_aref,
            vref_11
        };

        /*! Constructor. Sets voltage reference, prescaler to 16, and enable ADC.
         * @param vr voltage reference type.
         */
        ADCC(enum VRef vr);
        ADCC(const ADCC&) = delete;
        ADCC(const ADCC&&) = delete;

        /*! Sets voltage reference type.
         * @param vr target voltage reference.
         */
        void setVRef(enum VRef vr);
        /*! Gets current voltage reference type. */
        enum VRef getVRef();

        /*! Sets ADC channel.
         * @param c target ADC channel.
         */
        void setChannel(enum Channel c);
        /*! Gets current ADC channel. */
        enum Channel getChannel();

        /*! Starts single shot ADC conversion. This operation is blocking.
         * @param c ADC channel to be read from.
         * @return Contents of ADC register; conversion result.
         */
        uint16_t read(enum Channel c);

    private:
        enum Channel ch;
        enum VRef vref;
        uint16_t val;
};

#endif // __ADC_HPP__
