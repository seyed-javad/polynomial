#include <iostream>
#include <cstdlib>
#include<string>
#include "polynomial.h"

term::term(float coefficient, int power) : coefficient(coefficient), power(power) {}

string term::get_string(){

    string output;

    if (this->get_coefficient() == 0)
    {
        output="0";
        return output;
    }
    if (this->get_coefficient() == 1)
    {
        if(this->get_power() == 0){
        output= "1";
        return output;
        }
        if(this->get_power() == 1){
        output= "x";
        return output;
        }
        output= "x^" + to_string(this->get_power());
        return output;
    }
    output= to_string(this->get_coefficient());
    if(this->get_power() == 1){
        output+= "x";
        return output;
    }
    if(this->get_power() != 0){
    output+="x^" + to_string(this->get_power());
    }
    return output;

}
term term::operator+(const term &term2) const
{
    if (power == term2.power)
    {
        return term(coefficient + term2.coefficient, power);
    }
    else
    {
        throw term_exeption("cant +");
    }
}
term term::operator-(const term &term2) const
{
    if (power == term2.power)
    {
        return term(coefficient - term2.coefficient, power);
    }
    else
    {
        throw term_exeption("cant -");
    }
}
term term::operator*(const term &term2) const
{
    return term(coefficient * term2.coefficient, power + term2.power);
}
term term::operator/(const term &term2) const
{
    if (term2.coefficient == 0)
    {
        throw term_exeption("divided by 0");
    }
    else
    {
        return term(coefficient / term2.coefficient, power - term2.power);
    }
}
term &term::operator+=(const term &term2)
{
    *this = this->operator+(term2);
    return *this;
}
term &term::operator-=(const term &term2)
{
    *this = this->operator-(term2);
    return *this;
}
term &term::operator*=(const term &term2)
{
    *this = this->operator*(term2);
    return *this;
}
term &term::operator/=(const term &term2)
{
    *this = this->operator/(term2);
    return *this;
}
term &term::operator=(const term &term2)
{
    coefficient = term2.coefficient;
    power = term2.power;
    return *this;
}
bool term::operator>(const term &term2) const
{
    if (power == term2.power)
    {
        return (coefficient > term2.coefficient) ? true : false;
    }
    return (power > term2.power) ? true : false;
}
bool term::operator>=(const term &term2) const
{
    //if (power == term2.power)
    //{
    //    return (coefficient >= term2.coefficient) ? true : false;
    //}
    return (power >= term2.power) ? true : false;
}
bool term::operator<(const term &term2) const
{
    if (power == term2.power)
    {
        return (coefficient < term2.coefficient) ? true : false;
    }
    return (power < term2.power) ? true : false;
}
bool term::operator<=(const term &term2) const
{
    //if (power == term2.power)
    //{
    //    return (coefficient <= term2.coefficient) ? true : false;
    //}
    //else
    //{
    //    throw term_exeption("cant <=");
    //}
    return (power <= term2.power) ? true : false;
}
bool term::operator==(const term &term2) const
{
    if (power == term2.power)
    {
        return (coefficient == term2.coefficient) ? true : false;
    }
    else
    {
        throw term_exeption("cant ==");
    }
}
bool term::operator!=(const term &term2) const
{
    return (power != term2.power || coefficient != term2.coefficient) ? true : false;
}
term term::operator~() const
{
    if(this->get_power() == 0){
        return term(0,1);
    }
    return term(coefficient * power, power - 1);
}
term &term::operator++()
{
    // term t(1, 0);
    // try
    // {
    // return *this += t;
    // }
    // catch (term_exeption e)
    // {
    // throw term_exeption("cant ++");
    // }

    if (power == 0)
    {
        coefficient++;
        return *this;
    }
    else
    {
        throw term_exeption("cant ++");
    }
}
term term::operator++(int)
{
    if (power == 0)
    {
        term temp(*this);
        coefficient++;
        return temp;
    }
    else
    {
        throw term_exeption("cant ++");
    }
}
term &term::operator--()
{
    if (power == 0)
    {
        coefficient--;
        return *this;
    }
    else
    {
        throw term_exeption("cant --");
    }
}
term term::operator--(int)
{
    if (power == 0)
    {
        term temp(*this);
        coefficient--;
        return temp;
    }
    else
    {
        throw term_exeption("cant --");
    }
}
float term::operator()(float x)
{
    if (power == 0 && x == 0)
    {
        throw term_exeption("0^0");
    }
    else
    {

        float temp = 1;
        for (int i = 0; i < power; i++)
        {
            temp *= x;
        }
        return temp * coefficient;
    }
}

