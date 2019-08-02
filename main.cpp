#include<iostream>
#include<fstream>
#include<cmath>
#include<cstdlib>
#include<vector>

//const float lambda=250e-6;
//const float channel_width=1e-3;
//const int steps_channel = 1e6 +1; //uneven to hit 0 axis
//const float d_emitter=1e-2;
//const float d_sensor=1e-2;
//const int steps_sensor=100;
//const float x_max=15e-3;


using namespace std;


void print_results(vector<float> result, int x_max, int steps_sensor){
  for (int i = 0; i < (int)result.size(); ++i){
    cout <<(float)i/(steps_sensor-1) * x_max << "\t" << result[i] << endl;
  }
}

void write_results(vector<float> results, char** argv){
  ofstream out(argv[8]);
  if(out.fail()){
    cout << "outfile cannot be created" << endl;
    return;
  }
  
  out << "#lambda=" << argv[1] << "; channel_width=" << argv[2] << "; steps_channel=" << argv[3] << "; steps_sensor=" << argv[4] << "; d_emitter=" << argv[5] << "; d_sensor=" << argv[6] << "; x_max=" << argv[7] << endl;

  //write data
  for (int i = 0; i < (int)results.size(); ++i){
    out << ( (float)i/(atof(argv[4])-1)*atof(argv[7]) ) << "\t" << results[i] << endl;
  }


}


vector<float> calculate(float lambda, float channel_width, int steps_channel, int steps_sensor, float d_emitter, float d_sensor, float x_max ){
  vector<float> results(steps_sensor);
  //every position on sensor
  //TODO: parallel
  for (int i = 0; i < steps_sensor; ++i){
      float x = (float)i/(steps_sensor-1) * x_max;
      float efield_real = 0;
      float efield_imag = 0;
    //every position in channel (aperture)
    for (int j = 0;  j < steps_channel; j++){
      float pos_channel = (float)j/(steps_channel-1)*channel_width - channel_width/2;
      float distance = sqrt( pow(d_emitter,2) + pow(pos_channel,2)  ) + sqrt( pow(d_sensor,2) + pow(x-pos_channel,2)  );
      float phase = 2.*M_PI / lambda * distance;
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
    

    vector<float> results = calculate(atof(argv[1]), atof(argv[2]), atoi(argv[3]), atoi(argv[4]), atof(argv[5]), atof(argv[6]), atof(argv[7]));
    
    //print_results(results, atoi(argv[7]), atof(argv[4]));
    
    write_results(results, argv);

    return 0;
}



