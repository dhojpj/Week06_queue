#include "driver.h"

char menu(string title[])
{
   char ans;
   for(int i=0; i<12; i++)
           cout<<title[i]<<endl;
   cin>>ans;
   cin.ignore(100, '\n');
   return ans;
}

void perform(char ans, int &que, queue<char> &one, queue<char> &two)
{
   char item;
   bool repeat;
   char filename[80];
   ifstream in;
   ofstream out;
   switch(toupper(ans))
   {
      case 'S' : cout<<"Which queue do you wish to use (1 or 2)? ";
                 cin>>que;
                 if(que > 2 || que < 1) que = 1;
                 break;

      case 'R' :do
                {
                   repeat = false;
                   cout<<"Please enter a file name: ";
                   cin>>filename;
                   try
                   {
                     if(que == 1)
                        loadfile(one,filename);
                     else
                        loadfile(two,filename);
                   }
                   catch(int e)
                   {
                      cout<<"File not found. Please re-enter"<<endl;
                      repeat = true;
                   }
                 }while(repeat);
                 break;
      case 'W' : cout<<"Please enter a filename: ";
                 cin>>filename;
                 in.open(filename);
                 if(in.fail())
                 {
                   in.close();
                   out.open(filename);
                 }
                 else
                 {
                     in.close();
                     cout<<"This file exists. Do you want to (O)verwrite or (A)ppend, or (E)xit: ";
                     cin>>ans;
                     switch(toupper(ans))
                     {
                        case 'O' : out.open(filename);
                                   break;
                        case 'A' : out.open(filename,ios::app);
                                   break;
                        default  : return;
                     }
                 }
                 if(que == 1)
                       out<<one;
                 else
                       out<<two;
                 break;
      case 'P' : if(que == 1)
                    cout<<"The contents of queue one are: "<<endl<<one<<endl<<endl;
                 else
                    cout<<"The contents of queue two are: "<<endl<<two<<endl<<endl;
                 break;
      case '+' : cout<<"What is the item that you want to enqueue? ";
                 cin>>item;
                 if(que == 1) one << item;
                 else two << item;
                 break;
      case '-' :
                 if(que == 1) one >> item;
                 else two >> item;
                 cout<<"You dequeued: "<<item<<endl;
                 break;

     case 'Q' : cout<<"Good bye!!!"<<endl;
    }
    system("pause");
    system("cls");
}

void loadfile(queue<char> &one,char *filename)
{
   ifstream in;
   in.open(filename);
   if(in.fail())
   {
      in.close();
      throw 404;
   }
   while(in>>one);
}

void help()
{
     cout<<"/h or /H -- This message"<<endl
         <<"/sn or /Sn -- switch to queue n"<<endl
         <<"n=filename -- load queue n with data from file named filename"<<endl;
     exit(0);
}

void checkArgs(int argc, char *argv[],queue<char> &one,queue<char> &two, int &queue)
{
     char *filename, *queueNum;
     if(argc < 2) return;
     for(int i = 1; i < argc; i++)
     {
             if(argv[i][0] == '/')
                switch(toupper(argv[i][1]))
                {
                    case 'H': help();
                              break;
                    case 'S' : char num[30];
                               strcpy(num,argv[i]);
                               queue = atoi(num);
                               break;
                }
              if(strpbrk (argv[i], "="))
              {
                 char temp[80];
                 strcpy(temp, argv[i]);
                 queueNum = strtok(temp,"=");
                 filename = strtok(NULL,"=");
                 if(atoi(queueNum)==1)
                     loadfile(one, filename);
                 else
                     loadfile(two, filename);
              }
     }
}
