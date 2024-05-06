//file header comments 

#ifndef DAY_OF_YEARR_H  //header Guards pr Protection from MUltiple Inclusion. if not define, define the class
#define DAY_OF_YEARR_H

#include <iostream>
using namespace std;

class DayOfYear{
public:
    // string getName() {return m_name;}
	// string getMaterial() {return m_material;}
	// double getLength() {return m_length;}
	// double getWidth() {return m_width;}
	// void setName(string _name) {m_name = _name;}
	// void setMaterial(string _material) {m_material = _material;}
	// void setLength(double _length) {m_length = _length;}
	// void setWidth(double _width) {m_width = _width;}

    string getMonth() {return m_month;}
    string getDay() {return m_day;}
    void setMonth(int month){m_month = month;}
    void setDay(int day){ m_day = day;}

private: 
    int m_month;  //member variable 
    int m_day;    //member variable
    void Output();
}