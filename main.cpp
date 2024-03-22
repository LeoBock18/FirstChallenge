#include "gradmet.hpp"
#include<fstream>
#include<string>
#include "../../../../pacs-examples/Examples/include/json.hpp"
#include "muparser_fun.cpp"


using json = nlohmann::json;
using namesapce fcpacs;

Real_vec df_dx(Real_vec const & x);

parameters read_param_json(std::string const & filename);

int main(){
    // Real parameters from json file
    parameters param = read_param_json("grad_param.json");

    // Define functions with muparser (strings taken from json)
    std::ifstream f(filename);
    json data = json::parse(f);
    std::string fun_string = data.value("fun","");
    MuParserFun f(fun_string);

    // Define the function and its gradient
    //std::function< Real (Real_vec) > f = [](auto const & x){return x[0]*x[1]+4*x[0]*x[0]*x[0]*x[0]+x[1]*x[1]+3*x[0];};
    std::function< Real_vec (Real_vec) > df(df_dx);

    // Run the gradient method
    Real_vec ris = gradmet<armijo>(f, df, param);

    // Print the solution
    for(const auto & x : ris)
        std::cout << x << std::endl;

    return 0;
}

Real_vec df_dx(Real_vec const & x){
    Real_vec res;
    auto df_dx1 = [&x](){return x[1]+16*pow(x[0],3)+3;};
    auto df_dx2 = [&x](){return x[0]+2*x[1];};
    res.push_back(df_dx1());
    res.push_back(df_dx2());
    return res;    
}

parameters read_param_json(std::string const & filename){
    parameters default;

    std::ifstream check(filename);

    // Check existance of the file
    if(!check){
        std::cerr << "ERROR: parameter file " << filename << "does not exists, using default parameters" << std::endl;
        check.close();
        return default;
    }
    else
        check.close();

    // If file present, we read parameters from it
    std::ifstream f(filename);
    json data = json::parse(f);
    parameters param;
    
    param.epsilon_s = data.value("epsilon_s", default.epsilon_s);
    param.epsilon_r = data.value("epsilon_r", default.epsilon_r);
    param.kmax = data.value("kmax", default.kmax);
    param.alpha0 = data.value("alpha0", default.alpha0);
    param.mu = data.value("mu", default.mu);
    param.sigma = data.value("sigma", default.sigma);
    f.close();

    return param;
}