#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H


#include <iostream>
#include <cstdlib>
#include <vector>
#include<string>
using namespace std;

class term // this class shows cx^p
{
private:
    float coefficient;
    int power;

public:
    term(float, int);
    pair<float, int> get_term() { return {coefficient, power}; }
    string get_string();
    float get_coefficient() const { return coefficient; }
    int get_power() const { return power; }
    void set_coefficient(float c) { coefficient = c; }
    void set_power(int p) { power = p; }
    term operator+(const term &term2) const;
    term operator-(const term &term2) const;
    term operator*(const term &term2) const;
    term operator/(const term &term2) const;
    term &operator+=(const term &term2);
    term &operator-=(const term &term2);
    term &operator*=(const term &term2);
    term &operator/=(const term &term2);
    term &operator=(const term &term2);
    bool operator>(const term &term2) const;
    bool operator>=(const term &term2) const;
    bool operator<(const term &term2) const;
    bool operator<=(const term &term2) const;
    bool operator==(const term &term2) const;
    bool operator!=(const term &term2) const;
    term operator~() const;
    term &operator++();
    term operator++(int);
    term &operator--();
    term operator--(int);
    float operator()(float x);
    // ostream& operator<<(ostream& os, const term& term);
};

// term::term(/* args */)
// {
// }

class term_exeption
{
public:
    string err;
    term_exeption(string err) : err(err) {}
};

class polynomial
{
private:
    vector<term> polynomial_vect;

    void sort_polynomial();

public:
    polynomial(vector<term> vect);
    polynomial(){}
    polynomial operator+(const polynomial &polynomial2) const;
    polynomial operator-(polynomial polynomial2) const;
    polynomial operator*(const polynomial &polynomial2) const;
    polynomial &operator+=(const polynomial &polynomial2);
    polynomial &operator-=(const polynomial &polynomial2);
    polynomial &operator*=(const polynomial &polynomial2);
    polynomial &operator=(const polynomial &polynomial2);
    bool operator>(const polynomial &polynomial2) const;
    bool operator>=(const polynomial &polynomial2) const;
    bool operator<(const polynomial &polynomial2) const;
    bool operator<=(const polynomial &polynomial2) const;
    bool operator==(const polynomial &polynomial2) const;
    bool operator!=(const polynomial &polynomial2) const;
    polynomial operator~() const;
    polynomial &operator++();
    polynomial operator++(int);
    polynomial &operator--();
    polynomial operator--(int);
    float operator()(float x);
    term operator[](int index)const;
    term &operator[](int index);
    int get_term_count()const{return this->polynomial_vect.size();}
    int get_grade()const{return this->polynomial_vect.size()?this->polynomial_vect[0].get_power():0;}
    string get_string();

    friend ostream &operator<<(ostream &os, const polynomial &poly);

};


#endif // POLYNOMIAL_H
