//*****************************water quality checker*********************************
#include<iostream>
#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<iomanip>
#include<fstream>
#include<stdlib.h>
using namespace std;

//*****************************class*************************************************
class record{
	double ph,ec,tds,th,ca,cl,ni,su,do2,bod;
	char status[10];
	char day[10];
	double wqi;
	public: 
	void input(){ 
	    cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
	    cout<<"                   Type The Follwing Input:-           "<<endl;
		cout<<"                   1.Day                               ";
		cin>>day;
		cout<<"                   2.PH:                               ";
		cin>>ph;
		cout<<"                   3.Electical Conductivity:           ";
		cin>>ec;
		cout<<"                   4.Total Dissolve Solids:            ";
		cin>>tds;
		cout<<"                   5.Total Hardness:                   ";
		cin>>th;
		cout<<"                   6.Calcium:                          ";
		cin>>ca;
		cout<<"                   7.Cholrine:                         ";
		cin>>cl;
		cout<<"                   8.Nitrates:                         ";
		cin>>ni;
		cout<<"                   9.Sulphates:                        ";
		cin>>su;
		cout<<"                   10.Dissolve Oxygen:                 ";
		cin>>do2;
		cout<<"                   11.BOD:                             ";
		cin>>bod;
		cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
	
		double q[10];
	 	q[0]=100*((ph-7.0)/8.0);
		q[1]=100*((ec-0)/(300-0));
		q[2]=100*((tds-0)/(500-0));
		q[3]=100*((th-0)/(300-0));
		q[4]=100*((ca-0)/(75-0));
		q[5]=100*((cl-0)/(250-0));
		q[6]=100*((ni-0)/(45-0));
		q[7]=100*((su-0)/(150-0));
		q[8]=100*((do2-14.6)/(5-14.6));
		q[9]=100*((bod-0)/(5-0));
double wu[11]={0.2190,0.3710,0.0037,0.0062,0.0250,0.0074,0.0412,0.0124,0.3723,0.3723};

double sumwi=0;
for(int i=0;i<10;i++)
sumwi+=wu[i] ;

double wiqi=0;
for(int j=0;j<10;j++)
wiqi=wiqi+(q[j]*wu[j]);

  wqi=wiqi/sumwi;
  //cout<<"\nWQI:"<<wqi;
  
                      if(wqi>0&&wqi<25)
	                 strcpy (status,"excellent");
	                  if(wqi>25&&wqi<50)
	                 strcpy (status,"good");
	                  if(wqi>50&&wqi<75)
	                 strcpy (status,"bad");
	                  if(wqi>75&&wqi<100)
	                 strcpy (status,"very bad");
	                  if(wqi>100&&wqi<1000)
	                 strcpy (status,"unfit");
	                 cout<<"\nStatus:"<<status;
	}
	
	
	
	void show(){ cout<<"\nday:"<<day<<"\nwater quality index:"<<wqi;
		cout<<"\nStatus:"<<status;
	}
	
    char *ch(){
		return day;
	}
};

//*****************************function for options**********************************
void about()
{
	cout<<setw(100)<<"                WATER QUALITY CHECKER                    "<<endl;
cout<<"\nWQI indicates the quality of water in terms of index number which represents overall quality of water for any intended use.\n";
cout<<"\nIt  is defined as a rating reflecting the composite influence of different water quality parameters were taken into consideration for the calculation of water Quality index(WQI)";
cout<<"\nThe calculation of the WQI was done using weighted arithmetic water quality index which was originally proposed by Horton (1965) and developed by Brown et al (1972).\nThe weighted arithmetic water quality index (WQIA) is in the following form: \n";
cout<<"\nWQI=(sigma)WiQi(from i=0 to i=n / (sigma)Wi(from i=1 to i=n)\n";
cout<<"\nwi is the relative weight of the ith parameter and qi is the water quality rating of the ith parameter.\nThe unit weight (wi) of the various water quality parameters are inversely proportional to the recommended standards for the corresponding parameters\n";
cout<<"\nqi=100{(Vexp-Vact)/(Sstan-Videal)} \n";
}

void req(){
	cout<<"All the parameters expressed in mg/lit. except pH and EC (mmhos) \n";
	cout<<"Water samples must be collected from the source in sterile bottles (1 litre capacity) under aseptic conditions \n";
	cout<<" \n";
}

