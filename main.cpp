#include<iostream>
#include<fstream>
#include<cmath>
#include<cstdlib>
#include<vector>

//const double lambda=250e-6;
//const double channel_width=1e-3;
//const int steps_channel = 1e6 +1; //uneven to hit 0 axis
//const double d_emitter=1e-2;
//const double d_sensor=1e-2;
//const int steps_sensor=100;
//const double x_max=15e-3;


using namespace std;


void print_results(vector<double> result, int x_max, int steps_sensor){
  for (int i = 0; i < (int)result.size(); ++i){
    cout <<(double)i/(steps_sensor-1) * x_max << "\t" << result[i] << endl;
  }
}

void write_results(vector<double> results, char** argv){
  ofstream out(argv[8]);
  if(out.fail()){
    cout << "outfile cannot be created" << endl;
    return;
  }
  
  out << "#lambda=" << argv[1] << "; channel_width=" << argv[2] << "; steps_channel=" << argv[3] << "; steps_sensor=" << argv[4] << "; d_emitter=" << argv[5] << "; d_sensor=" << argv[6] << "; x_max=" << argv[7] << endl;

  //write data
  for (int i = 0; i < (int)results.size(); ++i){
    out << ( (double)i/(atof(argv[4])-1)*atof(argv[7]) ) << "\t" << results[i] << endl;
  }


}


vector<double> calculate(double lambda, double channel_width, int steps_channel, int steps_sensor, double d_emitter, double d_sensor, double x_max ){
  vector<double> results(steps_sensor);
  //every position on sensor
  #pragma omp parallel for 
  for (int i = 0; i < steps_sensor; ++i){
      double x = (double)i/(steps_sensor-1) * x_max;
      double efield_real = 0;
      double efield_imag = 0;
    //every position in channel (aperture)
    for (int j = 0;  j < steps_channel; j++){
      double pos_channel = (double)j/(steps_channel-1)*channel_width - channel_width/2;
      double distance =  sqrt( pow(d_emitter,2) + pow(pos_channel,2)  ) + sqrt( pow(d_sensor,2) + pow(x-pos_channel,2)  );
      double phase = 2.*M_PI / lambda * distance;
      efield_real += cos(phase) / steps_channel;
      efield_imag += sin(phase) / steps_channel;
     }
    
    results[i] = sqrt( pow(efield_real,2) + pow(efield_imag,2) );
  }

  return results;
}

int main(int argc, char** argv){
    
    if(argc != 9){
      cout << "usage: simple_diffraction <lambda> <channel_width> <steps_channel> <steps_sensor> <d_emitter> <d_sensor> <x_max> <output>" << endl;
      return 1; 
    } 
    

    vector<double> results = calculate(atof(argv[1]), atof(argv[2]), atoi(argv[3]), atoi(argv[4]), atof(argv[5]), atof(argv[6]), atof(argv[7]));
    
    //print_results(results, atoi(argv[7]), atof(argv[4]));
    
    write_results(results, argv);

    return 0;
}



