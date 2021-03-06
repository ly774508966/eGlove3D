/*
 * Copyright © 2016
 * Szymon Kłos, Robert Jankowski, Wojciech Tokarski
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Szymon Kłos, Robert Jankowski and Wojciech Tokarski
 *       nor the names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL SZYMON KŁOS, ROBERT JANKOWSKI, WOJCIECH TOKARSKI BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * */

#include <config.h>

#if _ACCELEROMETER == MPU6050

#include <acc.h>
#include <twi.h>

#define MPUW 0xD0
#define MPUR 0xD1

void mpu_transmit(uint8_t reg, uint8_t value);

void acc_init(void)
{
	twi_init();
	// Wake up
	mpu_transmit(0x6B, 0x00);
}

void mpu_transmit(uint8_t reg, uint8_t value)
{
	twi_start();
	twi_write(MPUW);
	twi_write(reg);
	twi_write(value);
	twi_stop();
}

uint16_t acc_receive(acc_axis reg)
{
	uint16_t ret = 0;
	uint16_t tmp;
	switch (reg)
	{
	case ACC_X:
		twi_start();
		twi_write(MPUW);
		twi_write(0x3B);
		twi_start();
		twi_write(MPUR);
		tmp = twi_read(NOACK);
		twi_stop();

		twi_start();
		twi_write(MPUW);
		twi_write(0x3C);
		twi_start();
		twi_write(MPUR);
		ret = (tmp << 8) | twi_read(NOACK);
		twi_stop();
	break;
	case ACC_Y:
		twi_start();
		twi_write(MPUW);
		twi_write(0x3D);
		twi_start();
		twi_write(MPUR);
		tmp = twi_read(NOACK);
		twi_stop();

		twi_start();
		twi_write(MPUW);
		twi_write(0x3E);
		twi_start();
		twi_write(MPUR);
		ret = (tmp << 8) | twi_read(NOACK);
		twi_stop();
	break;
	case ACC_Z:
		twi_start();
		twi_write(MPUW);
		twi_write(0x3F);
		twi_start();
		twi_write(MPUR);
		tmp = twi_read(NOACK);
		twi_stop();

		twi_start();
		twi_write(MPUW);
		twi_write(0x40);
		twi_start();
		twi_write(MPUR);
		ret = (tmp << 8) | twi_read(NOACK);
		twi_stop();
	break;
	}
	ret = (ret >> 8);
	return ret;
}

#endif
