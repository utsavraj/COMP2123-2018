using namespace std;

#include "database.h"
#include <string>
#include <iostream>

bool customClassSort(const Grade & a, const Grade & b){
    return a.classID < b.classID;
}

bool customNameSort(const Profile &a, const Profile & b){
    return a.name < b.name;
}

bool customG(const Grade &a, const Grade & b){
    return a.mark < b.mark;
}


bool Database::add_profile(string id, string name, string phone) { 
    Profile temporary;
    temporary.studentID = id;
    temporary.name = name;
    temporary.phoneNumber = phone;
    vector <Profile> :: iterator itr;
    bool result = binary_search(profiles.begin(), profiles.end(), temporary); 
    if (result) 
    {   
        for (itr=profiles.begin();itr!=profiles.end(); itr++) {
            if ((*itr).studentID == id) {
                (*itr).name = name;
                (*itr).phoneNumber = phone;
                cout << "Profile Updated" << endl;
                return true;
            }
        }
    }
    else 
    {
    
    profiles.push_back(temporary); 
    
    sort (profiles.begin(),profiles.end() );
    return true;
    }
    
}

bool Database::add_grade(string id, string class_id, double grade){ 
    Grade temporary;
    temporary.studentID = id;
    Profile temporary1;
    temporary1.studentID = id;
    vector <Grade> :: iterator itr;
    bool result = binary_search(profiles.begin(), profiles.end(), temporary1); 
    if (result) 
    {   
        for (itr=grades.begin();itr!=grades.end(); itr++) {
            if ((*itr).studentID == id && (*itr).classID == class_id) {
            (*itr).mark = grade;
            cout << "Grade Updated" << endl;
            return true; 
            
            
            }
        
        }
        temporary.studentID = id;
        temporary.classID = class_id;
        temporary.mark = grade;
        grades.push_back(temporary);
        
    }
    else 
    {
        cout <<  "Student Not Exists" << endl; 
        return false;
    }

}

void Database::display_profiles(){
  vector<Profile>:: iterator itr;
  sort(profiles.begin(), profiles.end(), customNameSort);
   for (itr=profiles.begin();itr!=profiles.end();itr++){
      cout << (*itr).name << " " << (*itr).studentID << " " << (*itr).phoneNumber << endl;
    }
  sort(profiles.begin(), profiles.end());
}


void Database::display_grades(string class_id) {
    Grade temporary;
    temporary.classID = class_id;
    vector <Grade> :: iterator itr;
    bool result = binary_search(grades.begin(), grades.end(), temporary, customClassSort);
    if (result)
    {
        vector<Profile>::iterator PItr;
        vector<Profile> namesVector;
        for (itr=grades.begin(); itr!=grades.end(); itr++) {
            if ((*itr).classID == class_id) {
                string name = "";
                for(PItr=profiles.begin(); PItr!=profiles.end(); PItr++){
                    if((*PItr).studentID == (*itr).studentID){
                        Profile temp;
                        temp.studentID = (*PItr).studentID;
                        temp.name = (*PItr).name;
                        namesVector.push_back(temp);
                        break;
                    }
                }
            }
        }
        sort(namesVector.begin(), namesVector.end(), customNameSort);
        
        int ptr = 0;
        double sum = 0, min = 101, max = 0;
        vector <Grade> fake;
        for (itr=grades.begin(); itr!=grades.end(); itr++) {
            if ((*itr).classID == class_id && (*itr).studentID == namesVector[ptr].studentID) {
                double mark = (*itr).mark;
                sum += mark;
                if(mark > max){
                    max = mark;
                }
                if(mark < min){
                    min = mark;
                }
                Grade hku;
                hku.studentID = namesVector[ptr].name;
                hku.classID = (*itr).studentID;
                hku.mark = (*itr).mark;
                fake.push_back(hku);
                ptr++;
            }
            sort(fake.begin(), fake.end(), customG);
            vector <Grade> :: iterator itrfake;
            for(itrfake=fake.begin(); itrfake!=fake.end(); itrfake++)
            {
                cout << (*itrfake).studentID <<" "<< (*itrfake).classID <<" " << (*itrfake).mark << endl;
            }
        }
        cout <<"Min "<<min<<endl;
        cout <<"Max "<<max<<endl;
        cout <<"Average "<<sum/(ptr)<<endl;
        
    }else{
        cout <<"No Records Found"<<endl;
    }
    
}

bool Database::del_profile(string id){
Profile temps;
  temps.studentID=id;
  sort(profiles.begin(), profiles.end());
  bool result=binary_search(profiles.begin(),profiles.end(),temps);
  if(result){
vector<Profile>:: iterator itr;
    for (itr=profiles.begin();itr!=profiles.end();itr++){
      if((*itr).studentID==id){
        profiles.erase(itr);
    return true;
      }
    }
  }else{
    cout<<"Record Not Exists"<<endl;
    return true;
  }
}

bool Database::del_grade(string id, string class_id){
  Grade temps;
  temps.studentID=id;
  temps.classID=class_id;
  sort(grades.begin(), grades.end());
  bool result=binary_search(grades.begin(),grades.end(),temps);
if(result){
    vector<Grade>:: iterator itr;
    for (itr=grades.begin();itr!=grades.end();itr++){
      if((*itr).studentID==id && (*itr).classID==class_id){
        grades.erase(itr);
return true;
      }
    }
    cout<<"Record Not Exists"<<endl;
        return true;
  }else{
    cout<<"Record Not Exists"<<endl;
    return true;
  }
}


bool operator<( const Profile & a , const Profile & b ){
    return a.studentID < b.studentID;
}

bool operator<( const Grade & a , const Grade & b ){
return a.studentID < b.studentID;
}


