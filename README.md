# Symbolic Regression using Genetic Programming with Adversarial Learning

This project uses Genetic Programming with underlying graph representation (Cartesian Genetic Programming, CGP) 
to solve problem of Symbolic Regression. It uses Adversarial Learning where one model tries to 
guess the unknown function (represented as a black box), and the other tries to produce hardest possible
training dataset. As the first model gets better, the other one has harder task to find the training dataset 
that the first model still doesn't describe well and vice versa.

Project is done by using ECF (Evolutionary Computation Framework) in C++ (http://ecf.zemris.fer.hr/).
