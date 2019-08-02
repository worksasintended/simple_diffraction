#include<iostream>
#include<cmath>
#include<stdlib.h>
#include<vector>

const double lambda=250e-6;
const double channel_width=1e-3;
const int steps_channel = 1e6 +1; //uneven to hit 0 axis
const double d_emitter=1e-2;
const double d_sensor=1e-2;
const int steps_sensor=100;
const double x_max=15e-3;


using namespace std;


void print_results(vector<double> result){
  for (int i = 0; i < steps_sensor; ++i){
    cout <<(double)i/(steps_sensor-1) * x_max << "\t" << result[i] << endl;
  }
}



vector<double> calculate(){
  vector<double> results(steps_sensor);
  //every position on sensor
  //TODO: parallel
  for (int i = 0; i < steps_sensor; ++i){
      double x = (float)i/(steps_sensor-1) * x_max;
      double efield_real = 0;
      double efield_imag = 0;
        
    //every position in channel (aperture)
    for (int j = 0;  j < steps_channel; j++){
      double pos_channel = (float)j/(steps_channel-1)*channel_width - channel_width/2;
      double distance = sqrt( pow(d_emitter,2) + pow(pos_channel,2)  ) + sqrt( pow(d_sensor,2) + pow(x-pos_channel,2)  );
      double phase = 2.*M_PI / lambda * distance;
      efield_real += cos(phase) / steps_channel;
      efield_imag += sin(phase) /steps_channel;
     }
    //normalize 
    efield_real = efield_real;
    efield_imag = efield_imag;
    
    results[i] = sqrt( pow(efield_real,2) + pow(efield_imag,2) );
  }

  return results;
}

int main(int argc, char** argv){
    
    vector<double> results = calculate();
    
    print_results(results);
    
    return 0;
}



