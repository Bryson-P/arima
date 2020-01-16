#include<stdio.h>
#include<iostream>
#include<fstream>
#include <iomanip>
#include<vector>
#include <stdlib.h>
#include<istream>
#include<string.h>
#include <sstream>
#include<cmath>


using namespace std;




void regression(vector <std::vector<double> > matrix) // Calculates line of best fit through the data
{
    vector <double> timesteps;
    //timesteps.push_back(0);
    int counter=0;
    for ( int t =0;t<matrix.size()-1;t++){
      counter++;
      timesteps.push_back(counter);

    }
    for ( int v =0; v<matrix.size()-1;v++){
      cout<<"Timestep is "<<timesteps[v]<<"\n";
      timesteps.push_back(counter);

    }


    int i,j,k;
    double a,b;
    int n=matrix.size()-1;
    double xsum=0,x2sum=0,ysum=0,xysum=0;                //variables for sums/sigma of xi,yi,xi^2,xiyi etc
    for (i=0;i<matrix.size()-1;i++)
    {
        xsum=xsum+timesteps[i];
        ysum=ysum+matrix[i][0];
        x2sum=x2sum+pow(timesteps[i],2);
        xysum=xysum+timesteps[i]*matrix[i][0];
    }
    a=(n*xysum-xsum*ysum)/(n*x2sum-xsum*xsum);
    double y_fit[n];
    for (i=0;i<n;i++)
        y_fit[i]=b+a*timesteps[i];
    cout<<"S.no"<<setw(5)<<"x"<<setw(19)<<"y(Actual)"<<setw(19)<<"y(fitted)"<<endl;
    cout<<"-----------------------------------------------------------------\n";
    for (i=0;i<n;i++)
        cout<<i+1<<"."<<setw(8)<<matrix[i][0]<<setw(15)<<timesteps[i]<<setw(18)<<y_fit[i]<<endl;



}

void AR(vector <std::vector<double> > matrix) // Forecasts future values
{
    vector <double> timesteps;
    //timesteps.push_back(0);
    int counter=0;
    for ( int t =0;t<3030;t++){
      counter++;
      timesteps.push_back(counter);

    }
    for ( int v =0; v<matrix.size()-1;v++){
      //cout<<"Timestep is "<<timesteps[v]<<"\n";


    }
    vector <double> price;
    for ( int i=0; i<matrix.size()-1;i++){
        price.push_back(matrix[i][0]);
    }

    for ( int i=0; i<price.size();i++){
      //cout<<price[i]<<"\n";
    }


    int i,j,k;
    double a,b,a2;
    int n=matrix.size()-1;
    double xsum=0,x2sum=0,ysum=0,xysum=0;                //variables for sums/sigma of xi,yi,xi^2,xiyi etc
  /*  for (i=0;i<n;i++)
    {
        xsum=xsum+timesteps[i];                        //calculate sigma(xi)
        ysum=ysum+matrix[i][0];                        //calculate sigma(yi)
        x2sum=x2sum+pow(timesteps[i],2);                //calculate sigma(x^2i)
        xysum=xysum+timesteps[i]*matrix[i][0];
        //cout<<"here"<<"\n";                   //calculate sigma(xi*yi)

    }*/
    for (i=0;i<matrix.size()-1;i++)
    {
        xsum=xsum+timesteps[i];
        ysum=ysum+price[i];
        x2sum=x2sum+pow(timesteps[i],2);
        xysum=xysum+timesteps[i]*price[i];
    }
    a=(n*xysum-xsum*ysum)/(n*x2sum-xsum*xsum);
    b=(x2sum*ysum-xsum*xysum)/(x2sum*n-xsum*xsum);
    a2=(n*xysum-xsum*ysum)/(n*x2sum-xsum*xsum);
    int forecast=3040;
    double y_fit[3030];
    ofstream myfile(rtn);
    for (int i=4;i<3030;i++) {

        y_fit[i]=(b+a*timesteps[i]+a2*price[i-1]+a2*price[i-2]+a2*price[i-3]);
        myfile << y_fit[i] << endl;
        if ( i>=3020){
        //cout<<y_fit[i]<<'\n';
         price.push_back(y_fit[i]);
        }
      }
    cout<<"S.no"<<setw(5)<<"x"<<setw(19)<<"y(Actual)"<<setw(19)<<"y(Prediction)"<<endl;
    cout<<"-----------------------------------------------------------------\n";
    for (i=0;i<3030-1;i++)
        //cout<<i+1<<"."<<setw(8)<<matrix[i][0]<<setw(15)<<timesteps[i]<<setw(18)<<y_fit[i]<<endl;//print a table of x,y(obs.) and y(fit.)
        cout<<i+1<<"."<<setw(8)<<price[i]<<setw(15)<<timesteps[i]<<setw(18)<<y_fit[i]<<endl;
    cout<<"\nValues past 3020 are forecasts:\n\n"<<endl;        //print the best fit line


}






