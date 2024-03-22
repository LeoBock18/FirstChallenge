#ifndef GRADIENT_METHOD_HPP
#define GRADIENT_METHOD_HPP

#include<iostream>
#include<functional>
#include<vector>
#include<cmath>
#include<fstream>
#include<string>
#include "json.hpp"

// Namespace: First Challenge   PACS
namespace fcpacs{

// Defining aliasis for generalization
using Real = double;
using Real_vec = std::vector<Real>;

// Defining an enumerator for choosing alpha technique
enum method {exp_dec, inv_dec, armijo};

// Parameters defined in a struct
struct parameters{
    Real_vec x0 = {0,0};
    Real epsilon_s = 1e-6;
    Real epsilon_r = 1e-6;
    unsigned kmax = 3000;
    Real alpha0 = 0.1;
    Real mu = 0.2;
    Real sigma = 0.025;
};

// Function for reading parameters from a json file
parameters read_param_json(std::string const & filename);

// Vector operations needed
Real_vec operator-(Real_vec const &, Real_vec const &);

Real_vec operator*(Real const &, Real_vec const &);

Real norm(Real_vec const &);

// Alpha methods functions
inline Real set_alpha_exp(Real const & alpha0, Real const & mu, unsigned k)
{
    return alpha0*exp(-mu*k);
}

inline Real set_alpha_inv(Real const & alpha0, Real const & mu, unsigned k)
{
    return alpha0 / (1+mu*k);
}

Real set_alpha_armijo(std::function< Real (Real_vec) > const &, std::function< Real_vec (Real_vec) > const &,
                Real const &, Real_vec const &, Real const &);

// Main function for gradient method: M defines the alpha method selected
template<method M>
Real_vec gradmet(std::function< Real (Real_vec) > f, std::function< Real_vec (Real_vec) > grad_f, const parameters & param)
{
    // Initialize variables of the problem with parameters (dx,df in this way in order to enter the while-loop)
    unsigned k = 0;
    Real dx = param.epsilon_s + 1;
    Real df = param.epsilon_r + 1;
    Real alpha_init = param.alpha0;
    Real_vec xold = param.x0;
    Real alpha;
    while(k < param.kmax && dx >= param.epsilon_s && df >= param.epsilon_r){
        if constexpr (M == exp_dec){
            alpha = set_alpha_exp(alpha_init,param.mu,k);
        }
        if constexpr (M == inv_dec){
            alpha = set_alpha_inv(alpha_init,param.mu,k);
        }
        if constexpr (M == armijo){
            alpha = set_alpha_armijo(f, grad_f, alpha_init, xold, param.sigma);
        }
        Real_vec xnew = xold - alpha * grad_f(xold);
        dx = norm(xnew-xold);
        //df = std::abs(f(xnew)-f(xold));
        df = norm(grad_f(xold));
        std::swap(xold,xnew);
        ++k;
    }
    return xold;
}

} // end namespace

#endif /*GRADIENT_METHOD_HPP*/