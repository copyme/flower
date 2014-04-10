/*=========================================================================

  Program:
  Module:    <>

  Copyright (c) Kacper Pluta <kacper.pluta@dbslabs.com.br>
                Meri-nut Zago <meri_zago@hotmail.fr>
  All rights reserved.
  See Copyright.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

#ifndef GUISTATEMONITOR_H
#define GUISTATEMONITOR_H

class GUIStateMonitor
{
private:
    bool panLock;
    bool turnLock;
    bool zoomLock;
    double lockPositionX;
    double lockPositionY;
//     int camera;
//     double time;
//     bool playing;
public:
    GUIStateMonitor();
    static const float MOUSE_PAN_SPEED;
    static const float MOUSE_ZOOM_SPEED;
    static const float MOUSE_TURN_SPEED;
    void lock_pan () {
        panLock = true;
    }
    void unlock_pan () {
        panLock = false;
    }
    bool pan () const {
        return panLock;
    }

    void lock_turn () {
        turnLock = true;
    }
    void unlock_turn () {
        turnLock = false;
    }
    bool turn () const {
        return turnLock;
    }

    void lock_zoom () {
        zoomLock = true;
    }
    void unlock_zoom () {
        zoomLock = false;
    }
    bool zoom () const {
        return zoomLock;
    }

    void set_position_x ( double x ) {
        lockPositionX = x;
    }
    void set_position_y ( double y ) {
        lockPositionY = y;
    }

    double get_position_x () const {
        return lockPositionX;
    }
    double get_position_y () const {
        return lockPositionY;
    }

//     void set_time ( double time ) { this->time = time; }
//     double get_time () const { return time; }

};

#endif // GUISTATEMONITOR_H
