/****************************************************************************************************
                                   ExploreEmbedded    
 ****************************************************************************************************
 * File:   rgb.h
 * Version: 16.0
 * Author: ExploreEmbedded
 * Website: http://www.exploreembedded.com/wiki
 * Description: File contains the functios to initialize and write the data to RGB leds.
 
The libraries have been tested on ExploreEmbedded development boards. We strongly believe that the 
library works on any of development boards for respective controllers. However, ExploreEmbedded 
disclaims any kind of hardware failure resulting out of usage of libraries, directly or indirectly.
Files may be subject to change without prior notice. The revision history contains the information 
related to updates. 
 
 
GNU GENERAL PUBLIC LICENSE: 
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>. 
 
Errors and omissions should be reported to codelibraries@exploreembedded.com
**************************************************************************************************/
 
#ifdef __cplusplus
extern "C" {
#endif

 
#ifndef _RGB_H_
#define _RGB_H_

#include"stdutils.h"



/*************************************************************************************************
                           Constants for PIN Function Selection
*************************************************************************************************/
#define RGB_OFF      1
#define RGB_ON       0
/*************************************************************************************************/




/***************************************************************************************************
                             Function prototypes
***************************************************************************************************/
void rgbInit(void);
void rgbWrite(uint8_t ledNum, uint8_t ledValue);
void rgbWriteAll(uint8_t redValue, uint8_t greenValue, uint8_t blueValue);
/**************************************************************************************************/

#endif

#ifdef __cplusplus
}
#endif