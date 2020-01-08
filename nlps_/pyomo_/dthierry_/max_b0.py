from pyomo.environ import *
from pyomo.opt import SolverFactory

m = ConcreteModel()
m.x = Var([0, 1], within=NonNegativeReals)
m.x[0].set_value(1e-09)
m.x[1].set_value(1e-09)
m.of = Objective(expr=(m.x[0] - 1) ** 2 + (m.x[1] - 1) ** 2, sense=minimize)

print("Before solution")
m.display()

ip = SolverFactory('/home/dav0/in_dev_/ipopt_vanilla_l1/builds/ipopt_l1/bin/ipopt')
ip.options["bound_push"] = 1e-08
ip.options["mu_init"] = 1e-05
ip.solve(m, tee=True)

print("After solution")
m.display()

