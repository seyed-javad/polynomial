#include <iostream>
#include <cstdlib>
#include<fstream>
#include "polynomial.h"
using namespace std;

term str_to_term(string);

ostream &operator<<(ostream &os, const term &term)
{
    // -5  x  3x  6x^5
    // coeff: 0  1  !=1
    // power: 0  1  !=1

    if (term.get_coefficient() == 0)
    {
        os << '0';
        return os;
    }
    if (term.get_coefficient() == 1)
    {
        if(term.get_power() == 0){
        os << '1';
        return os;
        }
        if(term.get_power() == 1){
        os << 'x';
        return os;
        }
        os<<"x^"<<term.get_power();
        return os;
    }
    os<<term.get_coefficient();
    if(term.get_power() == 1){
        os<<'x';
        return os;
    }
    if(term.get_power() != 0){
    os<<"x^"<<term.get_power();
    }
    return os;

}
int find(string str, char ch)
{
    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] == ch)
        {
            return i;
        }
    }
    return -1;
}
istream &operator>>(istream &is, term &term)
{
    //  [-] [float] [x] [^int]

    //   -    1.1    x
    //        5      x   ^3

    string str;
    is >> str;
    term=str_to_term(str);
    /*
    int x_pos = find(str, 'x');
    if (x_pos != -1)
    {
        if (x_pos != 0)
        {
            term.set_coefficient(atof(str.substr(0, x_pos).c_str()));
        }
        else
        {
            // x   x^int
            term.set_coefficient(1);
        }
        if(x_pos<(str.size()-1)){
            term.set_power(atoi(str.substr(x_pos+2,str.size()-x_pos+2).c_str()));
        }else{
            term.set_power(1);
        }
    }else{
        // float
        term.set_power(0);
        term.set_coefficient(atof(str.c_str()));
    }
    */

    return is;

}
term str_to_term(string str){
    term term(0,0);
    int x_pos = find(str, 'x');
    if (x_pos != -1)
    {
        if (x_pos != 0)
        {
            if(x_pos == 1 && str[0]== '-'){
                term.set_coefficient(-1);
            }else if(x_pos == 1 && str[0]== '+'){
                term.set_coefficient(1);
            }else{
            term.set_coefficient(atof(str.substr(0, x_pos).c_str()));
            }
        }
        else
        {
            // x   x^int
            term.set_coefficient(1);
        }
        if(x_pos<(str.size()-1)){
            term.set_power(atoi(str.substr(x_pos+2,str.size()-x_pos+2).c_str()));
        }else{
            term.set_power(1);
        }
    }else{
        // float
        term.set_power(0);
        term.set_coefficient(atof(str.c_str()));
    }
    return term;
}
ostream &operator<<(ostream &os, const polynomial &poly)
{
    if(poly.get_term_count() == 0){
        os<<0;
        return os;
    }
    os<<poly.polynomial_vect[0];
    for(int g=1;g<poly.get_term_count();g++){
        if(poly.polynomial_vect[g].get_coefficient() > 0){
            os<<'+';
        }
        os<<poly.polynomial_vect[g];
    }
    return os;
}
polynomial str_to_poly(string str){
    vector<term> vect;
    int i=0;
    while(i<str.size()){
            int f=i+1;
    while((str[f] != '+') && (str[f] != '-') && (f<str.size())){
        f++;
    }
    vect.push_back(str_to_term(str.substr(i,f-i)));
    i=f;
    }
    polynomial pol(vect);
    return pol;

}

istream &operator>>(istream &is, polynomial &poly)
{

    string str;
    is >> str;
    /*
    vector<term> vect;
    //int sign_pos = find(str, '-');
    int i=0;
    while(i<str.size()){
            int f=i+1;
    while((str[f] != '+') && (str[f] != '-') && (f<str.size())){
        f++;
    }
    //poly.polynomial_vect.push_back(str_to_term(str.substr(0,i)));
    vect.push_back(str_to_term(str.substr(i,f-i)));
    i=f;

    }
    polynomial pol(vect);
    //poly = polynomial(vect);
    */
    poly = str_to_poly(str);

    //poly.sort_polynomial();
    //cout<<pol<<endl;
    //cout<<poly<<endl;

    return is;

}

