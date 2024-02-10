# OptimizationSearchAlgorithms

This project is an implementation of 4 diferent Search/Optimization algorithms (Hill Climber, Probabilistic Hill Climber, Genetic and Hibrid between Hill Climber and Genetic) to solve the <b>"Maximum Edge Subgraph Problem"</b>

Given an undirected graph and an integer value k, the Maximum Edge Subgraph Problem involves finding a subset of k vertices such that the number of edges within the subset is maximized.

Formally, the problem is defined as follows:
Given

<li>an undirected graph G = (V, E), composed of a set V of vertices connected by edges E.</li>
<li>an integer k</li>
Problem:

Find a subset of vertices S of size k, such that V is a subset of S, in order to maximize the number of edges within this subset.
The objective of this problem is, therefore, a maximization problem.

The graphs are represented in each fileN.txt <p>
k 18 <p>
p edge 45 918 <p>
e 2 1 <p>
e 3 1 <p>
e 3 2 <p>
e 4 1 <p>
e 4 2 <p>
<li>The first line indicates the value of K</li>
<li>The second line provides further information about the graph, in this case the graph has 45 vertices and 918 edges total</li>
<li>Each subsequent line refers to and edge conecting two vertices, the first conects 2 and 1, the second 3 and 1, the third 3 and 2 and so on...</li>
