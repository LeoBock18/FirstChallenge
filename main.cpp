#include "gradmet.hpp"
#include<fstream>
#include<string>
#include "json.hpp"

using json = nlohmann::json;
using namespace fcpacs;

Real_vec df_dx(Real_vec const & x);

int main(){
    // Real parameters from json file
    parameters param = read_param_json("grad_param.json");

    // Define the function and its gradient: CHANGE HERE THE FUNCION
    std::function< Real (Real_vec) > f = [](auto const & x){return x[0]*x[1]+4*x[0]*x[0]*x[0]*x[0]+x[1]*x[1]+3*x[0];};
    std::function< Real_vec (Real_vec) > df(df_dx);

    // Run the gradient method: CHANGE HERE TEMPLATE INPUT TO CHANGE ALPHA METHOD
    Real_vec ris = gradmet<armijo>(f, df, param);

    // Print the solution
    std::cout << "Solution: " << std::endl;
    for(const auto & x : ris)
        std::cout << x << std::endl;

    return 0;
}

// CHANGE HERE GRADIENT COMPONENTS
Real_vec df_dx(Real_vec const & x){
    Real_vec res;
    auto df_dx1 = [&x](){return x[1]+16*pow(x[0],3)+3;};
    auto df_dx2 = [&x](){return x[0]+2*x[1];};
    res.push_back(df_dx1());
    res.push_back(df_dx2());
    return res;    
}