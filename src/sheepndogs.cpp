
#include <iostream>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

#include "Clock.h"

#include "Simulation/ClusterTimeSimulation.h"
#include "Simulation/FiniteSimulation.h"
#include "Simulation/InfiniteSimulation.h"

#include "Motion/BrownianMotion.h"
#include "Motion/ConstVelocity.h"
#include "Dogs.h"
#include "Sheep/SheepField.h"
#include "Sheep/SheepTree.h"
#include "World.h"

#include "Plotter/VoidPlotter.h"
#include "Plotter/GNUPlotter.h"
#include "Plotter/GLPlotter.h"

#include "Measure/DoMeasure.h"

using namespace std;

double Dphi=4.,delta_t=0.01,v0=4.,r1=.5,r2=.5,t3=10.;	//noise int.,time step, velocity, rates
double delta_l=1.,tau_s=10, mu=1.;	          	//interaction radius, cattle size, friction
double vec=5., cl_trMSD=0.7, cl_trMQD=0.1;		//vec size, clustering threshold
double simtime = 0.;                                    //elapsed time
int Ns=100, Nd=50, L=200,Nsb=1;				//Number of sheep,dog, box size
int t_end=1000,t_out=20;
int pr=0, mov=0, sc=0, fbreak=0, sim=0;                 //class switches
string mout="temp/measurements.txt";                              //measure output file

void parse_params(int argc, char **argv)
{
    if( argc > 1 )
    {
        if( strcmp( argv[1], "--help") == 0 )
        {
                printf("Parameters to set:\n");
                printf(" ( default value )\n\n");
                printf("	Ns,Nd \t( %i, %i )		//Particle Numbers\n", Ns, Nd );
                printf("	Nsb \t( %i )			//Number of sheep/cattle\n", Nsb );
                printf("	pr: \t( GNU )			//printing flag\n");
                printf("		GNU: generate GNUplot script (default), GL: 3D GL plotter (infinite), void: no plot\n");
                printf("	break: \t( %i )			//break flag\n", fbreak );
                printf("		0: MSD 1: MQD 2: MSD+MQD\n");
                printf("        sc: \t( %i )                           //sheep container\n", sc );
                printf("            kdtree: use kdtree mat: use matrix (faster for small grid)\n");
                printf("	L,vec \t( %i, %f )		//box-, vec-length\n", L, vec );
                printf("	Dd \t( %f )			//ang. diffusion const.\n", Dphi );
                printf("	ts \t( %f )			//mean diff. time sheep\n", tau_s );
                printf("	dt,dl \t( %f, %f )		//time step, cattle size\n", delta_t, delta_l );
                printf("	v \t( %f )			//velocity\n", v0 );
                printf("	r1,r2 \t( %f, %f )		//change rates\n", r1, r2 );
                printf("	t3 \t( %f )			//waiting time in sleeping state\n", t3 );
                printf("	t,out \t( %i, %i )		//end-, output-time\n", t_end, t_out );
                printf("	msdtr, mqdtr \t( %f, %f )	//threshold for clustering (MSD and MQD)\n", cl_trMSD, cl_trMQD );
                printf("	m: 		                //change movment\n");
                printf("	   cv: const velocity (default), bm: brownian motion\n");
                printf("        sim:                            //change simulation\n");
                printf("            inf: infinite sim., finite: finite sim. (default), cltime: clustering time sim.\n");
                printf("	mout \t( \"%s\" )	//measure outputfile\n", mout.c_str() );
                printf("                void: no output\n");
                exit(0);
        }
    }
	int jpar;
	if((argc % 2) == 0)
	{
      		printf("wrong parameters\n");
                exit(1);
   	}
	for(jpar=1; jpar<argc; jpar+=2)
	{
       		if(strcmp(argv[jpar], "-Nsb")==0)
		{
          		Nsb = atoi(argv[jpar+1]);
		}
       		if(strcmp(argv[jpar], "-Ns")==0)
		{
          		Ns = atoi(argv[jpar+1]);
		}
       		if(strcmp(argv[jpar], "-Nd")==0)
		{
          		Nd = atoi(argv[jpar+1]);
		}
       		if(strcmp(argv[jpar], "-L")==0)
		{
          		L = atoi(argv[jpar+1]);
		}
       		if(strcmp(argv[jpar], "-Dd")==0)
		{
          		Dphi = atof(argv[jpar+1]);
		}
       		if(strcmp(argv[jpar], "-dt")==0)
		{
          		delta_t = atof(argv[jpar+1]);
		}
       		if(strcmp(argv[jpar], "-dl")==0)
		{
          		delta_l = atof(argv[jpar+1]);
		}
       		if(strcmp(argv[jpar], "-msdtr")==0)
		{
          		cl_trMSD = atof(argv[jpar+1]);
		}
       		if(strcmp(argv[jpar], "-mqdtr")==0)
		{
          		cl_trMQD = atof(argv[jpar+1]);
		}
       		if(strcmp(argv[jpar], "-v")==0)
		{
          		v0 = atof(argv[jpar+1]);
		}
       		if(strcmp(argv[jpar], "-r1")==0)
		{
          		r1 = atof(argv[jpar+1]);
		}
       		if(strcmp(argv[jpar], "-r2")==0)
		{
          		r2 = atof(argv[jpar+1]);
		}
       		if(strcmp(argv[jpar], "-t3")==0)
		{
          		t3 = atof(argv[jpar+1]);
		}
       		if(strcmp(argv[jpar], "-vec")==0)
		{
          		vec = atof(argv[jpar+1]);
		}
       		if(strcmp(argv[jpar], "-t")==0)
		{
          		t_end = atoi(argv[jpar+1]);
		}
       		if(strcmp(argv[jpar], "-ts")==0)
		{
          		tau_s = atof(argv[jpar+1]);
		}
       		if(strcmp(argv[jpar], "-out")==0)
		{
          		t_out = atoi(argv[jpar+1]);
		}
       		if(strcmp(argv[jpar], "-pr")==0)
		{
          		if(!strcmp(argv[jpar+1],"GNU")) pr=0; 
          		if(!strcmp(argv[jpar+1],"void")) pr=1; 
          		if(!strcmp(argv[jpar+1],"GL")) pr=2; 
		}
       		if(strcmp(argv[jpar], "-sim")==0)
		{
          		if(!strcmp(argv[jpar+1],"finite")) sim=0; 
          		if(!strcmp(argv[jpar+1],"inf")) sim=1; 
          		if(!strcmp(argv[jpar+1],"cltime")) sim=2; 
		}
       		if(strcmp(argv[jpar], "-break")==0)
		{
          		fbreak = atoi(argv[jpar+1]);
		}
       		if(strcmp(argv[jpar], "-m")==0)
		{
          		if(!strcmp(argv[jpar+1],"cv")) mov=0; 
          		if(!strcmp(argv[jpar+1],"bm")) mov=1; 
		}
       		if(strcmp(argv[jpar], "-mout")==0)
		{
                        mout = argv[jpar+1];
		}
       		if(strcmp(argv[jpar], "-sc")==0)
		{
          		if(!strcmp(argv[jpar+1],"kdtree")) sc=0; 
          		if(!strcmp(argv[jpar+1],"mat")) sc=1; 
		}
	}
}

