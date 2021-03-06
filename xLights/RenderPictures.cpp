/***************************************************************
 * Name:      RgbEffects.cpp
 * Purpose:   Implements RGB effects
 * Author:    Matt Brown (dowdybrown@yahoo.com)
 * Created:   2012-12-23
 * Copyright: 2012 by Matt Brown
 * License:
     This file is part of xLights.

    xLights is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    xLights is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with xLights.  If not, see <http://www.gnu.org/licenses/>.
**************************************************************/
#include <cmath>
#include "RgbEffects.h"
#include "wx/log.h"
#include <wx/file.h>
#include <wx/utils.h>


void RgbEffects::RenderPictures(int dir, const wxString& NewPictureName2,int GifSpeed)
{
    const int speedfactor=4;
    //int maxframes=wxAtoi( MaxFrames ); // get max frames the user has passed in
    int maxframes;
    if(state==0 ) maxmovieframes=10;
    maxframes=maxmovieframes;
    int frame = state%maxframes;
    wxString suffix,BasePicture,sPicture,NewPictureName,buff;
    wxString filename = "RenderPictures.log";
    int createlog=0; // set to 1 to log variables to a log file. this is becaus debug in wxWidgets doesnt display strings
    wxFile f;


    if(NewPictureName2.length()==0) return;

//  Look at ending of the filename passed in. If we have it ending as *-1.jog then we will assume
//  we have a bunch of jpg files made by ffmpeg
//  movie files can be converted into jpg frames by this command
//      ffmpeg -i XXXX.mp4 -s 16x50 XXXX-%d.jpg
//      ffmpeg -i XXXX.avi -s 16x50 XXXX-%d.jpg
//      ffmpeg -i XXXX.mov -s 16x50 XXXX-%d.jpg
//      ffmpeg -i XXXX.mts -s 16x50 XXXX-%d.jpg


    sPicture = NewPictureName2;
    suffix = NewPictureName2.substr (NewPictureName2.length()-6,2);
    if( suffix =="-1") // do ew have amovie file?
    {
        //    yes
        BasePicture= NewPictureName2.substr (0,NewPictureName2.length()-6) ;

        //  build the next filename. the frame counter is incrementing through all frames

        sPicture = wxString::Format(wxT("%s-%d.jpg"),BasePicture,frame);
        if(state==0) // only once, try 10000 files to find how high is frame count
        {
            for (frame=1; frame<=9999; frame++)
            {
                sPicture = wxString::Format(wxT("%s-%d.jpg"),BasePicture,frame);
                if(wxFileExists(sPicture))
                {
                    maxmovieframes=frame+1;
                }
            }
        }

    }


    NewPictureName=sPicture;
    if(!wxFileExists(NewPictureName))
    {
        maxframes=frame-1;
        return;
    }
    if(createlog==1)
    {


        wxRemoveFile(filename);
        if (!f.Create(filename,false))
        {
            // ConversionError(_("Unable to create file: ")+filename);
            return;
        }

        buff = wxString::Format(wxT("NewPictureName %s, PictureName %s, NewPictureName2=%s, suffix=%s, frame=%d\n"),NewPictureName,PictureName,NewPictureName2,suffix,frame);
        f.Write(buff);
    }

    if (NewPictureName != PictureName)
    {
        imageCount = wxImage::GetImageCount(NewPictureName);
        imageIndex = 0;
        if (!image.LoadFile(NewPictureName,wxBITMAP_TYPE_ANY,0))
        {
            //wxMessageBox("Error loading image file: "+NewPictureName);
            image.Clear();
        }
        PictureName=NewPictureName;
        if (!image.IsOk())
            return;

    }
    if(imageCount>1)
    {
        // The 10 could be animation speed. I did notice that state is jumping numbers
        // so state%someNumber == 0 may not hit every time. There could be a better way.
        if(state%(21-GifSpeed)==0)  // change 1-20 in Gimspeed to be 20 to 1. This makes right hand slider fastest
        {
            if(imageIndex == imageCount-1)
            {
                imageIndex = 0;
            }
            else
            {
                imageIndex++;

            }


            if (!image.LoadFile(PictureName,wxBITMAP_TYPE_ANY,imageIndex))
            {
                //wxMessageBox("Error loading image file: "+NewPictureName);
                image.Clear();
            }
            if (!image.IsOk())
                return;
        }
    }

    int imgwidth=image.GetWidth();
    int imght=image.GetHeight();
    int yoffset=(BufferHt+imght)/2;
    int xoffset=(imgwidth-BufferWi)/2;
    int limit=(dir < 2) ? imgwidth+BufferWi : imght+BufferHt;
    int movement=(state % (limit*speedfactor)) / speedfactor;

// copy image to buffer
    wxColour c;
    for(int x=0;
            x<imgwidth;
            x++)
    {
        for(int y=0; y<imght; y++)
        {
            if (!image.IsTransparent(x,y))
            {
                c.Set(image.GetRed(x,y),image.GetGreen(x,y),image.GetBlue(x,y));
                switch (dir)
                {
                case 0:
                    // left
                    SetPixel(x+BufferWi-movement,yoffset-y,c);
                    break;
                case 1:
                    // right
                    SetPixel(x+movement-imgwidth,yoffset-y,c);
                    break;
                case 2:
                    // up
                    SetPixel(x-xoffset,movement-y,c);
                    break;
                case 3:
                    // down
                    SetPixel(x-xoffset,BufferHt+imght-y-movement,c);
                    break;
                default:
                    // no movement - centered
                    SetPixel(x-xoffset,yoffset-y,c);
                    break;
                }
            }
        }
    }
}


/*void RgbEffects::RenderPictures(int dir, const wxString& NewPictureName)
{
    const int speedfactor=4;
    if (NewPictureName != PictureName)
    {
        if (!image.LoadFile(NewPictureName))
        {
            //wxMessageBox("Error loading image file: "+NewPictureName);
            image.Clear();
        }
        PictureName=NewPictureName;
    }
    if (!image.IsOk()) return;
    int imgwidth=image.GetWidth();
    int imght=image.GetHeight();
    int yoffset=(BufferHt+imght)/2;
    int xoffset=(imgwidth-BufferWi)/2;
    int limit=(dir < 2) ? imgwidth+BufferWi : imght+BufferHt;
    int movement=(state % (limit*speedfactor)) / speedfactor;

    // copy image to buffer
    wxColour c;
    for(int x=0; x<imgwidth; x++)
    {
        for(int y=0; y<imght; y++)
        {
            if (!image.IsTransparent(x,y))
            {
                c.Set(image.GetRed(x,y),image.GetGreen(x,y),image.GetBlue(x,y));
                switch (dir)
                {
                case 0:
                    // left
                    SetPixel(x+BufferWi-movement,yoffset-y,c);
                    break;
                case 1:
                    // right
                    SetPixel(x+movement-imgwidth,yoffset-y,c);
                    break;
                case 2:
                    // up
                    SetPixel(x-xoffset,movement-y,c);
                    break;
                case 3:
                    // down
                    SetPixel(x-xoffset,BufferHt+imght-y-movement,c);
                    break;
                default:
                    // no movement - centered
                    SetPixel(x-xoffset,yoffset-y,c);
                    break;
                }
            }
        }
    }
}
*/
