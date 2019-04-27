

#include <iostream>
#include <sys/wait.h>
#include <vector>
#include <string>
#include <chrono>
#include <algorithm>
#include <unistd.h>
using namespace std;

typedef struct cmds{
  string cmd;
  chrono::duration<double> durr;
} cmds;
bool operator<(cmds &a, cmds &b){
  return a.durr<b.durr;
}

int main() {
  int pid = fork(); 
  vector <cmds> lst;
  cmds a;
  string cmd;
  if (pid == -1) 
    exit(-1); 

  else if (pid == 0)

  { 
    while (1) 
    {   cout<<"tinyshell>";
        getline(cin,cmd);
        a.cmd=cmd;
        string comd;
        for(int i=0;i<cmd.length();i++){
          if(cmd[i]!=' ')
            comd+=cmd[i];
        }
        if(comd=="exit"){
          exit(0);
        }
        else if(comd=="history"){
          auto start=chrono::system_clock::now();
          vector<cmds>::iterator itr;
          for (( ( lst.end() - lst.begin() ) >5 ) ? (itr=lst.begin()+5) : (itr=lst.end()-1) ;itr!=lst.begin()-1;itr--){
            cout<<(*itr).cmd<<"  "<<(*itr).durr.count()<<"s"<<endl;
          }
          auto end=chrono::system_clock::now();
          chrono::duration<double> dur = end-start;
          a.durr=dur;
        }
        else if(comd=="history-sbu"){
          auto start=chrono::system_clock::now();
          vector<cmds>::iterator itr;
          vector <cmds> lt=lst;
          sort(lt.rbegin(), lt.rend());
          for (itr=lt.begin();itr!=lt.end()&&itr!=(lt.begin()+5);itr++){
            cout<<(*itr).cmd<<"  "<<(*itr).durr.count()<<"s"<<endl;
          }
          auto end=chrono::system_clock::now();
          chrono::duration<double> dur = end-start;
          a.durr=dur;
        }
        else{
          char s[256]="";
          for (int i=0; i<cmd.length(); i++) 
            s[i]=cmd[i];
          auto start=chrono::system_clock::now();
          system(s);
          auto end=chrono::system_clock::now();
          chrono::duration<double> dur = end-start;
          a.durr=dur;
        }
        lst.push_back(a);
        } 
        } 
  
  
  else 
  wait(NULL); 
}
