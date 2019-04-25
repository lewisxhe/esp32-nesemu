/*
** Nofrendo (c) 1998-2000 Matthew Conte (matt@conte.com)
**
**
** This program is free software; you can redistribute it and/or
** modify it under the terms of version 2 of the GNU Library General 
** Public License as published by the Free Software Foundation.
**
** This program is distributed in the hope that it will be useful, 
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU 
** Library General Public License for more details.  To obtain a 
** copy of the GNU Library General Public License, write to the Free 
** Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
**
** Any permitted reproduction of these routines, in whole or in part,
** must bear this legend.
**
**
** gui_elem.c
**
** GUI elements (font, mouse pointer, etc.)
** $Id: gui_elem.c,v 1.2 2001/04/27 14:37:11 neil Exp $
*/

#include <stdlib.h>
#include <noftypes.h>
#include <gui.h>
#include <gui_elem.h>

#define  SMALL_FONT_KERN   6
#define  SMALL_FONT_HEIGHT 6

static const fontchar_t small_data[] =
{
   { { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, SMALL_FONT_KERN }, /* space */
   { { 0x20, 0x20, 0x20, 0x00, 0x20, 0x00 }, SMALL_FONT_KERN },
   { { 0x50, 0x50, 0x00, 0x00, 0x00, 0x00 }, SMALL_FONT_KERN },
   { { 0x50, 0xF8, 0x50, 0xF8, 0x50, 0x00 }, SMALL_FONT_KERN },
   { { 0x20, 0x78, 0x20, 0xF0, 0x20, 0x00 }, SMALL_FONT_KERN },
   { { 0xC8, 0xD0, 0x20, 0x58, 0x98, 0x00 }, SMALL_FONT_KERN },
   { { 0x40, 0xA0, 0x58, 0x90, 0xF0, 0x00 }, SMALL_FONT_KERN },
   { { 0x20, 0x40, 0x00, 0x00, 0x00, 0x00 }, SMALL_FONT_KERN },
   { { 0x20, 0x40, 0x40, 0x40, 0x20, 0x00 }, SMALL_FONT_KERN },
   { { 0x20, 0x10, 0x10, 0x10, 0x20, 0x00 }, SMALL_FONT_KERN },
   { { 0x00, 0x50, 0x20, 0x50, 0x00, 0x00 }, SMALL_FONT_KERN },
   { { 0x00, 0x20, 0x70, 0x20, 0x00, 0x00 }, SMALL_FONT_KERN },
   { { 0x00, 0x00, 0x00, 0x20, 0x40, 0x00 }, SMALL_FONT_KERN },
   { { 0x00, 0x00, 0x70, 0x00, 0x00, 0x00 }, SMALL_FONT_KERN },
   { { 0x00, 0x00, 0x00, 0x00, 0x20, 0x00 }, SMALL_FONT_KERN },
   { { 0x08, 0x10, 0x20, 0x40, 0x80, 0x00 }, SMALL_FONT_KERN },

   /* 0-9 */
   { { 0x70, 0x98, 0xA8, 0xC8, 0x70, 0x00 }, SMALL_FONT_KERN },
   { { 0x60, 0x20, 0x20, 0x20, 0xF8, 0x00 }, SMALL_FONT_KERN },
   { { 0xF0, 0x08, 0x70, 0x80, 0xF8, 0x00 }, SMALL_FONT_KERN },
   { { 0x70, 0x88, 0x30, 0x88, 0x70, 0x00 }, SMALL_FONT_KERN },
   { { 0x30, 0x50, 0x90, 0xF8, 0x10, 0x00 }, SMALL_FONT_KERN },
   { { 0xF8, 0x80, 0x70, 0x08, 0xF0, 0x00 }, SMALL_FONT_KERN },
   { { 0x70, 0x80, 0xF0, 0x88, 0x70, 0x00 }, SMALL_FONT_KERN },
   { { 0xF8, 0x08, 0x10, 0x20, 0x20, 0x00 }, SMALL_FONT_KERN },
   { { 0x70, 0x88, 0x70, 0x88, 0x70, 0x00 }, SMALL_FONT_KERN },
   { { 0x70, 0x88, 0x78, 0x08, 0x70, 0x00 }, SMALL_FONT_KERN },

   { { 0x00, 0x20, 0x00, 0x20, 0x00, 0x00 }, SMALL_FONT_KERN },
   { { 0x00, 0x20, 0x00, 0x20, 0x40, 0x00 }, SMALL_FONT_KERN },
   { { 0x10, 0x20, 0x40, 0x20, 0x10, 0x00 }, SMALL_FONT_KERN },
   { { 0x00, 0x70, 0x00, 0x70, 0x00, 0x00 }, SMALL_FONT_KERN },
   { { 0x40, 0x20, 0x10, 0x20, 0x40, 0x00 }, SMALL_FONT_KERN },
   { { 0x70, 0x88, 0x30, 0x00, 0x20, 0x00 }, SMALL_FONT_KERN },
   { { 0x70, 0x88, 0xA8, 0xB0, 0x78, 0x00 }, SMALL_FONT_KERN },

   /* A-Z */
   { { 0x70, 0x88, 0xF8, 0x88, 0x88, 0x00 }, SMALL_FONT_KERN },
   { { 0xF0, 0x88, 0xF0, 0x88, 0xF0, 0x00 }, SMALL_FONT_KERN },
   { { 0x78, 0x80, 0x80, 0x80, 0x78, 0x00 }, SMALL_FONT_KERN },
   { { 0xF0, 0x88, 0x88, 0x88, 0xF0, 0x00 }, SMALL_FONT_KERN },
   { { 0xF8, 0x80, 0xF8, 0x80, 0x78, 0x00 }, SMALL_FONT_KERN },
   { { 0x78, 0x80, 0xF8, 0x80, 0x80, 0x00 }, SMALL_FONT_KERN },
   { { 0x78, 0x80, 0xB8, 0x88, 0xF0, 0x00 }, SMALL_FONT_KERN },
   { { 0x88, 0x88, 0xF8, 0x88, 0x88, 0x00 }, SMALL_FONT_KERN },
   { { 0xF8, 0x20, 0x20, 0x20, 0xF8, 0x00 }, SMALL_FONT_KERN },
   { { 0x08, 0x08, 0x08, 0x88, 0x70, 0x00 }, SMALL_FONT_KERN },
   { { 0x88, 0x90, 0xE0, 0x90, 0x88, 0x00 }, SMALL_FONT_KERN },
   { { 0x80, 0x80, 0x80, 0x80, 0x78, 0x00 }, SMALL_FONT_KERN },
   { { 0xF0, 0xA8, 0xA8, 0xA8, 0xA8, 0x00 }, SMALL_FONT_KERN }, 
   { { 0xF0, 0x88, 0x88, 0x88, 0x88, 0x00 }, SMALL_FONT_KERN },
   { { 0xF0, 0x88, 0x88, 0x88, 0x78, 0x00 }, SMALL_FONT_KERN },
   { { 0xF0, 0x88, 0xF0, 0x80, 0x80, 0x00 }, SMALL_FONT_KERN },
   { { 0x70, 0x88, 0x88, 0x90, 0x68, 0x00 }, SMALL_FONT_KERN },
   { { 0xF0, 0x88, 0xF0, 0x88, 0x88, 0x00 }, SMALL_FONT_KERN },
   { { 0x78, 0x80, 0x70, 0x08, 0xF0, 0x00 }, SMALL_FONT_KERN },
   { { 0xF8, 0x20, 0x20, 0x20, 0x20, 0x00 }, SMALL_FONT_KERN },
   { { 0x88, 0x88, 0x88, 0x88, 0x78, 0x00 }, SMALL_FONT_KERN },
   { { 0x88, 0x88, 0x88, 0x50, 0x20, 0x00 }, SMALL_FONT_KERN },
   { { 0xA8, 0xA8, 0xA8, 0xA8, 0x78, 0x00 }, SMALL_FONT_KERN },
   { { 0x88, 0x50, 0x20, 0x50, 0x88, 0x00 }, SMALL_FONT_KERN },
   { { 0x88, 0x88, 0x70, 0x20, 0x20, 0x00 }, SMALL_FONT_KERN },
   { { 0xF8, 0x08, 0x70, 0x80, 0xF8, 0x00 }, SMALL_FONT_KERN },

   { { 0x70, 0x40, 0x40, 0x40, 0x70, 0x00 }, SMALL_FONT_KERN },
   { { 0x80, 0x40, 0x20, 0x10, 0x08, 0x00 }, SMALL_FONT_KERN },
   { { 0x70, 0x10, 0x10, 0x10, 0x70, 0x00 }, SMALL_FONT_KERN },
   { { 0x20, 0x50, 0x00, 0x00, 0x00, 0x00 }, SMALL_FONT_KERN },
   { { 0x00, 0x00, 0x00, 0x00, 0x70, 0x00 }, SMALL_FONT_KERN },
   { { 0x20, 0x10, 0x00, 0x00, 0x00, 0x00 }, SMALL_FONT_KERN },

   /* A-Z */
   { { 0x70, 0x88, 0xF8, 0x88, 0x88, 0x00 }, SMALL_FONT_KERN },
   { { 0xF0, 0x88, 0xF0, 0x88, 0xF0, 0x00 }, SMALL_FONT_KERN },
   { { 0x78, 0x80, 0x80, 0x80, 0x78, 0x00 }, SMALL_FONT_KERN },
   { { 0xF0, 0x88, 0x88, 0x88, 0xF0, 0x00 }, SMALL_FONT_KERN },
   { { 0xF8, 0x80, 0xF8, 0x80, 0x78, 0x00 }, SMALL_FONT_KERN },
   { { 0x78, 0x80, 0xF8, 0x80, 0x80, 0x00 }, SMALL_FONT_KERN },
   { { 0x78, 0x80, 0xB8, 0x88, 0xF0, 0x00 }, SMALL_FONT_KERN },
   { { 0x88, 0x88, 0xF8, 0x88, 0x88, 0x00 }, SMALL_FONT_KERN },
   { { 0xF8, 0x20, 0x20, 0x20, 0xF8, 0x00 }, SMALL_FONT_KERN },
   { { 0x08, 0x08, 0x08, 0x88, 0x70, 0x00 }, SMALL_FONT_KERN },
   { { 0x88, 0x90, 0xE0, 0x90, 0x88, 0x00 }, SMALL_FONT_KERN },
   { { 0x80, 0x80, 0x80, 0x80, 0x78, 0x00 }, SMALL_FONT_KERN },
   { { 0xF0, 0xA8, 0xA8, 0xA8, 0xA8, 0x00 }, SMALL_FONT_KERN }, 
   { { 0xF0, 0x88, 0x88, 0x88, 0x88, 0x00 }, SMALL_FONT_KERN },
   { { 0xF0, 0x88, 0x88, 0x88, 0x78, 0x00 }, SMALL_FONT_KERN },
   { { 0xF0, 0x88, 0xF0, 0x80, 0x80, 0x00 }, SMALL_FONT_KERN },
   { { 0x70, 0x88, 0x88, 0x90, 0x68, 0x00 }, SMALL_FONT_KERN },
   { { 0xF0, 0x88, 0xF0, 0x88, 0x88, 0x00 }, SMALL_FONT_KERN },
   { { 0x78, 0x80, 0x70, 0x08, 0xF0, 0x00 }, SMALL_FONT_KERN },
   { { 0xF8, 0x20, 0x20, 0x20, 0x20, 0x00 }, SMALL_FONT_KERN },
   { { 0x88, 0x88, 0x88, 0x88, 0x78, 0x00 }, SMALL_FONT_KERN },
   { { 0x88, 0x88, 0x88, 0x50, 0x20, 0x00 }, SMALL_FONT_KERN },
   { { 0xA8, 0xA8, 0xA8, 0xA8, 0x78, 0x00 }, SMALL_FONT_KERN },
   { { 0x88, 0x50, 0x20, 0x50, 0x88, 0x00 }, SMALL_FONT_KERN },
   { { 0x88, 0x88, 0x70, 0x20, 0x20, 0x00 }, SMALL_FONT_KERN },
   { { 0xF8, 0x08, 0x70, 0x80, 0xF8, 0x00 }, SMALL_FONT_KERN },

   { { 0x10, 0x20, 0x20, 0x20, 0x10, 0x00 }, SMALL_FONT_KERN },
   { { 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0x00 }, SMALL_FONT_KERN },
   { { 0x40, 0x20, 0x20, 0x20, 0x40, 0x00 }, SMALL_FONT_KERN },
   { { 0x50, 0xA0, 0x00, 0x00, 0x00, 0x00 }, SMALL_FONT_KERN },
   { { 0xF8, 0x88, 0x88, 0x88, 0xF8, 0x00 }, SMALL_FONT_KERN },
};

font_t small = { small_data, SMALL_FONT_HEIGHT };

const uint8 cursor_color[] =
{
   0,
   GUI_BLACK,
   GUI_WHITE,
   GUI_LTGRAY,
   GUI_GRAY
};

const uint8 cursor[] =
{
   1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   4, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0,
   4, 3, 3, 1, 0, 0, 0, 0, 0, 0, 0,
   4, 2, 3, 3, 1, 0, 0, 0, 0, 0, 0,
   4, 2, 3, 3, 3, 1, 0, 0, 0, 0, 0,
   4, 2, 2, 3, 3, 3, 1, 0, 0, 0, 0,
   4, 2, 2, 3, 3, 3, 3, 1, 0, 0, 0,
   4, 2, 2, 2, 3, 3, 3, 3, 1, 0, 0,
   4, 2, 2, 2, 3, 3, 3, 3, 3, 1, 0,
   4, 2, 2, 3, 1, 1, 1, 1, 1, 1, 1,
   4, 2, 3, 1, 2, 2, 1, 0, 0, 0, 0,
   4, 3, 1, 0, 4, 2, 3, 1, 0, 0, 0,
   4, 1, 0, 0, 4, 2, 3, 1, 0, 0, 0,
   1, 0, 0, 0, 0, 4, 2, 3, 1, 0, 0,
   0, 0, 0, 0, 0, 4, 2, 3, 1, 0, 0,
   0, 0, 0, 0, 0, 0, 4, 2, 3, 1, 0,
   0, 0, 0, 0, 0, 0, 4, 3, 3, 1, 0,
   0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0,
};

/*
** $Log: gui_elem.c,v $
** Revision 1.2  2001/04/27 14:37:11  neil
** wheeee
**
** Revision 1.1.1.1  2001/04/27 07:03:54  neil
** initial
**
** Revision 1.8  2000/10/10 13:03:54  matt
** Mr. Clean makes a guest appearance
**
** Revision 1.7  2000/07/31 04:28:46  matt
** one million cleanups
**
** Revision 1.6  2000/07/17 04:21:18  neil
** warning: initialization makes integer from pointer without a cast
**
** Revision 1.5  2000/07/17 01:52:27  matt
** made sure last line of all source files is a newline
**
** Revision 1.4  2000/06/09 15:12:25  matt
** initial revision
**
*/
