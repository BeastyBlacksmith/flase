/*
 * Window.cpp
 *
 *  Created on: 08.06.2012
 *      Author: explicit
 */

//#define RT_STATISTICS

#include "Window.h"

#include <iostream>
#include <string.h>

#include <GL/glew.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>         /* glut.h includes gl.h and glu.h*/
#endif

using namespace std;

Window::Window() :
    created( false ),
    warp_pointer( true ),
    fullscreen( false ),
    speedup( 0.125 )
{
    mouse[0] = mouse[1] = 0;
}

Window::~Window() {
    if( created )
        close_window();
    singleton = NULL;
}

void Reshape( int width, int height ) {
    Window::get_instance().reshape( width, height );
}

void ProcessMousePassiveMotion( int x, int y ) {
    Window::get_instance().processMousePassiveMotion( x, y );
}

void MouseKey( int button, int state, int x, int y ) {
    Window::get_instance().mouseKey( button, state, x, y );
}

void Key2( int key, int x, int y ) {
    Window::get_instance().key2( key, x, y );
}

void Key( unsigned char key, int x, int y ) {
    Window::get_instance().key( key, x, y );
}

void KeyUp( unsigned char key, int x, int y ) {
    Window::get_instance().keyUp( key, x, y );
}

void SpecialKeyUp( int key, int x, int y ) {
    Window::get_instance().specialKeyUp( key, x, y );
}

void Draw() {
    Window::get_instance().draw();

    Window::get_instance().frametime = Window::get_instance().timer.tick();

    // finish frame
    {
        //glFlush();
        glFinish();
        glutSwapBuffers();
    }

#   ifdef RT_STATISTICS
    cout << " " << 1 / Window::get_instance().frametime << endl;
#   endif

}

void Window::create_window( int argc, char** argv, int width, int height ) {
    if( created )
        return;

    windW = width;
    windH = height;

    glutInit( &argc, argv );

    glutInitWindowPosition( 0, 0 );
    glutInitWindowSize( windW, windH );

    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );

    if( ( wnd_id = glutCreateWindow( "Test" ) ) == GL_FALSE ) {
        cout << "Could not create window!" << endl;
        exit( 1 );
    }
    created = true;

    this->init();

    glutSetCursor( GLUT_CURSOR_NONE );
    glutReshapeFunc( Reshape );
    glutKeyboardFunc( Key );
    glutSpecialFunc( Key2 );
//    glutKeyboardUpFunc( KeyUp );
//    glutSpecialUpFunc( SpecialKeyUp );
    glutPassiveMotionFunc( ProcessMousePassiveMotion );
    glutMouseFunc( MouseKey );
    glutDisplayFunc( Draw );

    glutIdleFunc( glutPostRedisplay );
}

void Window::run() {
    timer.tick();
    glutMainLoop();
}

void Window::close_window() {
    if( !created )
        return;

    glutDestroyWindow( wnd_id );

    created = false;
}

void Window::enter_fullscreen() {
    glutFullScreen();
}

void Window::leave_fullscreen() {
    glutReshapeWindow( _windW, _windH );
    //glutPositionWindow(0,0);
}

void Window::init( ) {
    memset( keys, 0, sizeof(bool) * 256 );
    memset( specialkeys, 0, sizeof(bool) * 246 );
    memset( mousebuttons, 0, sizeof(bool) * 3 );
}

void Window::reshape( int width, int height ) {
    windW = ( GLint )width;
    windH = ( GLint )height;

    if( !fullscreen ) {
        _windW = windW;
        _windH = windH;
    }
}

void Window::processMousePassiveMotion( int x, int y ) {
    if( x < 0 || x >= windW || y < 0 || y >= windH )
        return;

    mouse[0] = ((( float )x) / windW - 0.5);
    mouse[1] = ((( float )y) / windH - 0.5);
}

void Window::mouseKey( int button, int state, int x, int y ) {
    if( state == GLUT_DOWN )
        mousebuttons[button % 3] = true;
    else
        mousebuttons[button % 3] = false;
}

void Window::key2( int key, int x, int y ) {
    specialkeys[key] = true;
}

void Window::key( unsigned char key, int x, int y ) {
    keys[key] = true;

    switch( key ) {
    case 27:
        close_window();
        break;

    case 'o':
        warp_pointer = !warp_pointer;
        break;

    case 'f':
        fullscreen = !fullscreen;
        if( fullscreen )
            enter_fullscreen();
        else
            leave_fullscreen();
        break;

    default:
        return;
    }
}

void Window::keyUp( unsigned char key, int x, int y ) {
    keys[key] = false;
}

void Window::specialKeyUp( int key, int x, int y ) {
    specialkeys[key] = false;
}

void Window::draw() {
    if( warp_pointer )
        glutWarpPointer( windW >> 1, windH >> 1 );

    glViewport( 0, 0, windW, windH );

    glClearColor( 0, 0, 0, 1 );
    glClearDepth( 1 );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}

Window& Window::get_instance() {
    if( NULL == singleton )
        singleton = new Window;

    return *singleton;
}

bool Window::has_instance() {
    return ( NULL != singleton );
}

Window* Window::singleton = NULL;
int Window::wnd_id = 0;

