#ifndef XLIGHTS_GLOBALS_H_INCLUDED_
#define XLIGHTS_GLOBALS_H_INCLUDED_

#define XLIGHTS_VERSION "3.0.19"
#define XLIGHTS_CONFIG_ID "xLights"
#define XLIGHTS_HELP_URL        "http://sourceforge.net/apps/mediawiki/xlights/index.php?title=Main_Page"
#define XLIGHTS_SCRIPT_HELP_URL "http://sourceforge.net/apps/mediawiki/xlights/index.php?title=XScheduler_Script_Reference"

#define XTIMER_INTERVAL 50

#define XLIGHTS_ANIMATION_FILE "xlights_animation.xml"
#define XLIGHTS_NETWORK_FILE   "xlights_networks.xml"
#define XLIGHTS_CHANNEL_FILE   "xlights_channels.csv"
#define XLIGHTS_SCHEDULE_FILE  "xlights_schedule.xml"
#define XLIGHTS_RGBEFFECTS_FILE  "xlights_rgbeffects.xml"
#define XLIGHTS_SEQUENCE_EXT   "xseq"

#define XLIGHTS_DESCRIPTION "Use xLights to control you holiday light display"

#define XLIGHTS_LICENSE "xLights Copyright 2010-2013 Matt Brown\nNutcracker Copyright 2012-2013 Sean Meighan\n\nThis file is part of xLights.\n\nxLights-Nutcracker is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. xLights-Nutcracker is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.\n\nYou should have received a copy of the GNU General Public License along with xLights.  If not, see <http://www.gnu.org/licenses/>.\n\nNutcracker website is http://nutcracker123.com/nutcracker\n\nAcknowledgements\n\nxLights relies on 2 open-source libraries: wxWidgets and irrXML.\n\nCode for serial port communication was inpired by the ctb library written by Joachim Buermann. Code for base64 encoding and decoding was written by Ren� Nyffenegger."

#if !wxCHECK_VERSION(2,9,1)
#define HasAttribute HasProp
#define DeleteAttribute DeleteProperty
#endif

#endif