void cal()
{ record a;
 fstream ob;
 ob.open("sample.dat",ios::app);
 a.input();
 ob.write((char *)&a, sizeof(record));
 a.show();
 cout<<endl;
 ob.close();
	
}

void specific()
{  char n[10];
   cout<<"\nenter the date you want to see the record of:";
   cin>>n;
   record a;
   fstream ob;
   ob.open("sample.dat");
        if (!ob)
    	{
    		cout << "File could not be open !! ";
    		
    		return;
    	}
        while(!ob.eof())
      	{ ob.read((char *)&a,sizeof(record));	
		  if (strcmp(n,a.ch())==0)	
    		{ //ob.read((char *)&a,sizeof(record));
    		  a.show();
    		  break;
			}
    	//ob.read((char *)&a,sizeof(record));
		}
   ob.close();
}

void all()
{
	 	record a;
    	fstream ob;
    	ob.open("sample.dat");
    	if (!ob)
    	{
    		cout << "File could not be open !! ";
    		
    		return;
    	}
    	cout<<"\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
    	ob.read((char *)&a,sizeof(record));
    	  	while(!ob.eof())
      	{   
		    a.show();
		    cout<<"\npress any key for next record..\n";
		    getch();
      		ob.read((char *)&a,sizeof(record));
      		
	    }
	    ob.close();
}

void Delete()		
{
	char n[100];
	record a;
	cout<<"Enter record day that should be Deleted :";
	cin>>n;
	ofstream o;
	fstream fil;
	o.open("new.dat",ios::out|ios::app);
	fil.open("sample.dat",ios::in| ios::app);
	if(!fil)
	{
		cout<<"File not Found";
		exit(0);
	}
	else
	{
		fil.read((char*)&a, sizeof(record));
		while(!fil.eof())
		{
			if(strcmp(n,a.ch())!=0)
			{
				o.write((char*)&a, sizeof(record));
			}
			fil.read((char*)&a, sizeof(record));
		}
	}
	o.close();
	fil.close();
	remove("sample.dat");
	rename("new.dat", "sample.dat");
	cout<<"\n Record Deleted\n";
}

void prev()
{
	cout<<"\n1.specific record";
	cout<<"\n2.All records";
	cout<<"\n3.Delete record";
	cout<<"\nenter option:";
	int a;
	cin>>a;
	switch(a){
		case 1:specific();
		break;
		case 2:all();
		break;
		case 3:Delete();
		break;
		default: cout<<"\nerror";
	}
	
}

//******************************main fuction******************************************
main(){
	cout<<setw(100)<<"*********************************************************"<<endl;
	cout<<setw(100)<<"*               WATER QUALITY CHECKER                   *"<<endl;
	cout<<setw(100)<<"*              by:-Prabhat Kumar Dubey                  *"<<endl;
	cout<<setw(100)<<"*********************************************************"<<endl<<endl;
	OPTION:
	cout<<setw(100)<<"                   --::OPTIONS::--                       "<<endl;
	cout<<setw(100)<<"---------------------------------------------------------"<<endl;
	cout<<setw(100)<<"|            1.About Water Quality Index                |"<<endl;
	cout<<setw(100)<<"|            2.requirements to calculate WQI            |"<<endl;
	cout<<setw(100)<<"|            3.WQI Calculator                           |"<<endl;
	cout<<setw(100)<<"|            4.Previous Records                         |"<<endl;
	cout<<setw(100)<<"|            5.exit                                     |"<<endl;
	cout<<setw(100)<<"---------------------------------------------------------"<<endl;
	cout<<setw(61)<<"enter your option:";
	int opt;
	cin>>opt;
	switch(opt)
	{
		case 1:cout<<"you choose option 1:"<<endl;
		    about();
			break;
		case 2:cout<<"you choose option 2:"<<endl;
		    req();
			break;
		case 3:cout<<"you choose option 3:"<<endl;
		    cal();
			break;
		case 4:cout<<"you choose option 4:"<<endl;
		    prev();
			break;
		case 5:exit(0);
		default: cout<<"error";
		    break;
	}
	goto OPTION;
}
//**************************************program end************************************
