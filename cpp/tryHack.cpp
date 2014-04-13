// Example of using the GeographicLib::GravityModel class
#include <iostream>
#include <exception>
#include <GeographicLib/GravityModel.hpp>
#include <math.h>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;
using namespace GeographicLib;
int main() {
  try {
    int i=0,j=0;
    double latA[9000],lol;
    GravityModel grav("egm96");
    double lat = 27.99, lon = 86.93, h = 1292; // Mt Everest
    //double minLat=-85,maxLat=-15,minLon=26.22,maxLon=30;
    double ans,avg=9.78431,sd,sum=0;
    double gx, gy, gz;
    ofstream outfile;
    outfile.open("../GravityNew.json");
    std::ifstream  data("elev.csv");

    std::string line;
    outfile << "[[\"1990\",[";
    while(std::getline(data,line))
    {
        std::stringstream  lineStream(line);
        std::string        cell;

        while(std::getline(lineStream,cell,','))
        {
			lol = atof(cell.c_str());
            latA[i]=lol;
            cout << latA[i] << "\t";
            i=i+1;
            //cout <<"\n";
        }
        grav.Gravity(latA[j],latA[j+1], latA[j+2], gx, gy, gz);
		//cout << gx << " " << gy << " " << gz << "\n";
		ans=pow(pow(gx,2)+pow(gy,2)+pow(gz,2),0.5);
		sd=abs(avg-ans)/ans;
		sd=exp(sd*1000)/100;
		//cout << ans << "\n";
		outfile << latA[j]<< ","<<latA[j+1]<<","<<sd<<","<< endl;
		//outfile << latA[j]<< ","<<latA[j+1]<<","<<ans/10 <<",";
		j=i;
        //cout <<"\n" ;
    }
    //avg=sum/2480;
    //cout <<avg;
    outfile << "]]]";
	outfile.close();
    // open a file in write mode.
}
   /*ofstream outfile;
   outfile.open("afile.txt");

   cout << "Writing to the file" << endl;
   //cout << "Enter your name: ";

    for(i=0;i<1050;i++)
      {
    grav.Gravity(latA[i],latA[i+1], latA[i+2], gx, gy, gz);
    cout << gx << " " << gy << " " << gz << "\n";
    ans=pow(pow(gx,2)+pow(gy,2)+pow(gz,2),0.5);
    cout << ans << "\n";
    outfile << latA[i]<< ","<<latA[i+1]<<","<<ans<< endl;
      }
   outfile.close();
  }
  */
  catch (const exception& e) {
    cerr << "Caught exception: " << e.what() << "\n";
    return 1;
  }

  return 0;
}
//80.4, 88.12 : 26.22 , 30