string polynomial::get_string(){
    string output="";
    if(this->get_term_count() == 0){
        output = "0";
        return output;
    }
    output+=this->polynomial_vect[0].get_string();
    for(int g=1;g<this->get_term_count();g++){
        if(this->polynomial_vect[g].get_coefficient() > 0){
            output+= "+";
        }
        output += this->polynomial_vect[g].get_string();
    }
    return output;
}

polynomial::polynomial(vector<term> vect){
    for(int i=0;i<vect.size();i++){
        polynomial_vect.push_back(vect[i]);
    }
    this->sort_polynomial();
}

void polynomial::sort_polynomial()
{

    // adding repeated power to first one
    int s = this->polynomial_vect.size();
    for (int i = 0; i < s - 1; i++)
    {
        for (int z = i + 1; z < s; z++)
        {
            if (this->polynomial_vect[i].get_power() == this->polynomial_vect[z].get_power())
            {
                this->polynomial_vect[i] += this->polynomial_vect[z];
                this->polynomial_vect[z].set_coefficient(0);
            }
        }
    }
    // deleting repeated power
    for (int i = 0; i < this->polynomial_vect.size(); i++)
    {
        if (this->polynomial_vect[i].get_coefficient() == 0 && this->polynomial_vect.size() != 1)
        {
            this->polynomial_vect.erase(this->polynomial_vect.begin() + i);
            i--;
        }
    }
    // sorting polynomial
    float temp_c;
    int temp_p;
    for (int r = 0; r < this->polynomial_vect.size() - 1; r++)
    {
        for (int e = r + 1; e < this->polynomial_vect.size(); e++)
        {
            if (this->polynomial_vect[r].get_power() < this->polynomial_vect[e].get_power())
            {
                // swaping terms
                temp_c = this->polynomial_vect[r].get_coefficient();
                this->polynomial_vect[r].set_coefficient(this->polynomial_vect[e].get_coefficient());
                this->polynomial_vect[e].set_coefficient(temp_c);

                temp_p = this->polynomial_vect[r].get_power();
                this->polynomial_vect[r].set_power(this->polynomial_vect[e].get_power());
                this->polynomial_vect[e].set_power(temp_p);
            }
        }
    }
}

polynomial polynomial::operator+(const polynomial &polynomial2) const
{
    polynomial final_poly(*this);
    for (int q = 0; q < polynomial2.polynomial_vect.size(); q++)
    {
        final_poly.polynomial_vect.push_back(polynomial2.polynomial_vect[q]);
    }
    final_poly.sort_polynomial();
    return final_poly;
}
polynomial polynomial::operator-(polynomial polynomial2) const
{
    polynomial final_poly(*this);
    for (int y = 0; y < polynomial2.polynomial_vect.size(); y++)
    {
        polynomial2.polynomial_vect[y].set_coefficient(polynomial2.polynomial_vect[y].get_coefficient() * -1);
    }
    final_poly += polynomial2;
    return final_poly;
}
polynomial polynomial::operator*(const polynomial &polynomial2) const
{
    polynomial final_poly;
    for(int s=0;s<this->polynomial_vect.size();s++){
        for(int p=0;p<polynomial2.polynomial_vect.size();p++){
            final_poly.polynomial_vect.push_back(this->polynomial_vect[s] * polynomial2.polynomial_vect[p]);
        }
    }
    final_poly.sort_polynomial();
    return final_poly;
}
polynomial &polynomial::operator+=(const polynomial &polynomial2)
{
    *this = *this + polynomial2;
    return *this;
}
polynomial &polynomial::operator-=(const polynomial &polynomial2){
    *this = *this - polynomial2;
    return *this;
}
polynomial &polynomial::operator*=(const polynomial &polynomial2){
    *this = *this * polynomial2;
    return *this;
}
polynomial &polynomial::operator=(const polynomial &polynomial2){
    this->polynomial_vect.clear();
    for(int g=0;g<polynomial2.polynomial_vect.size();g++){
        this->polynomial_vect.push_back(polynomial2.polynomial_vect[g]);
    }
    this->sort_polynomial();
    return *this;
}
bool polynomial::operator>(const polynomial &polynomial2) const{
    //this->sort_polynomial();
    //polynomial2.sort_polynomial();

    // considered to be sorted

    //int size_=(this->polynomial_vect.size() < polynomial2.polynomial_vect.size()) ? this->polynomial_vect.size() : polynomial2.polynomial_vect.size();
    //for(int i=0;i<size_;i++){
    //    if(this->polynomial_vect[i] > polynomial2.polynomial_vect[i]){
     //       return true;
    //    }
    //}
    int w=0;
    int min_size=min(this->polynomial_vect.size(),polynomial2.polynomial_vect.size());
    while((this->polynomial_vect[w].get_power() == polynomial2.polynomial_vect[w].get_power()) && (this->polynomial_vect[w].get_coefficient() == polynomial2.polynomial_vect[w].get_coefficient()) && w<min_size){
        w++;
    }
    return (this->polynomial_vect[w] > polynomial2.polynomial_vect[w]);

}

