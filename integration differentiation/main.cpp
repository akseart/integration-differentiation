//
//  main.cpp
//  integration differentiation
//
//  Created by Артем on 20.05.2018.
//  Copyright © 2018 Артем. All rights reserved.
//

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
double test1( double x){
    return (x/(2*x+5));
}
double centrRectangle(double (*f) (double), double a, double b, double h){
    double area = 0.0;
    for (double x=a; x<b; x+=h) {
        area += f((x+h+x)/2);
    }
    return area*h;
}
double leftRectangle(double (*f) (double), double a, double b, double h){
    double area = 0.0;
    for (double x=a; x<=b; x+=h) {
        area += f(x);
    }
    return area*h;
}
double rightRectangle(double (*f) (double), double a, double b, double h){
    double area = 0.0;
    for (double x=a+h; x<=b; x+=h) {
        area += f(x);
    }
    return area*h;
}
double trapeze(double (*f) (double), double a, double b, double h){
    double area = 0.0;
    for (double x = a; x<b; x+=h){
        area += f(x)+f(x+h);
    }
    return h/((b-a)/h)*area;
}
double Simpson(double (*f) (double), double a, double b, double h){
    double area = 0.0;
    for (double x = a+h; x<b; x+=2*h){
        area += f(x-h)+4*f(x)+f(x+h);
    }
    return (h/3)*area;
}

int searchX(vector<double> x,double xi){
    for (int i = 0;i != x.size(); i++) {
        if (abs(x.at(i) - xi) < pow(10,-7)) return i;
    }
    return -1;
}
double diff1(vector<double> x,vector<double> y, double xi){
    int i = searchX(x, xi);
    if (i == -1)
        return INFINITY;
    if (i == x.size() - 1)
        return INFINITY;
    return (y.at(i+1)-y.at(i))/(x.at(i+1)-x.at(i));
};
double ddiff1(vector<double> x,vector<double> y, double xi){
    int i = searchX(x, xi);
    if (i == -1)
        return INFINITY;
    if ((i == x.size() - 1) || (i == 0))
        return INFINITY;
    return 2*(((y.at(i+1)-y.at(i))/(x.at(i+1)-x.at(i)) - ((y.at(i)-y.at(i-1))/(x.at(i)-x.at(i-1)))) / (x.at(i+1) - x.at(i-1)));
};
double diff2(vector<double> x,vector<double> y, double xi){
    int i = searchX(x, xi);
    if (i == -1)
        return INFINITY;
    if (i == x.size() - 1)
        return INFINITY;
    return (y.at(i+1)-y.at(i-1))/(x.at(i+1)-x.at(i-1));
};
double ddiff2(vector<double> x,vector<double> y, double xi){
    int i = searchX(x, xi);
    if (i == -1)
        return INFINITY;
    if ((i == x.size() - 2) || (i == 0))
        return INFINITY;
    double ddiff21 = (y.at(i+2) - y.at(i+1))/(x.at(i+2) - x.at(i+1));
    double ddiff22 = (y.at(i+1) - y.at(i))/(x.at(i+1) - x.at(i));
    return (ddiff21-ddiff22)/x.at(i+2)-x.at(i);
};
double RungeRombergDichardson (double Fn, double Fkn, double n, double kn){
    return Fn+((Fn - Fkn)/(kn/(kn-1)));
}

int main(int argc, const char * argv[]) {
    std::cout<< "x/(2x+5) h = 0.5"<<std::endl;
    std::cout << "Метод прямоугольников: "<<centrRectangle(test1, -1, 1, 0.5)<<endl;
    std::cout << "Метод левых прямоугольников: "<<leftRectangle(test1, -1, 1, 0.5)<<endl;
    std::cout << "Метод правых прямоугольников: "<<rightRectangle(test1, -1, 1, 0.5)<<endl;
    std::cout << "Метод трапеций: "<<trapeze(test1, -1, 1, 0.5)<<endl;
    std::cout << "Метод Симпсона: "<<Simpson(test1, -1, 1, 0.5)<<endl;
    std::cout<< "x/(2x+5) h = 0.25"<<std::endl;
    std::cout << "Метод прямоугольников: "<<centrRectangle(test1, -1, 1, 0.25)<<endl;
    std::cout << "Метод левых прямоугольников: "<<leftRectangle(test1, -1, 1, 0.25)<<endl;
    std::cout << "Метод правых прямоугольников: "<<rightRectangle(test1, -1, 1, 0.25)<<endl;
    std::cout << "Метод трапеций: "<<trapeze(test1, -1, 1, 0.25)<<endl;
    std::cout << "Метод Симпсона: "<<Simpson(test1, -1, 1, 0.25)<<endl;
    
    cout<<"\nУточнение по методу Рунге-Ромберга-Ричардсона"<<endl;
    cout<<"Метод прямоугольников: "<<RungeRombergDichardson(centrRectangle(test1, -1, 1, 0.25), centrRectangle(test1, -1, 1, 0.5), 0.25, 0.5)<<endl;
    cout << "Метод левых прямоугольников: "<<RungeRombergDichardson(leftRectangle(test1, -1, 1, 0.25), leftRectangle(test1, -1, 1, 0.5), 0.25, 0.5) <<endl;
    cout << "Метод правых прямоугольников: "<<RungeRombergDichardson(rightRectangle(test1, -1, 1, 0.25), rightRectangle(test1, -1, 1, 0.5), 0.25, 0.5) <<endl;
    cout << "Метод трапеций: "<<RungeRombergDichardson(trapeze(test1, -1, 1, 0.25), trapeze(test1, -1, 1, 0.5), 0.25, 0.5) <<endl;
    cout << "Метод Симпсона: "<<RungeRombergDichardson(Simpson(test1, -1, 1, 0.25), Simpson(test1, -1, 1, 0.5), 0.25, 0.5) <<endl;
    
    vector<double> x {-1.0,0.0,1.0,2.0,3.0};
    vector<double> y {-0.5,0.0,0.5,0.86,1.0};
    cout<<endl;
    cout<<"Первая производная 1-го порядка: "<<diff1(x,y,1.0)<<endl;
    cout<<"Вторая производная 1-го порядка: "<<ddiff1(x,y,1.0)<<endl;
    cout<<"Первая производная 2-го порядка: "<<diff2(x,y,1.0)<<endl;
    cout<<"Вторая производная 2-го порядка: "<<ddiff2(x,y,1.0)<<endl;
    return 0;
}
