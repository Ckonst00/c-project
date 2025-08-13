C project for the Aalto University course Basic Course in C programming.

## Adding a reservation:
  input form: A name month date hour
  
  An example:
  "A Dorsia 8 13 14"
  
  --> saved as "Dorsia 13.08 at 14"

## Deleting a reservation:
  input form: D month day hour

  An example:
  "D 8 13 14"

## See all the reservations:
  input form: L

  An example:
    "L"
    --> "Dorsia 13.08 at 14"


## Save reservations to a file:

  input form: W filename

  An example:
  "W newfile"

  --> a file named newfile is created to the root of the project folder

## Load from file, which loads meetings from a text file saved using Save to file command:

  input form: O newfile
  
