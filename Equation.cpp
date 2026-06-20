#include "Equation.hpp"
#include <stdexcept>
#include <iostream>
#include <cmath>
#include <limits>
#include <iomanip>
//Initiating array with nan values
void initate_arr(double *solutions){
    solutions[0]=std::numeric_limits<double>::quiet_NaN();
    solutions[1]=std::numeric_limits<double>::quiet_NaN();
}
//Checking number of solutions and assign them
std::size_t solut_check(double const &a,double const &b,double const &delta,double *solutions){
    if(delta<0){
        
        for(int i=0;i<ARR_SIZE;i++){
            if(!(std::isnan(solutions[i]))){
                solutions[i]=std::numeric_limits<double>::quiet_NaN();
            }
        }
        return 0;
    }
    else if(delta==0){
        solutions[0]=(-b)/(2*a);
        solutions[1]=std::numeric_limits<double>::quiet_NaN();
        return 1;
    }
    solutions[0]=(-b+sqrt(delta))/(2*a);
    solutions[1]=(-b-sqrt(delta))/(2*a);
    return 2;
}

Equation::Equation(double const &va,double const &vb,double const &vc):a{va},b{vb},c{vc},solutions{nullptr},solutions_size{0}{
    if(a==0){
        throw std::invalid_argument("A cant be 0\n");
    
    }
    else{
        double delta=b*b-4*a*c;
        solutions=new double [ARR_SIZE];
        initate_arr(solutions);
        solutions_size=solut_check(a,b,delta,solutions);            
    }
}
Equation:: ~ Equation(){
    delete [] solutions;
}
Equation::Equation(Equation const &o):a{o.a},b{o.b},c{o.c},solutions{nullptr},solutions_size{o.solutions_size}{
    solutions=new double[ARR_SIZE];
    initate_arr(solutions);
    for(int i=0;i<ARR_SIZE;i++){
        solutions[i]=o.solutions[i];        
    }
}
Equation & Equation::operator =(Equation const &o){
    if(this!=&o){
        a=o.a;
        b=o.b;
        c=o.c;
        solutions_size=o.solutions_size;
        double *tmp=new double[ARR_SIZE];
        delete [] solutions;
        solutions=tmp;
        for(int i=0;i<ARR_SIZE;i++){
            solutions[i]=o.solutions[i];
        }
    }
    return *this;
}
Equation::Equation(Equation &&o):a{o.a},b{o.b},c{o.c},solutions{o.solutions},solutions_size{o.solutions_size}{
    o.solutions=nullptr;
}
Equation & Equation::operator =(Equation &&o){
    if(this!=&o){
        delete [] solutions;
        a=o.a;
        b=o.b;
        c=o.c;
        solutions=o.solutions;
        solutions_size=o.solutions_size;
        o.solutions=nullptr;
    }
    return *this;
}

double Equation::get_a()const{
    return a;
}
double Equation::get_b()const{
    return b;
}
double Equation::get_c()const{
    return c;
}
Equation & Equation::set_a(double const &val){
    if(val==0){        
        throw std::invalid_argument("A cant be 0\n");
    }
    else{
        a=val;
        double delta=b*b-4*a*c;
        solutions_size=solut_check(a,b,delta,solutions);
    }
    return *this;

}
Equation & Equation::set_b(double const &val){
    b=val;
    double delta=b*b-4*a*c;
    solutions_size=solut_check(a,b,delta,solutions);
    return *this;
}
Equation & Equation::set_c(double const &val){
    c=val;
    double delta=b*b-4*a*c;
    solutions_size=solut_check(a,b,delta,solutions);
    return *this;
}
std::size_t Equation::get_solutions_size() const{
    return solutions_size;
}
double const * Equation::get_solutions(){
    return solutions;
}
Equation operator + (Equation const &eq1,Equation const &eq2){
    Equation new_eq((eq1.get_a()+eq2.get_a()),(eq1.get_b()+eq2.get_b()),(eq1.get_c()+eq2.get_c()));
    return new_eq;
}
Equation operator + (Equation const &eq, double const &c){
    Equation new_eq(eq.get_a(),eq.get_b(),eq.get_c()+c);
    return new_eq;
}
Equation operator+(double const &c, Equation const & eq){
    Equation new_eq(eq.get_a(),eq.get_b(),eq.get_c()+c);
    return new_eq;
}
std::ostream & operator <<(std::ostream &out,Equation const & eq){
    out<<std::fixed<<std::setprecision(1);
    out<<eq.get_a()<<" X^2 + "<<eq.get_b()<<" X + "<<eq.get_c()<<" = 0";
    return out;
}
