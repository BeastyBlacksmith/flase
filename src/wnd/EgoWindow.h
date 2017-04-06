/*
 * EgoWindow.h
 *
 *  Created on: 08.06.2012
 *      Author: explicit
 */

#ifndef EGOTESTWINDOW_H_
#define EGOTESTWINDOW_H_

#include "Window.h"

#include "Camera.h"

class EgoWindow : public Window {
protected:
    EgoWindow( );

public:
    virtual ~EgoWindow( );

    static EgoWindow& get_instance();

    const Camera& get_cam_ego() const { return c_ego; }
    const Camera& get_cam_out() const { return c_out; }
    const Camera& get_cam_following() const { return *camera_follow; }
    const Camera& get_cam_controlling() const { return *camera_control; }

    Camera& get_cam_ego() { return c_ego; }
    Camera& get_cam_out() { return c_out; }
    Camera& get_cam_following() { return *camera_follow; }
    Camera& get_cam_controlling() { return *camera_control; }

    void set_fov( double fov );
    void set_zfar( double zfar );

protected:
    void key( unsigned char key, int x, int y );
    void draw();

    virtual void handle_camera_keys();

private:
    Camera c_ego;
    Camera c_out;
    Camera *camera_follow;
    Camera *camera_control;

    double fov;
    double zfar;

    bool follow_camera;
    bool control_camera;

    bool cullface;
    bool drahtgitter;
    bool smooth;

    double mousespeed;

    double rot[3];
    double rot2[3];
};

#endif /* EGOTESTWINDOW_H_ */