void paste_params(Motion& motion)
{
	printf("Ns:\t%i\n",Ns);
	printf("Nd:\t%i\n",Nd);
	printf("Box:\t%i\n",L);
	printf("Cattle:\t%g\n",delta_l);
	printf("Sheep per Box:\t%i\n",Nsb);
	printf("Noise int:\t\t%g\n",Dphi);
	printf("Sheeptime:\t\t%g\n",tau_s);
	printf("Velocity:\t\t%g\n",v0);
	printf("Rate 1->2:\t\t%g\n",r1);
	printf("Rate 2->3:\t\t%g\n",r2);
	printf("Time 3->1:\t\t%g\n",t3);
	printf("timestep:\t\t%g\n",delta_t);
	printf("endtime:\t\t%d\n",t_end);
	printf("output:\t\t\t%d\n",t_out);
	printf("time elapsed:\t\t%g\n",simtime);
	//printf("number of runs:\t\t%i\n",Nrun);
	//printf("number of clustered:\t%i\n",Ncl);
	printf("\n===============================\n");
	printf("eff. Diffusion:\t%f\n", motion.getEffectiveDiffusion() );
	printf("pers. Time:\t%f\n", motion.getPersistenceTime() );
	printf("pers. Length:\t%f\n", motion.getPersistenceLength() );
	printf("\n===============================\n");

	FILE *fp;
	fp=fopen("./temp/parameters.dat","w");

		fprintf(fp,"\nNd:\t%i\n",Nd);
		fprintf(fp,"Ns:\t%i\n",Ns);
		fprintf(fp,"Box:\t%i\n",L);
		fprintf(fp,"Cattle:\t%g\n",delta_l);
		fprintf(fp,"Sheep per Box:\t%i\n",Nsb);
		fprintf(fp,"Noise int:\t\t%g\n",Dphi);
		fprintf(fp,"Sheeptime:\t\t%g\n",tau_s);
		fprintf(fp,"Velocity:\t\t%g\n",v0);
		fprintf(fp,"Rate 1->2:\t\t%g\n",r1);
		fprintf(fp,"Rate 2->3:\t\t%g\n",r2);
		fprintf(fp,"Time 3->1:\t\t%g\n",t3);
		fprintf(fp,"timestep:\t\t%g\n",delta_t);
		fprintf(fp,"endtime:\t\t%d\n",t_end);
		fprintf(fp,"output:\t\t\t%d\n",t_out);
		fprintf(fp,"time elapsed:\t\t%g\n",simtime);
	//	fprintf(fp,"number of runs:\t\t%i\n",Nrun);
	//	fprintf(fp,"number of clustered:\t%i\n",Ncl);
		fprintf(fp,"\n===============================\n");
                fprintf(fp,"eff. Diffusion:\t%f\n", motion.getEffectiveDiffusion() );
                fprintf(fp,"pers. Time:\t%f\n", motion.getPersistenceTime() );
                fprintf(fp,"pers. Length:\t%f\n", motion.getPersistenceLength() );
		fprintf(fp,"\n===============================\n");

	fclose(fp);
}