double STD(vector <std::vector<double> > matrix ){
  double variance;
  double deviation;
  double period;

  deviation=sqrt(variance);
  return deviation;
}

vector<double> EMA(std:: vector <std::vector<double> > matrix){ // Used for moving average
  //cout<<" here";
  std:: vector<double> movingaverage;
  double period=0;
  int index =0;
  int counter =0; // used to control
  double average=0;
  movingaverage.push_back(0);
  movingaverage.push_back(0);
  movingaverage.push_back(0);
  movingaverage.push_back(0);
  movingaverage.push_back(0);
  double ma2[5];
  for ( int x=0; x<matrix.size(); x++){
    //printf("counter2: %d\n",x);
      period ++;
    for (int i=0; i< matrix[x].size();i++){

      movingaverage[counter]=(movingaverage[counter]+matrix[x][i]);
      counter++;
      if (counter==5){
      counter=0;
      for ( long int j=0; j<movingaverage.size();j++){
        //cout<<movingaverage[j]<<" herey ";
      }
      //cout<<"\n";
    }
      }
    //printf("\n");
  }
  //cout<<"period is "<<period<<"\n";
  for ( int q=0; q<movingaverage.size();q++){
    movingaverage[q]=(movingaverage[q]/period-1);
  }
  for ( long int j=0; j<movingaverage.size();j++){
    //cout<<movingaverage[j]<<"  ";
  }
  return movingaverage;
}

void ACF(std:: vector <std::vector<double> > matrix){
 vector<double> mean;
  vector<double> correlation;
  mean=EMA(matrix);


}

vector<double>  FOD(vector <std::vector<double> > matrix){ // Used for differencing
  vector<double> differenced;
  differenced.push_back(0);
  differenced.push_back(0);
  differenced.push_back(0);
  differenced.push_back(0);
  differenced.push_back(0);

  int counter;
  //cout<<matrix[0][0]<<" "<<matrix[2][1]<<"\n";
  for ( int x=0; x<3019; x++){
    //printf("counter2: %d\n",x);

    for (int i=0; i< matrix[x].size();i++){
    //  cout<<matrix[x][i]<<"  "<< matrix[x+1][i]<<" ";
      differenced[counter]=(matrix[x+1][i]-matrix[x][i]);
      cout<<matrix[x+1][i]-matrix[x][i]<<" ";
      counter+=1;
      if (counter==5){
      counter=0;
    }
    if (i==3000){
    break;
    }

  }
  printf("\n");

}


  return differenced;
}





int main(){





  std::ifstream apple("AAPL.csv");
  std:: vector <std::vector<double> > matrix;
  std:: string buffer;
  std::vector<std::string> buffer2;
  std::vector<double>initial;
  matrix.push_back(initial);
  long int  convert;
  int counter1=0;
  int counter2=0;

  std:: string buffer3;
  std:: string line;


  while(apple>>buffer){
    //cout<<buffer<<"\n";
    //buffer2.push_back(buffer);
    std::stringstream iss(buffer);
    std::string token;
    while (std::getline(iss,token, ',')){
      //cout<<"here"<<"\n";
      char*pointer;
      matrix[counter2].push_back(strtod(token.c_str(),&pointer));
      counter1++;
      if (counter1==5){
        counter1=0;
        counter2++;
        std::vector<double> temp;
        matrix.push_back(temp);

      }

      }


}

  int counterr =0;
  for (int x=0; x<matrix.size(); x++){
    //printf("counter2: %d\n",x);
    for (int i=0; i< matrix[x].size();i++){
      //printf("%d, ", matrix[x][i);
      //cout<<matrix[x][i]<<" ";
      counterr+=1;
      if (counterr==5){
        //cout<<"\n";
        counterr=0;
      }
      }

    //printf("\n");
  }

    //regression(matrix);

    AR(matrix);

    //EMA(matrix);

    //FOD(matrix);



   }
