// Author: David Thierry @dthierry CMU 01-06-2020

#include "IpIpoptApplication.hpp"
#include "max_b0_nlp.hpp"

#include <iostream>

using namespace Ipopt;

int main(int argv, char* argc[]){
    SmartPtr<TNLP> nlp_davs = new MAX_B0_NLP();

    SmartPtr<IpoptApplication> ip = IpoptApplicationFactory();
    ip->RethrowNonIpoptException(true);
    ip->Options()->SetStringValue("output_file", "davs_output");

    ApplicationReturnStatus status;
    status = ip->Initialize();
    if (status != Solve_Succeeded){
        std::cout << std::endl << "Error!" << std::endl;
        return (int) status; //do I have to cast this.
    }

    status = ip->OptimizeNLP(nlp_davs);

    if (status == Solve_Succeeded){
        std::cout << std::endl << "Solved!" << std::endl;
    } else {
        std::cout << std::endl << "Failure!" << std::endl;

    }

    return (int) status;
}