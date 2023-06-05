'''
The program is written in Vyxal, a language
used for code golf. The language is based
around a stack.

First let's investigate the program:

NCKvΠ₈›%kg*⌊:(:Þż)Wv∑kṅ‹%vøC\»-\»2vø↳ṅ

(Implicitly has stdin on the stack)
N - Swaps uppercase/lowercase
C - Convert to ordinals (now we have a list of char codes)
K - Gets prefixes of the list (e.g. [A,B] -> [[A], [A,B]])
vΠ - Takes product of each element of the list (e.g. [[3,4], [4,5]] -> [12,20])
₈› - Pushes 256+1=257 onto the stack
% - Takes every element of the list mod 257
kg - Pushes the golden ratio = 1.618... onto the stack
* - Multiples every element of the list by the golden ratio
⌊ - Takes the floor of every element of the list
: - Duplicates the list.

For convenience, let l = length of our list.

(   ) - For loop: iterates over the duplicate list, effectively running :Þż l times
 :    - Duplicates the top of the stack
  Þż  - Multiplies each element of the list by its index
Now, the stack has l lists.

W - Wraps the stack into one giant list of lists
v∑ - Takes sum of each element in the list (e.g. [[3,4], [4,5]] -> [7,9])
Essentially, if the elements of the list are a, b, c, etc,
this process creates a+b+c+..., a+2b+3c+..., a+4b+9c+..., and so on.
This is a system of linear equations.

kṅ‹ - Pushes 8192-1=8191 onto the stack
% - Takes every element of the list mod 8191
vøC - Compresses each number in the list into Vyxal's base 255 format
\»- - Remove the »s (delimiters for the base 255 format)
\»2 - Pushes » and 2 onto the stack
vø↳ - Pads every element in the list with » up to a length of 2
ṅ - Concatenates every element of the list.
(Implicit print of top element)

We will have to reverse this.
'''