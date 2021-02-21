# Gigel and the Mobsters - AA Homework 2 - C++

## Necula Alexandru - 322CD

### Task 1

For solving this task, I assigned a variable to each family-spy association. For
example, families_num = 2, spies_num = 2

- f1-s1 -> 1
- f1-s2 -> 2
- f2-s1 -> 3
- f2-s2 -> 4

For analyzing the complexity of the solution, let:

- V = families_num
- E = relationships_num
- S = spies_num (can be reduced to a constant)

There are 3 types of restrictions to reduce this problem to SAT.

- There is at least 1 spy assigned to a family - **O(V\*S)**
- There is at most 1 spy assigned to a family - **O(V\*S)**
- Each related family has a different spy - **O(E\*S)**

Depending on the relationship between V and E, the final complexity will be
either **O(ES)** or **O(VS)**. In our tests, E is almost always greater than V
and S can be reduced to a constant, so we can safely assume that the complexity
is **O(E)**.

### Task 2

Task 2 is actually the K-Clique problem, which can be reduced to SAT. We create
a list of variables which are interpreted as "v is the i-th vertex in the
clique" and store them in a map.

For analyzing the complexity of the solution, let:

- V = families_num
- E = relationships_num
- k = family_size (constant)

Firstly, we convert the pairs of families to an adjacency matrix. Then, we
create the clauses for the SAT solver.

There are 3 types of restrictions to reduce this problem to SAT.

- There must be exactly one vertex v in that clique for each i between 1 and k
  (family_size) - **O(V)**
- For every non-edge (v,w), v and w cannot both be in the clique - **O(V^2)**
- For every i, j (where j != i), the i-th vertex is different from the j-th
  vertex - **O(V^2)**

Last two restrictions are implemented with two nested for loops, so the
complexity will be **O(V^2)** because our variable map has k\*V variables.

Final complexity: **O(V^2)**

### Task 3

Task 3 is actually the Minimum Vertex Cover problem, which I reduced to the
K-Clique problem in Task 2.

For analyzing the complexity of the solution, let:

- V = families_num
- E = relationships_num
- k = minimum number of arrests (minimum vertex cover size)

Let our family graph be G = (V, E). In a for loop, we start with k = 1 and
iterate until we find a vertex cover. Worst case: k = V

The steps for reducing to Task 2 are:

- Generate the complement graph: !G = (V, !E)
- Solve Clique(!G, V - k)
- Task 2 will return the families that are not in our vertex cover, if found
- Using a variable map, we will find the families that are in our vertex cover

Because we call Task 2 k times which has **O(V^2)** complexity, Task 3's
complexity will be **O(V^3)**

### Bonus

We want to reduce Minimum Vertex Cover directly to SAT.

For analyzing the complexity of the solution, let:

- V = families_num
- E = relationships_num

Let variable x_i for every vertex i, representing the condition that the vertex
is part of the vertex cover.

There are two types of restrictions we have to construct:

- All edges in the family graph must be covered by the selected vertices (hard
  clause, **O(E)**)
- A variable corresponding to a vertex can be false (soft clause, maximize
  number of true clauses, minimize number of true variables, **O(V)**)

Depending on the relationship between V and E, the final complexity will be
either **O(E)** or **O(V)**. In our tests, E is almost always greater than V, so
we can safely assume that the complexity is **O(E)**.