int main( int argc, char* argv[] )
{
    // init random number generator
    
    const gsl_rng_type *T;
    gsl_rng *rng;
    long int seed;

	gsl_rng_env_setup();
	T = gsl_rng_default;
	rng = gsl_rng_alloc (T);
	time_t t1;
	time(&t1);
	seed=t1;  
	gsl_rng_set(rng,seed);

    // read parameters

    parse_params(argc, argv);
    //get things right
    {
        mu = Dphi / ( v0 * v0 ) ;          // ensures that persistence times match
    }
    //check initial conditions
    if( Ns/Nsb > L * L / (delta_l * delta_l) )
    {
        printf("Too many sheep\n");
        exit(1);
    }

    // setup simulation
    Motion* motion = NULL; 
    switch(mov)
    {
    case 0:
        motion = new ConstVelocity ( Dphi, rng, v0 );
        break;
    case 1:
    	motion = new BrownianMotion ( v0 * v0 * v0 * v0 / (2 * Dphi), rng, mu );                //D_bm should match D_eff
	break;

    default:
	cerr << "Motion == " << mov << "?! Bei dir hackt's wohl!!" << endl;
	return -1;
    }
    Dogs dogs(*motion);

    Sheep* sheep = NULL;
    switch( sc )
    {
    case 0:
        sheep = new SheepTree ( L/delta_l, Nsb, rng );
        break;
    case 1:
        sheep = new SheepField ( L/delta_l, Nsb, rng );
        break;
    default:
	cerr << "Sheep == " << sc << "?! Bei dir hackt's wohl!!" << endl;
	return -1;
    }
    World::createInstance( L, rng, t3, r1, r2, *sheep, dogs );
    HarryPlotter* plotter = NULL;

    Measure* measure = NULL;
    if( mout == "void" )
    {
        measure = new VoidMeasure( t_out/delta_t );
        if( pr == 0 ) pr = 1;
    }
    else
    {
        measure = new DoMeasure( t_out/delta_t, mout );
    }

    switch(pr)
    {
    case 0:
    	plotter = new GNUPlotter ( *measure, t_out/delta_t, vec*0.002*L );
	break;
    case 1:
        plotter = new VoidPlotter;
        break;
    case 2:
    	plotter = new GLPlotter;
        sim = 1;
	break;
    default:
	cerr << "Plotter == " << pr << "?! Bei dir hackt's wohl!!" << endl;
	return -1;
    }

    sheep->init(Ns);
    measure->init();
    
    Simulation* simulation = NULL;

    switch( sim )
    {
    case 0:
    	simulation = new FiniteSimulation ( *plotter, tau_s, rng, *measure, delta_t, t_end );
        break;
    case 1:
    	simulation = new InfiniteSimulation ( *plotter, tau_s, rng, *measure, delta_t );
        break;
    case 2:
    	simulation = new ClusterTimeSimulation ( *plotter, tau_s, rng, *measure, delta_t, cl_trMSD, cl_trMQD, fbreak );
        break;
    default:
	cerr << "Simulation == " << sim << "?! Bei dir hackt's wohl!!" << endl;
	return -1;
    }
    
    dogs.init(Nd, v0);

    //measure time
    //simulate
    Clock clock;
    clock.tick();
    simtime = simulation->run();
    clock.tick();

    //Print parameters
    paste_params( *motion );

    cout << "Time per run: " << clock.getFrameTime() << " s" << endl;
    // let's have some fun

    // clean up!!!!!!!!
    {
        delete sheep;
        delete simulation;
        delete plotter;
        delete motion;
        delete measure;
    }

    return 0;
}

