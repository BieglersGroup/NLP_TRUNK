// Author: David Thierry @dpthierry CMU 01-06-2020

#include "max_b0_nlp.hpp"
#include <iostream>
#include <cmath>

using namespace Ipopt;

MAX_B0_NLP::MAX_B0_NLP() {}
MAX_B0_NLP::~MAX_B0_NLP() {}

bool MAX_B0_NLP::get_nlp_info(Index &n, Index &m, Index &nnz_jac_g, Index &nnz_h_lag,
                              TNLP::IndexStyleEnum &index_style) {
    n = 2;
    m = 0;
    nnz_jac_g = 0;
    nnz_h_lag = 2;
    index_style = TNLP::C_STYLE;
    return true;
}

bool MAX_B0_NLP::get_bounds_info(Index n, Number *x_l, Number *x_u, Index m, Number *g_l, Number *g_u) {
    for (Index i=0; i < 2; i++){
        x_l[i] = 0.0;
        x_u[i] = 2e19;
    }
    return true;
}

bool MAX_B0_NLP::get_starting_point(Index n, bool init_x, Number *x, bool init_z, Number *z_L, Number *z_U, Index m,
                                    bool init_lambda, Number *lambda) {
    x[0] = 1.0E-09;
    x[1] = 1.0E-09;
    return true;
}

bool MAX_B0_NLP::eval_f(Index n, const Number *x, bool new_x, Number &obj_value) {
    obj_value = pow(x[0] - 1, 2) + pow(x[1] - 1, 2);
    return true;
}

bool MAX_B0_NLP::eval_grad_f(Index n, const Number *x, bool new_x, Number *grad_f) {
    grad_f[0] = 2 * (x[0] - 1);
    grad_f[1] = 2 * (x[1] - 1);
    return true;
}

bool MAX_B0_NLP::eval_g(Index n, const Number *x, bool new_x, Index m, Number *g) {
    return true;
}

bool MAX_B0_NLP::eval_jac_g(Index n, const Number *x, bool new_x, Index m, Index nele_jac, Index *iRow, Index *jCol,
                            Number *values) {
    return true;
}

bool MAX_B0_NLP::eval_h(Index n, const Number *x, bool new_x, Number obj_factor, Index m, const
Number *lambda, bool new_lambda, Index nele_hess, Index *iRow, Index *jCol, Number *values) {
    if (values == NULL) {
        iRow[0] = 0;
        jCol[0] = 0;
        iRow[1] = 1;
        jCol[1] = 1;
    } else {
        values[0] = 2.0;
        values[1] = 2.0;
    }

    return true;

}

void MAX_B0_NLP::finalize_solution(SolverReturn status, Index n, const Number *x, const Number *z_L, const Number *z_U,
                                   Index m, const Number *g, const Number *lambda, Number obj_value,
                                   const IpoptData *ip_data, IpoptCalculatedQuantities *ip_cq) {
    std::cout << std::endl << std::endl << "Solution" << std::endl;
    for (Index i=0; i<n; i++){
        std::cout << "x[" << i << "] = " << x[i] << std::endl;
    }

    for (Index i=0; i<n; i++){
        std::cout << "z_L[" << i << "] = " << z_L[i] << std::endl;
    }

    std::cout << " Objective value  " << obj_value << std::endl;

}