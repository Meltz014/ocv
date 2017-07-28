## Synopsis

This project is for my own personal experimentation with the Qt gui framework and OpenCV.  The main gui was built to load
 a video file and generate a "[rolling shutter]( https://en.wikipedia.org/wiki/Rolling_shutter)" effect.  It now supports
 using the optflow module in OpenCV to interpolate motion between frames in order to achieve a smoother result.

There are two programs that can be built here: 
* OCV.exe: Gui that loads a video and generates a rolling shutter effect
* upsampvid.exe: command-line tool to upsample the frame rate of a video file.  The command line args are as follows
  * -i [input video]
  * -o [output avi file]
  * -s [start frame]
  * -e [end frame]
  * -n [number of inbetween frames]
  * -x [scale factor % for output (1-100, will be rounded to the nearest 5%)]
  * -f [flow algorithm to use]
    * N: no interpolation will be done.
    * S: simple flow
    * D: deep flow

## Example

### Rolling Shutter effect without interpolation

![ ]( http://i.imgur.com/c5ElxgQ.gifv )

### Rolling Shutter effect with interpolation

animation sped up 6x.  3 intermediary frames using Simple Flow algorithmn.
![ ]( http://i.imgur.com/YaJ94z1.gifv )

## Motivation

This project was started to gain experience with Qt and OpenCV frameworks.
Inspiration came from this [Smarter Every Day video]( https://www.youtube.com/watch?v=dNVtMmLlnoE ).

