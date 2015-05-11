
#include <iostream>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

#include "Clock.h"

#include "FiniteSimulation.h"
#include "InfiniteSimulation.h"

#include "BrownianMotion.h"
#include "ConstVelocity.h"
#include "Dogs.h"
#include "SheepField.h"
#include "SheepTree.h"
#include "World.h"

#include "VoidPlotter.h"
#include "GNUPlotter.h"
#include "GLPlotter.h"

using namespace std;

double Dphi=4.,delta_t=0.01,v0=4.,r1=.5,r2=.5,t3=10.;	//noise int.,time step, velocity, rates
double delta_l=1.,tau_s=.01, mu=1.;	          	//interaction radius, cattle size, friction
double vec=5., cl_trMSD=0.9, cl_trMQD=0.15;		//vec size, clustering threshold
int Ns=100, Nd=50, L=200,Nsb=1;				//Number of sheep,dog, box size
int t_end=1000,t_out=20, simtime=0;
int pr=0, mov=0, sc=0, fbreak=2;                        //class switches

void parse_params(int argc, char **argv)
{
/* Parameters to set:

	Ns,Nd				//Particle Numbers
	Nsb				//Number of sheep/cattle
	pr:				//printing flag 
		GNU: generate GNUplot script (default), GL: 3D GL plotter (infinite), void: no plot		
	break:				//break flag
		0: MQD 1: MQD+MSD 2: MSD (default)
        sc:                             //sheep container
            kdtree: use kdtree (default), mat: use matrix (faster for small grid)
	L,vec				//box-, vec-length
	Dd				//ang. diffusion const.
	ts				//mean diff. time sheep
	dt,dl 				//time step, cattle size
	v,mu				//velocity, friction
	r1,r2				//change rates
	t3				//waiting time in sleeping state
	t,out				//end-, output-time
	tr1,tr2	 1:MSD, 2:MQD		//threshold for clustering
	m: bm: brownian motion		//change movment
	   cv: const velocity (default)
*/
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
       		if(strcmp(argv[jpar], "-tr1")==0)
		{
          		cl_trMSD = atof(argv[jpar+1]);
		}
       		if(strcmp(argv[jpar], "-tr2")==0)
		{
          		cl_trMQD = atof(argv[jpar+1]);
		}
       		if(strcmp(argv[jpar], "-v")==0)
		{
          		v0 = atof(argv[jpar+1]);
		}
       		if(strcmp(argv[jpar], "-mu")==0)
		{
          		mu = atof(argv[jpar+1]);
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
       		if(strcmp(argv[jpar], "-break")==0)
		{
          		fbreak = atoi(argv[jpar+1]);
		}
       		if(strcmp(argv[jpar], "-m")==0)
		{
          		if(!strcmp(argv[jpar+1],"cv")) mov=0; 
          		if(!strcmp(argv[jpar+1],"bm")) mov=1; 
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
	//TODO: check this
	//int get= (int) t*delta_t/t_out;
	//if(t==simtime) get --;

	printf("Ns:\t%i\n",Ns);
	printf("Nd:\t%i\n",Nd);
	printf("Box:\t%i\n",L);
	printf("Cattle:\t%g\n",delta_l);
	printf("Sheep per Box:\t%i\n",Nsb);
	printf("Noise int:\t\t%g\n",Dphi);
	printf("Sheeptime:\t\t%g\n",tau_s*delta_t);
	printf("Velocity:\t\t%g\n",v0);
	printf("Rate 1->2:\t\t%g\n",r1);
	printf("Rate 2->3:\t\t%g\n",r2);
	printf("Time 3->1:\t\t%g\n",t3*delta_t);
	printf("timestep:\t\t%g\n",delta_t);
	printf("endtime:\t\t%d\n",t_end);
	printf("output:\t\t\t%d\n",t_out);
	//printf("time elapsed:\t\t%g\n",t*delta_t);
	//printf("number of runs:\t\t%i\n",Nrun);
	//printf("number of clustered:\t%i\n",Ncl);
	printf("\n===============================\n");
	printf("eff. Diffusion:\t%f\n", motion.getEffectiveDiffusion() );
	printf("pers. Time:\t%f\n", motion.getPersistenceTime() );
	printf("pers. Length:\t%f\n", motion.getPersistenceLength() );
	//printf("MQD OP:\t%f\n",OP[get]/delta_l);
	//printf("MSD OP:\t%f\n",MSD[get]);
	//printf("Mean cl time:\t%g\n",aver5(1));
	//printf(" -\"- +/- :\t%g\n",sigma5(1));

	FILE *fp;
	fp=fopen("./temp/parameters.dat","w");

		fprintf(fp,"\nNd:\t%i\n",Nd);
		fprintf(fp,"Ns:\t%i\n",Ns);
		fprintf(fp,"Box:\t%i\n",L);
		fprintf(fp,"Cattle:\t%g\n",delta_l);
		fprintf(fp,"Sheep per Box:\t%i\n",Nsb);
		fprintf(fp,"Noise int:\t\t%g\n",Dphi);
		fprintf(fp,"Sheeptime:\t\t%g\n",tau_s*delta_t);
		fprintf(fp,"Velocity:\t\t%g\n",v0);
		fprintf(fp,"Rate 1->2:\t\t%g\n",r1);
		fprintf(fp,"Rate 2->3:\t\t%g\n",r2);
		fprintf(fp,"Time 3->1:\t\t%g\n",t3*delta_t);
		fprintf(fp,"timestep:\t\t%g\n",delta_t);
		fprintf(fp,"endtime:\t\t%d\n",t_end);
		fprintf(fp,"output:\t\t\t%d\n",t_out);
	//	fprintf(fp,"time elapsed:\t\t%g\n",t*delta_t);
	//	fprintf(fp,"number of runs:\t\t%i\n",Nrun);
	//	fprintf(fp,"number of clustered:\t%i\n",Ncl);
		fprintf(fp,"\n===============================\n");
                fprintf(fp,"eff. Diffusion:\t%f\n", motion.getEffectiveDiffusion() );
                fprintf(fp,"pers. Time:\t%f\n", motion.getPersistenceTime() );
                fprintf(fp,"pers. Length:\t%f\n", motion.getPersistenceLength() );
	//	fprintf(fp,"MQD OP:\t%f\n",OP[get]/delta_l);
	//	fprintf(fp,"MSD OP:\t%f\n",MSD[get]);
	//	fprintf(fp,"Mean cl time:\t%g\n",aver5(1));
	//	fprintf(fp," -\"- +/- :\t%g\n",sigma5(1));

	fclose(fp);

//	OP[0]=1;
//	fp=fopen("./temp/msd.dat","w");
//	
//	for(i=0;i<=get;i++)
//	{
//		fprintf(fp,"%g\t%g\n",OP[i],MSD[i]);
//	}
//	fprintf(fp,"\n\n");
//	fclose(fp);
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
	t3 /= delta_t;
	tau_s /= delta_t;

    // setup simulation
    Motion* motion = NULL; 
    switch(mov)
    {
    case 0:
        motion = new ConstVelocity ( Dphi, rng, v0 );
        break;
    case 1:
    	motion = new BrownianMotion ( Dphi, rng, mu );
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

    // TODO: filename from commandline?
    Measure measure( "temp/measurements.txt" );

    switch(pr)
    {
    case 0:
    	plotter = new GNUPlotter ( measure, t_out/delta_t, vec );
	break;
    case 1:
        plotter = new VoidPlotter;
        break;
    case 2:
    	plotter = new GLPlotter;
	break;
    default:
	cerr << "Plotter == " << pr << "?! Bei dir hackt's wohl!!" << endl;
	return -1;
    }

    sheep->init(Ns);
    
    Simulation* simulation = NULL;
    if( pr == 2 )
    {
    	simulation = new InfiniteSimulation ( *plotter, tau_s, rng, measure, delta_t );
    }
    else
    {
    	simulation = new FiniteSimulation ( *plotter, tau_s, rng, measure, delta_t, t_end );
    }
    
    dogs.init(Nd, v0);

    //Print parameters
    paste_params( *motion );

    //measure time
    //simulate
    Clock clock;
    clock.tick();
    simulation->run();
    clock.tick();


    cout << "Time per run: " << clock.getFrameTime() << " s" << endl;
    // let's have some fun

    // clean up!!!!!!!!
    {
        delete sheep;
        delete simulation;
        delete plotter;
        delete motion;
    }

	return 0;
}

