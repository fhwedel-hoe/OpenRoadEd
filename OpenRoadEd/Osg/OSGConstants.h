#ifndef OSGCONSTANTS_H
#define OSGCONSTANTS_H

//Global constants go here

//===============================
//Sampling step size
//===============================
//ChordLine step
const double CHORDLINE_STEP=1.;
//Road step
const double ROAD_STEP=4.5;
//Junction step
const double JUNCTION_STEP=3.;

//Junction elevation shift, so that the junction tracks are drawn above the road
const double JUNCTION_ELEVATION_SHIFT=0.05;

//Epsilon constant for length and s related precision
const double LENGTH_EPS = 0.0000001;

//Epsilon constant for Height related precision
const double HEIGHT_EPS = 1.e-6;

//Texture scaling along the road (along s)
//S is divided by this constant to define the number of tiling of the texture
const double TEXTURE_LENGTH_SCALING = 4.;




//===============================
//Road marks constants
//===============================
//widths for the two types of weight values
const double STD_ROADMARK_WIDTH=0.15;
const double BOLD_ROADMARK_WIDTH=0.3;

//elevation shift, so that the road mark is drawn above the road
const double ROADMARK_ELEVATION_SHIFT=0.05;

//broken mark tiling
const double ROADMARK_BROKEN_TILING=3.;



//===============================
//Grid Size
//===============================
const double MIN_GRID_X=0;
const double MAX_GRID_X=100;
const double MIN_GRID_Y=-50;
const double MAX_GRID_Y=50;
const double GRID_ROWS=10;
const double GRID_COLLUMNS=10;





#endif