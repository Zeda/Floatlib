Floatlib
Zeda Thomas (xedaelnara@gmail.com)


Check out this project on GitHub! : https://github.com/Zeda/Floatlib

Devices
    This app works on the TI-83+, TI-84+, TI-83+SE, TI-84+SE, TI-84+pocket.fr

What is this?
    This app contains a library of third party Z80 floating point routines.
  The routines are sourced from the z80float project (https://github.com/Zeda/z80float),
  and are highly optimized for use on the Z80. For comparison, many routines
  are several times faster than the floats used by the native OS, and at higher
  precision.

    Floatlib also features a built-in reference for its included routines, as
  well as jumptable offsets and a hexadecimal header for on-calc programmers.

    Included are both single- and extended-precision routines for:
      Comparison, Negation, Absolute value
      Addition/Subtraction
      Multiplication
      Division
      Square Roots
      Exponentials (2^x, e^x, 10^x, y^x)
      Logarithms (log2(x), ln(x), log10(x), log_y(x))
      Trig (sine, cosine, tangent)
      Inverse Trig (arcsine, arccosine, arctangent)
      Hyperbolics (sinh, cosh, tanh)
      Inverse Hyperbolics (arcsinh, arccosh, arctanh)
      rand
      Conversion (between strings, floats, and TI floats)
      And more specialty routines including the Borchardt-Gauss mean


How To Use:
    First you need to manually load the app and then you just make calls to jump
  table entries. I've included a pre-made header that loads the app and loads
  the floatlib.inc file, so all you will need to do is include header.z80 (you
  don't even need to include the normal program header). A hexadecimal version
  of the header can be found in-app and it is slightly different.
          #include "header.z80"
          ;Your code goes here

  For details on all of the routines, see Routines.txt.

Example:
  If you want to add pi and e:
      ;Get a pointer to the constant, pi.
      ld a,_pi            ;set a to zero for PI
      call constSingle    ;Gets a pointer in HL to the indicated float

      ;put the pointer in DE for safe keeping
      ex de,hl

      ;Get a pointer to the constant, e.
      ld a,_e
      call constSingle

      ;We will output the result to `scrap`
      ld bc,scrap

      ;Finally, let's add them:
      call addSingle

  And then if we want to convert it to a string and store it back to `scrap`:
      ld h,b    ;Our number is at scrap and BC already points there
      ld l,c
      call single2str

  And if we want to display the string:
      ;ld h,b      ;HL already points to the string location,
      ;ld l,c      ;so we don't need this
      bcall(_PutS)

  So putting it all together, we can add pi and e and then display the result:
      ld a,_pi
      call constSingle
      ex de,hl
      ld a,_e
      call constSingle
      ld bc,scrap
      call addSingle
      ld h,b
      ld l,c
      call single2str
      bcall(_PutS)

  Here is what it looks like with extended-precision floats:
      ld a,_pi
      call xconst
      ex de,hl
      ld a,_e
      call xconst
      ld bc,scrap
      call xadd
      ld h,b
      ld l,c
      call xtostr
      bcall(_PutS)