bool polynomial::operator>=(const polynomial &polynomial2) const{
    return !((*this)<polynomial2);
}
bool polynomial::operator<(const polynomial &polynomial2) const{
    int w=0;
    int min_size=min(this->polynomial_vect.size(),polynomial2.polynomial_vect.size());
    while((this->polynomial_vect[w].get_power() == polynomial2.polynomial_vect[w].get_power()) && (this->polynomial_vect[w].get_coefficient() == polynomial2.polynomial_vect[w].get_coefficient()) && w<min_size){
        w++;
    }
    return (this->polynomial_vect[w] < polynomial2.polynomial_vect[w]);
}
bool polynomial::operator<=(const polynomial &polynomial2) const{
    return !((*this)>polynomial2);
}
bool polynomial::operator==(const polynomial &polynomial2) const{
    // considered to be sorted
    if(this->polynomial_vect.size() == polynomial2.polynomial_vect.size()){
        for(int r=0;r<polynomial2.polynomial_vect.size();r++){
            if(this->polynomial_vect[r] != polynomial2.polynomial_vect[r]){
                return false;
            }
        }
        return true;
    }
    return false;
}
bool polynomial::operator!=(const polynomial &polynomial2) const{
    return !(*this == polynomial2);
}
polynomial polynomial::operator~() const{
    polynomial final_poly;
    for(int e=0;e < this->polynomial_vect.size();e++){
        final_poly.polynomial_vect.push_back(~(this->polynomial_vect[e]));
    }
    final_poly.sort_polynomial();
    return final_poly;
}
polynomial &polynomial::operator++(){
    term temp(1,0);
    this->polynomial_vect.push_back(temp);
    this->sort_polynomial();
    return *this;
}
polynomial polynomial::operator++(int){
    polynomial temp_poly(this->polynomial_vect);
    term temp(1,0);
    this->polynomial_vect.push_back(temp);
    this->sort_polynomial();
    return temp_poly;
}
polynomial &polynomial::operator--(){
    term temp(-1,0);
    this->polynomial_vect.push_back(temp);
    this->sort_polynomial();
    return *this;
}
polynomial polynomial::operator--(int){
    polynomial temp_poly(this->polynomial_vect);
    term temp(-1,0);
    this->polynomial_vect.push_back(temp);
    this->sort_polynomial();
    return temp_poly;
}
float polynomial::operator()(float x){
    float sum=0;
    for(int f=0;f<this->polynomial_vect.size();f++){
        sum+=this->polynomial_vect[f](x);
    }
    return sum;
}
term polynomial::operator[](int index)const{
    return this->polynomial_vect[index];
}
term &polynomial::operator[](int index){
    return this->polynomial_vect[index];
}
