TI software to display a matrix as a graph and perform several operations (dictionary, closure, edge search with the ford bellman algorithm). 
Written in 2007 for mathematical exams, as a helper tool, and as a project for the computer science exams. 

Binary compiled with TIGCC http://tigcc.ticalc.org/

The following documentation has been created using a TI-89 titanium, some instructions may vary depending on your TI model.

# Build

## For TI calculator

* Install tigcc and export the TIGCC environement variable
```
mkdir tigcc
wget http://tigcc.ticalc.org/linux/tigcc_bin.tar.bz2
tar -xjf tigcc_bin.tar.bz2 -C tigcc
export TIGCC=~/tigcc
```

The software can now be build with make

  make 

## For PC terminal

A makefile is provided for PC build

  make -f Makefile_PC

# Usage

## Send the binary to the calculator

Send the binary to the calculator via the calble or to an emulator like tiemu.

to install tiemu under ubuntu, run:  

    sudo apt install tiemu

For the TI89, the file to use is mtograph.89z

## Create a matrix using the Data/Matrix Editor

Matrix are created using the calculator's internal `Data/Matrix Editor` application.

Open this application via the main APP menu, then in the dialog menu select `new`, then under type select `matrix`. 
Under the variable field, enter the name of the new matrix, for example `m`.

Note that the matrix must be square (same number of rows and cols). In row and Col dimension enter `4` in each field.

edit the matrix with values that you need.

## Run

Under the `HOME` app, type `mtograph()` or use the `var-link` menu then select mtograph.

the matrix can be given as an argument, `mtograph(m)`, if no arguments are provided, mtograph start by displaying an open dialog to select a matrix. We will select the previously created matrix `m`.

Using the cursor menu (F4) the nodes can be re-organized by placing the cursor above a node and pushing enter, then move the cursor to the desired location and pushing enter again.

## Menu

* F1 File
  * Open
* F2 Edit (pen icon)
* F3 Display
  * Display matrix: Display the loaded matrix
  * Display edge: Display a list of all edges
  * List  nodes: Display a list of all  nodes
  * Prec dictionary: Display the dictionary of  nodes previous to one another
  * Next dictionary: Display a dictionry of  nodes next to one another
  * Matrix power: Given a number, will display each element at this power
  * Transitive closure: Display the matrix with it's transitive closure
  * edge search: Search a edge from one  node to another.
* F4 Move (arrow icon): Display an arrow to move  nodes, this will affect the display only
* F5 quit
