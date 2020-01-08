// Author: David Thierry @dthierry CMU 01-06-2020

#include "IpIpoptApplication.hpp"
#include "max_b0_nlp.hpp"

#include <iostream>

using namespace Ipopt;

int main(int argv, char* argc[]){
    SmartPtr<TNLP> nlp_davs = new MAX_B0_NLP();
    std::string optlist;

    SmartPtr<IpoptApplication> ip = IpoptApplicationFactory();
    ip->RethrowNonIpoptException(true);

    std::cout << optlist << std::endl;
    ip->Options()->SetStringValue("output_file", "davs_output");
    ip->Options()->SetNumericValue("bound_push", 1.E-08);
    ip->Options()->SetNumericValue("mu_init", 1.E-05                                                );
    ip->Options()->SetStringValue("print_info_string", "yes");
    ip->Options()->SetIntegerValue("file_print_level", 7);
    ip->Options()->PrintList(optlist);
    ApplicationReturnStatus status;
    status = ip->Initialize();
    if (status != Solve_Succeeded){
        std::cout << std::endl << "Error!" << std::endl;
        return (int) status; //do I have to cast this.
    }

    status = ip->OptimizeTNLP(nlp_davs);

    if (status == Solve_Succeeded){
        std::cout << std::endl << "Solved!" << std::endl;
    } else {
        std::cout << std::endl << "Failure!" << std::endl;

    }

    return (int) status;
}