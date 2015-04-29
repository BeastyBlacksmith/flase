
#ifndef _CAMERA_H
#define _CAMERA_H

#include "CameraProjection.h"

#include "common.h"

class Camera : public CameraProjection
{
public:
    RVec pos;
    Matrix rotation;

    Camera( );

    Matrix get_modelview_matrix( ) const;

    RVec getX( ) const;
    RVec getY( ) const;
    RVec getZ( ) const;

    void moveTo( real x, real y, real z );
    void moveTo( const RVec& p );

    void move( real dx, real dy, real dz );
    void move( const RVec& d );

    // Euler Angle
    void rotate( real dRX, real dRY, real dRZ );

    // rotate around axis
    void rotate( real angle, real axis1, real axis2, real axis3 );
    void rotate( real angle, const RVec& axis );

    void lookdir( real dx, real dy, real dz, real ux, real uy, real uz );
    void lookdir( const RVec& look, const RVec& up );

    void reset_bounds();

    void viewFrom( ) const;

    const RVec& get_n_left() const { return n_left; }
    const RVec& get_n_right() const { return n_right; }
    const RVec& get_n_bottom() const { return n_bottom; }
    const RVec& get_n_top() const { return n_top; }
    const RVec& get_n_near() const { return n_near; }
    const RVec& get_n_far() const { return n_far; }

    const RVec& get_nbl() const { return nbl; }
    const RVec& get_nbr() const { return nbr; }
    const RVec& get_ntl() const { return ntl; }
    const RVec& get_ntr() const { return ntr; }
    const RVec& get_fbl() const { return fbl; }
    const RVec& get_fbr() const { return fbr; }
    const RVec& get_ftl() const { return ftl; }
    const RVec& get_ftr() const { return ftr; }

private:
    RVec n_left;
    RVec n_right;
    RVec n_bottom;
    RVec n_top;
    RVec n_near;
    RVec n_far;

    RVec nbl;
    RVec nbr;
    RVec ntl;
    RVec ntr;
    RVec fbl;
    RVec fbr;
    RVec ftl;
    RVec ftr;
};

#endif // _CAMERA_H

