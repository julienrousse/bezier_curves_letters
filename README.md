# Bézier curves letters

The code produces three font styles of uppercase sans serif letters, defined with Bézier curves (de Casteljau's algortihm):
  - a font with only the outline of the letters
  - a font with the inside of the letters in black
  - a font with the inside of the letters in black and a 2 pixels red outline

The code was written in C++, using Eclipse and the [Doxygen](http://www.stack.nl/~dimitri/doxygen/) syntax.

The font reproduced is "Keep Calm", with control points coordinates (`points_lettres.txt`) obtained with the free software [FontForge](https://fontforge.github.io).  
The images produced are saved in `.ppm` files.
