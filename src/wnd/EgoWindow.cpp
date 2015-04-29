/*
 * EgoWindow.cpp
 *
 *  Created on: 08.06.2012
 *      Author: explicit
 */

#define ZFAR 100
#define FOV 50

#include "EgoWindow.h"

#include <GL/glew.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>         /* glut.h includes gl.h and glu.h*/
#endif

#include <string.h>

EgoWindow::EgoWindow( ) :
    camera_follow( &c_ego ),
    camera_control( &c_ego ),
    fov( FOV ),
    zfar( ZFAR ),
    follow_camera( true ),
    control_camera( true ),
    cullface( true ),
    drahtgitter( false ),
    smooth( true ),
    mousespeed( 30 )
{
    memset( rot, 0, sizeof( double )*3 );
    memset( rot2, 0, sizeof( double )*3 );
}

EgoWindow::~EgoWindow( ) {
}

EgoWindow& EgoWindow::get_instance() {
    if( ! has_instance() ) {
        singleton = new EgoWindow;
        return *static_cast< EgoWindow* >( singleton );
    }

    EgoWindow* w = dynamic_cast< EgoWindow* >( singleton );
    if( NULL == w ) {
        delete singleton;
        return get_instance();
    }

    return *w;
}

void EgoWindow::set_fov( double fov ) {
    this->fov = fov;
}

void EgoWindow::set_zfar( double zfar ) {
    this->zfar = zfar;
}

void EgoWindow::key( unsigned char key, int x, int y ) {
    Window::key( key, x, y );

    switch( key ) {
    case 'V':
        follow_camera = !follow_camera;
        if( follow_camera )
            camera_follow = &c_ego;
        else {
            camera_follow = &c_out;
            c_out = c_ego;
        }
        break;

    case 'v':
        control_camera = !control_camera;
        if( control_camera )
            camera_control = &c_ego;
        else
            camera_control = &c_out;
        break;

    case '1':
        cullface = !cullface;
        break;

    case '2':
        drahtgitter = !drahtgitter;
        break;

    case '3':
        smooth = !smooth;
        break;

    }
}

void EgoWindow::draw() {
    Window::draw();

    handle_camera_keys();

    // break rotation
    {
        rot[0] *= 0.9;
        rot[1] *= 0.9;
        rot[2] *= 0.9;

        rot2[0] *= 0.9;
        rot2[1] *= 0.9;
        rot2[2] *= 0.9;
    }

    // set camera
    {
        // set camera movement
        {
            c_ego.rotate( rot[0], rot[1], rot[2] );
            c_out.rotate( rot2[0], rot2[1], rot2[2] );
        }

        camera_follow->set_projection();
        camera_follow->reset_bounds();
    }

    // view modes
    {
        if( cullface )
            glEnable( GL_CULL_FACE );
        else
            glDisable( GL_CULL_FACE );

        if( drahtgitter ) {
            glPolygonMode( GL_FRONT, GL_FILL );
            glPolygonMode( GL_BACK, GL_LINE );
        }
        else
            glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

        if( smooth )
            glShadeModel( GL_SMOOTH );
        else
            glShadeModel( GL_FLAT );

    }

    camera_follow->viewFrom();
}

void EgoWindow::handle_camera_keys() {
    double* const prot = control_camera ? rot : rot2;

    prot[0] = -get_frametime() * mousespeed * get_mouse_coords()[1];
    prot[1] = get_frametime()
            * mousespeed
            * get_mouse_coords()[0]
            * (( double )get_window_width() / ( double )get_window_height());

    if( get_keys()['a'] ) {
        camera_control->move( -25 * get_frametime() * camera_control->getX() );
    }

    if( get_keys()['d'] ) {
        camera_control->move( 25 * get_frametime() * camera_control->getX() );
    }

    if( get_keys()['w'] ) {
        camera_control->move( -25 * get_frametime() * camera_control->getZ() );
    }

    if( get_keys()['s'] ) {
        camera_control->move( 25 * get_frametime() * camera_control->getZ() );
    }

    if( get_keys()['q'] ) {
        camera_control->move( -25 * get_frametime() * camera_control->getY() );
    }

    if( get_keys()['e'] ) {
        camera_control->move( 25 * get_frametime() * camera_control->getY() );
    }

    if( get_special_keys()[GLUT_KEY_UP] ) {
        prot[0] += get_frametime() * 2;
    }

    if( get_special_keys()[GLUT_KEY_DOWN] ) {
        prot[0] -= get_frametime() * 2;
    }

    if( get_special_keys()[GLUT_KEY_RIGHT] ) {
        prot[1] += get_frametime() * 2;
    }

    if( get_special_keys()[GLUT_KEY_LEFT] ) {
        prot[1] -= get_frametime() * 2;
    }
}
