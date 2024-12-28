from pulp import *

# Create a LP problem
prob = LpProblem("Example", LpMaximize)

# Read the LP file
prob.readLP("ex1.lp")

# Solve the LP problem
prob.solve()

# Get the solution
print("Status:", LpStatus[prob.status])
for var in prob.variables():
    print(var.name, "=", var.varValue)
print("Optimal value:", value(prob.objective))
