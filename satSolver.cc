#include "satSolver.h"
#include "minisat/core/SolverTypes.h"
#include "minisat/core/Solver.h"

bool satCallingMiniSat(unsigned int numVar, std::vector<std::vector<int>> &cnf) {
  // your code starts here

    Minisat::Solver solver;
    std::vector<Minisat::Var> variables_generated;

    int counter = 0;
    while(true) {
      if (counter >= numVar) {break;}
      variables_generated.push_back(solver.newVar());
      counter++;
    }

  for (int i = 0; i < cnf.size(); i++) {
    Minisat::vec<Minisat::Lit> CL;
    for (int j = 0; j < cnf[i].size(); j++) {
      if (cnf[i][j] > 0) {
        
        CL.push(Minisat::mkLit(variables_generated[cnf[i][j]-1]));
      } else {

        CL.push(~Minisat::mkLit(variables_generated[-cnf[i][j]-1]));
      }
    }
    solver.addClause(CL);

  }

    bool res = solver.solve();

  return res;
}
