/*
 * Window.h
 *
 *  Created on: 08.06.2012
 *      Author: explicit
 */

#ifndef TESTWINDOW_H_
#define TESTWINDOW_H_

#include "Clock.h"

class Window {
protected:
    Window( );

public:
    virtual ~Window( );

    static Window& get_instance();
    static bool has_instance();

    void create_window( int argc, char** argv, int width = 640, int height = 480 );
    void run();
    void close_window( );

    int get_window_width( ) const { return windW; }
    int get_window_height( ) const { return windH; }

    const Clock& get_timer( ) const { return timer; }
    double get_frametime( ) const { return frametime; }

    bool const * get_keys( ) const { return keys; }
    bool const * get_special_keys( ) const { return specialkeys; }
    bool const * get_mouse_buttons( ) const { return mousebuttons; }
    double const * get_mouse_coords( ) const { return mouse; }

    void enter_fullscreen();
    void leave_fullscreen();

protected:
    virtual void init( );
    virtual void reshape( int width, int height );
    virtual void processMousePassiveMotion( int x, int y );
    virtual void mouseKey( int button, int state, int x, int y );
    virtual void key2( int key, int x, int y );
    virtual void key( unsigned char key, int x, int y );
    virtual void keyUp( unsigned char key, int x, int y );
    virtual void specialKeyUp( int key, int x, int y );
    virtual void draw( );

private:
    Clock timer;

    bool created;
    bool warp_pointer;
    bool fullscreen;

    double frametime;

    double speedup;

    double mouse[2];

    bool keys[256];
    bool specialkeys[246];
    bool mousebuttons[3];

    int windW, windH;
    int _windW, _windH;

    friend void Init( );
    friend void Reshape( int width, int height );
    friend void ProcessMousePassiveMotion( int x, int y );
    friend void MouseKey( int button, int state, int x, int y );
    friend void Key2( int key, int x, int y );
    friend void Key( unsigned char key, int x, int y );
    friend void KeyUp( unsigned char key, int x, int y );
    friend void SpecialKeyUp( int key, int x, int y );
    friend void Draw();

protected:
    static Window* singleton;
    static int wnd_id;
};


#endif /* TESTWINDOW_H_ */
