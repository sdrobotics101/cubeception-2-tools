//
//  MS5803.h
//
//  This library is for reading and writing to the MS5803 pressure/temperature sensor.
//
//  Created by Victor Konshin on 4/10/13.
//
//
//  Copyright (c) 2013, Victor Konshin, info@ayerware.com
//  for the DIY Dive Computer project www.diydivecomputer.com
//  All rights reserved.

//  Redistribution and use in source and binary forms, with or without
//  modification, are permitted provided that the following conditions are met:
//  * Redistributions of source code must retain the above copyright
//  notice, this list of conditions and the following disclaimer.
//  * Redistributions in binary form must reproduce the above copyright
//  notice, this list of conditions and the following disclaimer in the
//  documentation and/or other materials provided with the distribution.
//  * Neither the name of Ayerware Publishing nor the
//  names of its contributors may be used to endorse or promote products
//  derived from this software without specific prior written permission.

//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
//  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
//  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
//  DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
//  DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
//  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
//   LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
//  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
//  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
//  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef ____MS5803__
#define ____MS5803__

#include <stdint.h>

#include "../Utilities/spi.h"

class MS5803
{
public:

    MS5803(uint32_t spi_device, int verbose = 0);

    void resetSensor();
    
    bool initSensor();
    
    void readSensor();
    
    double temperature() const { return temp;  }    // returns temp in degrees C.
    double pressure()    const { return press; }    // Returns pressure in mBars. 
    
private:
    
    double            press;                        // Stores actual pressure in mbars
    double            temp;                         // Stores actual temp in degrees C.

    uint32_t          _spi_device;                  // pointer to spi device
    int               _verbose;                     // verbose printouts

    unsigned int      sensorCoefficients[8];        // calibration coefficients
    unsigned long     D1;                           // Stores uncompensated pressure value
    unsigned long     D2;                           // Stores uncompensated temperature value
    double            deltaTemp;                    // These three variable are used for the conversion.
    double            sensorOffset;
    double            sensitivity;

    unsigned int  ms5803ReadCoefficient(uint8_t index); // Reads the coeffincient data from the sensor.
    unsigned char ms5803CRC4(unsigned int n_prom[]);    // Verifies the validity of the coeffient data using CRC4.
    unsigned long ms5803CmdAdc(uint8_t cmd);               // Handles commands to the sensor.
};

#endif /* defined(____MS5803__) */
