
/*
Copyright (C) 2017  Simon Christ <c.O_o.l@web.de>, Jörg Bachmann <explicit@explicits.de>

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
*/
#include "GL/glew.h"

#include "common.h"
#include "World.h"

#include "GLPlotter.h"

#include "EgoWindow.h"

using namespace std;

class MyWindow : public EgoWindow
{
public:

    MyWindow() :
        mutex( PTHREAD_MUTEX_INITIALIZER ),
        quit( false )
    {
    }

    static MyWindow& get_instance() {
        if( ! has_instance() ) {
            singleton = new MyWindow;
            return *static_cast< MyWindow* >( singleton );
        }

        MyWindow* w = dynamic_cast< MyWindow* >( singleton );
        if( NULL == w ) {
            delete singleton;
            return get_instance();
        }

        return *w;
    }

    pthread_mutex_t mutex;
    real time;

    World* world;
    bool quit;


protected:

    void init();
    void draw();
};

void MyWindow::init()
{
    //get_cam_ego().orthographic( 1, 1, 0, 2 );
    get_cam_ego().perspective( 90, 1, 0.1, 500 );
    //get_cam_out().perspective( 90, 1, 0.1, 1/sqrt(3) );
}

void MyWindow::draw()
{
    pthread_mutex_lock( &mutex );
    if( quit ) {
        close_window();
        return;
    }

    EgoWindow::draw();

    for( size_t j = 0; j < world->sheep.size()-1; ++j )
    {
        glBegin( GL_QUAD_STRIP );
        for( size_t i = 0; i < world->sheep.size(); ++i )
        {
            const size_t nSheep = world->sheep.getNSheep( i, j );
            const float col = nSheep / ( float )( world->sheep.getCapacity()+1 );

            glColor3f( col, sqrt(1-col), 0 );
            glVertex3f( i, 0*5*nSheep / ( float )world->sheep.getCapacity(), j );


            const size_t nSheep2 = world->sheep.getNSheep( i, j+1 );
            const float col2 = nSheep2 / ( float )( world->sheep.getCapacity()+1 );

            glColor3f( col2, sqrt(1-col2), 0 );
            glVertex3f( i, 0*5*nSheep2 / ( float )world->sheep.getCapacity(), j+1 );
        }
        glEnd();
    }

    glPointSize( 5 );
    for( size_t i = 0; i < world->dogs.size(); ++i )
    {
        switch( world->dogs[i].getState() )
        {
        case ACTIVE:
            glColor3f( 1, 1, 1 );
            break;

        case OCCUPIED:
            glColor3f( 1, 0, 0 );
            break;

        case SLEEPY:
            glColor3f( 0, 0, 1 );
            break;
        }

        glBegin( GL_LINES );
        glVertex3f( world->dogs[i].x, 0.1, world->dogs[i].y );
        glVertex3f( world->dogs[i].x + world->dogs[i].vx, 0.1, 
                    world->dogs[i].y + world->dogs[i].vy );
        glEnd();

        glBegin( GL_POINTS );
        glVertex3f( world->dogs[i].x + world->dogs[i].vx, 0.1, 
                    world->dogs[i].y + world->dogs[i].vy );
        glEnd();
    }

    pthread_mutex_unlock( &mutex );
}


void* glPlotterThread( void* data )
{
    MyWindow& w = MyWindow::get_instance();    

    w.create_window( 0, NULL, 640, 480 );
    w.run();

    pthread_mutex_unlock( &w.mutex );
    return NULL;
}


GLPlotter::GLPlotter()
{
    MyWindow& w = MyWindow::get_instance();    

    pthread_mutex_lock( &w.mutex );

    pthread_create( &thread, NULL, glPlotterThread, NULL );
}

GLPlotter::~GLPlotter()
{
    MyWindow& w = MyWindow::get_instance();    

    w.quit = true;
    pthread_mutex_unlock( &w.mutex );

    // wait for window to finish closing process
    {
        pthread_mutex_lock( &w.mutex );
        pthread_mutex_unlock( &w.mutex );
    }
}

void GLPlotter::plot( World& world, real time )
{
    MyWindow& w = MyWindow::get_instance();    

    w.world = & world;
    w.time = time;

    pthread_mutex_unlock( &w.mutex );
    pthread_mutex_lock( &w.mutex );
}

