# B-Tree

University of São Paulo - São Carlos

2nd Semester of 2017

Project made for the course "SCC603 - Algorithms and Data Structures II", ministered by Professor Elaine Parros M. de Sousa.

This project was originally made by:

* Guilherme Blatt (https://github.com/guilherme-blatt)
* Lucas Akira Morishita (https://github.com/lucas-akira)
* Thiago Músico (https://github.com/ThiagoMusico)
* Tiago Toledo Junior (https://github.com/TNanukem)

## Brief description and objective

Abstract data type implementation of an order 5 B-tree (generalization of a binary search tree), along with data indexing, creation, insertion and search. 

The goal was to apply the concepts studied during the classes into a practical environment. The 'Complete project requirements' section contains the English translation of the original PDF file (Trabalho2_BTree.pdf) describing the project to be made (in Portuguese) with all the requirements imposed by the professor.

## (some) Project features
* Made in C
* B-Tree stored in secondary memory (in disk)
* No global variables
* No external libraries, apart from the C standard ones (like stdio, stdlib, etc.)
* Creates a log file with each action done (insertion, creation, etc.),

## Running
```
gcc arquivo.c arvore.c fila.c main.c -o b-tree
./b-tree
```

## Complete project requirements (WIP)

University of São Paulo 

Institute of Mathematics and Computer Science

Computer Sciences Department

### Project 2 - B-Tree

#### 1. Project Objective

Apply the concepts studied in the course Algorithms and Data Structures II to implement solutions to practical problems. 

On this project, the student must develop a program in C or C++ to resolve the problem specified in **section 4** using graphs and data structure concepts.

The program must be compiled in **Code::Blocks 16.01**. (*sic*) 

(*Note: this project was compiled using gcc*)

#### 2. Avaliation Criteria

The program should be developed in groups of 3 or 4 students and must follow strictly the defined input and output formats. Any copied programs (partially or totally) will obtain **grade zero**, no matter which one is the original or the copy. Programs developed in another programming language (other than C/C++) will not be accepted.

* The project grade will be from 0 to 10 (inclusive)
* The maximum grade is obtained if the evaluated project follows all requirements, and is well organized and presented
* For each non-fulfilled requirement the grade will be decreased by one until its minimum limit
* Grade ZERO will be obtained when one (or more) of these itens occurs:
  * the project is not delivered until the maximum allowed date;
  * the project has many errors;
  * the code fails compilation;
  * complete or partial code copy is detected;
  * a report is not delivered according to specification;
  * the B-tree is not implemented in disk;
  * insertion and/or search operations are made without the use of the B-tree.
  
The avaliation itens are:
1. (50%) The program works correctly in the described tasks for all test cases and process input/output correctly;
2. (20%) Quality of the developed solution, functional code modularization, good usage of programming techniques and efficiency in terms of space and time;
3. (10%) Good identation and comment usage in code, along with good code structure;
4. (20%) External documentation: Short report (in .pdf format) explaining each taken decision to implement the solution, being necessary the inclusion of details about (at least) the index archive structure, used data structures, implementation strategies of the B-tree creation, search, insertion and removal, and time/space complexity estimations. Include figures to illustrate file organization and support structures (similar to the figures shown in class). 

#### 3. Delivery date and method

**Delivery date:** 30/11/2017 - until 23:55 (*GMT-3*)

(*The date was later changed to 05/12/2017*)

The considered delivered date will be the most recent archive upload in the *Tidia-ae* platform.

For each **overdue** day **one point of the final grade will be subtracted**. For this rule consecutive days will be considered, no matter if it is a working day or not. 

No projects will be accepted after the maximum deadline of ten days.

**Delivery method:**

The delivery method will be done in the *Tidia-ae* platform inside Activity **Project 2**.

**What to deliver?**

You should deliver the archives containing **only your source code and the report**. The complete project folder should be compressed into a single archive (with .zip extension).

The name of the compressed archive should be formed by the acronym "T2-" concatenated to the first letter of the name, followed by the last surname of the group member that delivered the project.

Example: T2-esousa
