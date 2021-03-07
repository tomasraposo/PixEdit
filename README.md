# pixedit
A tiny command line ppm editor 

```
Usage: ./pixedit [OPTION] ... [INFILE] [OUTFILE]

Type './pixedit --h [--help]' for instructions.
```
##### Supported image types
- P3 (ASCII)
- P6 (binary)

##### Available commands
- **-d** (single-flag) opens new window with [FILE]

- **-n[r][g][b]** negates the red, green or blue value of each pixel

- **-f[r][g][b]** sets red, green or blue value of each pixel to zero

- **-m**  flips image along diagonal

- **-fv** flips each row vertically

- **-gs** sets each pixel value to the average of the three";

- **-hb** takes the values of the red numbers of three adjacent pixels and replaces them with their average

- **-ec** changes each colour number to either the highest colour number possible (if greater than 127) or to 0

- **-rn** adds a random number to each colour number or subtracts a random number

- **-i** inverts the red, green and blue vales of each pixel

- **-z[rg][rb][gb]** flattens red and green, red and blue or green and blue values of each pixel
