/*
             LUFA Library
     Copyright (C) Dean Camera, 2010.
              
  dean [at] fourwalledcubicle [dot] com
      www.fourwalledcubicle.com
*/

/*
  Copyright 2010  Dean Camera (dean [at] fourwalledcubicle [dot] com)

  Permission to use, copy, modify, distribute, and sell this 
  software and its documentation for any purpose is hereby granted
  without fee, provided that the above copyright notice appear in 
  all copies and that both that the copyright notice and this
  permission notice and warranty disclaimer appear in supporting 
  documentation, and that the name of the author not be used in 
  advertising or publicity pertaining to distribution of the 
  software without specific, written prior permission.

  The author disclaim all warranties with regard to this
  software, including all implied warranties of merchantability
  and fitness.  In no event shall the author be liable for any
  special, indirect or consequential damages or any damages
  whatsoever resulting from loss of use, data or profits, whether
  in an action of contract, negligence or other tortious action,
  arising out of or in connection with the use or performance of
  this software.
*/

#define  __INCLUDE_FROM_SERIALSTREAM_C
#include "SerialStream.h"

FILE USARTStream = FDEV_SETUP_STREAM(SerialStream_TxByte, SerialStream_RxByte, _FDEV_SETUP_RW);

static int SerialStream_TxByte(char DataByte,
                               FILE *Stream)
{
	(void)Stream;
	
	Serial_TxByte(DataByte);
	return 0;
}

static int SerialStream_RxByte(FILE *Stream)
{
	(void)Stream;
	
	if (!(Serial_IsCharReceived()))
	  return _FDEV_EOF;

	return Serial_RxByte();
}