void save_to_textfile(string str,string filename){
    ofstream fout(filename.c_str());
    if(fout){
        fout<<str;
        fout.close();
    }
}
void save_to_binaryfile(polynomial &poly,string filename){
    ofstream fout(filename.c_str(),ios::binary);
    if(fout){
        fout.write((char*)&poly,sizeof(poly));
        fout.close();
    }

}
polynomial load_from_binaryfile(string filename){
    polynomial poly;
    ifstream fin(filename.c_str(),ios::binary);
    if(fin){
        fin.read((char*)&poly,sizeof(poly));
        fin.close();
        return poly;
    }else{
        //throw
    }
}
polynomial load_from_textfile(string filename){
    polynomial poly;
    string str;
    ifstream fin(filename.c_str());
    if(fin){
        fin>>str;
        fin.close();
        poly = str_to_poly(str);
        return poly;
    }else{
        //throw
    }
}

void poly_menu(polynomial current_poly){
    int s_o=0;
    polynomial poly;
    do{
        cout<<"--- Polynomial Menu ---\n";
        cout<<"Current Polynomial : "<<current_poly<<endl;

        cout<<"1- Add\n"
            <<"2- Subtract\n"
            <<"3- Multiply\n"
            <<"4- Derivative\n"
            <<"5- Find Degree\n"
            <<"6- Find Value For Specific x\n"
            <<"7- Compare\n"
            <<"8- Save To a Text File\n"
            <<"9- Save To a Binary File\n"
            <<"10- Back To Main Menu\n";
        do{
        cout<<"enter a number : ";
        cin>>s_o;
        }while(s_o != 1 && s_o != 2 && s_o != 3 && s_o != 4 && s_o != 5 && s_o != 6 && s_o != 7 && s_o != 8 && s_o != 9 && s_o != 10);
        //system("cls");
        switch(s_o){
            case 1:{
                cout<<"enter polynomial : ";
                cin>>poly;
                current_poly += poly;
                break;}
            case 2:{
                cout<<"enter polynomial : ";
                cin>>poly;
                current_poly -= poly;
                break;}
            case 3:{
                cout<<"enter polynomial : ";
                cin>>poly;
                current_poly *= poly;
                break;}
            case 4:{
                current_poly = ~current_poly;
                break;}
            case 5:{
                cout<<"current polynomial degree : "<<current_poly.get_grade()<<endl;
                break;}
            case 6:{
                float x;
                cout<<"enter x : ";
                cin>>x;
                cout<<"value of current polynomial for x="<<x<<" : "<<current_poly(x)<<endl;
                break;}
            case 7:{
                polynomial input;
                cout<<"enter polynomial : ";
                cin>>input;
                cout<<"comparing :\n";
                if(current_poly > input){
                cout<<"current polynomial > other polynomial"<<endl;}
                if(current_poly >= input){
                cout<<"current polynomial >= other polynomial"<<endl;}
                if(current_poly < input){
                cout<<"current polynomial < other polynomial"<<endl;}
                if(current_poly <= input){
                cout<<"current polynomial <= other polynomial"<<endl;}
                if(current_poly == input){
                cout<<"current polynomial == other polynomial"<<endl;}
                break;}
            case 8:{
                string filename;
                cout<<"enter file name : ";
                cin>>filename;
                save_to_textfile(current_poly.get_string(),filename);
                break;}
            case 9:{
                string filename;
                cout<<"enter file name : ";
                cin>>filename;
                save_to_binaryfile(current_poly,filename);
                break;}

        }


    //system("cls");
    }while(s_o != 10);

}


int main()
{

    polynomial current_polynomial;
    int selected_option=0;
    do{
        cout<<"--- main menu ---\n";
        cout<<"1- New Polynomial\n"
            <<"2- Load From Text File\n"
            <<"3- Load From Binary File\n"
            <<"4- Quit\n";
        do{
        cout<<"enter a number : ";
        cin>>selected_option;
        }while(selected_option != 1 && selected_option != 2 && selected_option != 3 && selected_option != 4);
        system("cls");
        switch(selected_option){
            case 1:
                poly_menu(current_polynomial);
                break;
            case 2:{
                string filename;
                cout<<"enter file name : ";
                cin>>filename;
                current_polynomial= load_from_textfile(filename);
                poly_menu(current_polynomial);

                break;}
            case 3:{
                string filename;
                cout<<"enter file name : ";
                cin>>filename;
                current_polynomial = load_from_binaryfile(filename);
                poly_menu(current_polynomial);
                break;}
        }



    }while(selected_option != 4);


    return 0;
}
