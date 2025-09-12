 OwlTechA1 - Number Base Conversion Utility

## Author
Kai Glaza

## Description
Starter files for Owl Tech Assignment 1: Number base conversion utility.## 

## Test Results
- All of the div_convert tests worked.
- Robustness testing of sub_convert failed with outputs like *out of 1111111111111 or similar.
- fixed it was a weird issue with the logic I used it led to inf

## Notes
- Compiling and running can be tricky; the console commands are a bit confusing; steepest learning curve.
- Unsure about all the junk files included; needed ChatGPT and Reddit to figure out how to run the files :C
- Printing output in the console has been so cryptic and unsual I still don't really get it

## Biggest Issues
- sub_convert caused the largest issues, breaking during robustness testing.
- Printing functionality was frustrating, but I learned a lot from working through it.


## Build Instructions
idk what this really means but I had to run something different from the document
```bash
cd src
gcc main.c convert.c -o main
./main
