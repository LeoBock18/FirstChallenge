#include "gradmet.hpp"

fcpacs::parameters fcpacs::read_param_json(std::string const & filename){
    parameters defaults;

    std::ifstream check(filename);

    // Check existance of the file
    if(!check){
        std::cerr << "ERROR: parameter file " << filename << "does not exists, using default parameters" << std::endl;
        check.close();
        return defaults;
    }
    else
        check.close();

    // If file present, we read parameters from it
    std::ifstream f(filename);
    nlohmann::json data = nlohmann::json::parse(f);
    parameters param;
    
    param.epsilon_s = data.value("epsilon_s", defaults.epsilon_s);
    param.epsilon_r = data.value("epsilon_r", defaults.epsilon_r);
    param.kmax = data.value("kmax", defaults.kmax);
    param.alpha0 = data.value("alpha0", defaults.alpha0);
    param.mu = data.value("mu", defaults.mu);
    param.sigma = data.value("sigma", defaults.sigma);
    f.close();

    return param;
}

fcpacs::Real_vec fcpacs::operator-(Real_vec const & a, Real_vec const & b)
{
    Real_vec result;
    std::transform(a.begin(),a.end(),b.begin(),std::back_inserter(result),std::minus<Real>());
    return result;
}

fcpacs::Real_vec fcpacs::operator*(Real const & num, Real_vec const & vec)
{
    Real_vec result;
    std::transform(vec.begin(),vec.end(),std::back_inserter(result), [&num](auto & x){return num*x;});
    return result;
}

fcpacs::Real fcpacs::norm(Real_vec const & x)
{
    Real n{0.};
    for(const Real & i:x)
        n += i*i;
    return sqrt(n);
}

fcpacs::Real fcpacs::set_alpha_armijo(std::function< Real (Real_vec) > const & f, std::function< Real_vec (Real_vec) > const & grad_f,
                Real const & alpha0, Real_vec const & xk, Real const & sigma){
    Real alpha = alpha0;
    auto fun = [&](Real_vec x){return f(x)-f(x-alpha*grad_f(x)) >= sigma*alpha*norm(grad_f(x))*norm(grad_f(x));};
    while(!fun(xk)){
        alpha /= 2;
    }
    return alpha;
}