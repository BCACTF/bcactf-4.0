#!sage
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

'''
First step: Getting the linear equations.
We will do this using Vyxal itself (for
the compression).

The newline is messing things up so I will
replace it with a j in input and then fix 
it in the code (j being an arbitrary
unused char).

(n.b. my Vyxal code is likely quite bad)

\j¶Vǒ\»-k⟇\»-vβ

\j¶ - Push j and newline to stack
V - Replace j with newline
ǒ - Split chars into pairs
\»- - Push and remove all »s (padding)
k⟇\»- - Push Vyxal codepage minus »
vβ - Use that as a base to decode each element

This recovers the sums
⟨ 1883 | 2358 | 521 | 6548 | 2483 | 4088 | 2152 | 7308 | 5831 | 6585 | 350 | 5377 | 1115 | 4493 | 2962 | 7717 | 6227 | 1065 | 6588 | 1301 | 5163 | 5489 | 2090 | 4520 | 2144 | 1690 | 1114 | 1805 | 2239 | 6808 | 791 | 3649 | 7158 | 1080 | 5701 | 1904 | 8168 | 5697 | 1556 | 7683 | 3939 | 7 | 1984 | 4148 | 2770 | 3156 | 5763 | 5733 | 84 | 3092 | 6048 ⟩.

Then q\|\,V\ - to make it a more Python-usable format
(make string, replace | with , remove spaces)
'''

# Use sage linear algebra to solve the system
vec = vector(GF(8191),[1883,2358,521,6548,2483,4088,2152,7308,5831,6585,350,5377,1115,4493,2962,7717,6227,1065,6588,1301,5163,5489,2090,4520,2144,1690,1114,1805,2239,6808,791,3649,7158,1080,5701,1904,8168,5697,1556,7683,3939,7,1984,4148,2770,3156,5763,5733,84,3092])
mat = matrix(GF(8191),[[(c+1)^r for c in range(len(vec))] for r in range(len(vec))])
solution = list(mat \ vec)

# Next: divide by the golden ratio and ceiling
divided = [ceil(N(x) / N(golden_ratio)) for x in solution]
 
# Then get the original numbers one at a time through division
ords = [divided[0]]+[(divided[x+1]/divided[x])%257 for x in range(len(divided)-1)]

# Then convert back to chars
chars = [chr(x) for x in ords]

# Finally, join and swap case
print(''.join(chars).swapcase())