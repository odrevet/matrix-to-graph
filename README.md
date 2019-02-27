TI software to display a matrix as a graph and perform several operations (dictionary, closure, path search with the ford bellman algorithm)


Written in 2007 for mathematical exams, as a helper tool, and as a project for the computer science exams; as a presentation. At the moment, the application is in french, as it was mandatory to be presented for computer science exam.

Binary compiled with TIGCC http://tigcc.ticalc.org/

The following documentation has been created using a TI-89 titanium, some instructions may vary depending on your TI model.

# Usage

## Send the binary to the calculator

Send the binary to the calculator via the calble or to an emulator like tiemu.

For the TI89, the file to use is mtograph.89z

## Create a matrix using the Data/Matrix Editor

Matrix are created using the calculator's internal `Data/Matrix Editor` application.

Open this application via the main APP menu, then in the dialog menu select `new`, then under type select `matrix`. Under the variable field, enter `m` as the name of the matrix.

Note that the matrix must be square (same number of rows and cols). In row and Col dimension enter `4` in each field.

edit the matrix with values that you need.

## Run

Under the `HOME` app, type `mtograph()` or use the `var-link` menu then select mtograph.

the matrix can be given as an argument, `mtograph(m)`, if no arguments are provided, mtograph start by displaying an open dialog to select a matrix. We will select the previously created matrix `m`.

The graph should be displayed, summits are dsplayed in a diagonal.

Using the cursor menu (F4) the summits can be re-organized by placing the cursor above a summit and pushing enter, then move the cursor to the desired location and pushing enter again.

Order the summits so the graph is readable.

## Menu

* F1 File
  * Open
* F2 Edit (pen icon)
* F3 Display
  * Display matrix: Display the loaded matrix
  * Display Path: Display a list of all paths
  * List Summits: Display a list of all summits
  * Prec dictionary: Display the dictionary of summits previous to one another
  * Next dictionary: Display a dictionry of summits next to one another
  * Matrix power: Given a number, will display each element at this power
  * Transitive closure: Display the matrix with it's transitive closure
  * Path search: Search a path from one summit to another.
* F4 Move (arrow icon): Display an arrow to move summits, this will affect the display only
* F5 quit
