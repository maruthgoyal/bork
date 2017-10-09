# Bork: A LISP dialect
```scheme
(define (hai fren) 
		(display 
			(+ "wai halo der " 
				fren 
				"! nice doin u a meet! blep.")))

(hai "pupper")
```

```scheme
(define (fibonacci n) 
	(if (<= n 1) 
		n 
		(+ 
			(f (- n 1)) 
			(f (- n 2)))))

(display (fibonacci 5))
(display (fibonacci 20))
```

**Bork** is a mini-language modeled after [**LISP**](https://en.wikipedia.org/wiki/Lisp_(programming_language)).

You can define your own functions, use if-else, do arithmetic, use boolean operators, and yes, it supports recursion. 

**Bork** was created as a side-project, an attempt to develop an interpreter for a LISP-like language without having any prior education on computer languages.

## Functions
- `(+ arg1 arg2 ...)` Adds all the arguments. Can be strings or numbers
- `(- arg1 arg2 ...)` Subtracts all the arguments. Must be numbers
- `(* arg1 arg2 ...)` Multiplies
- `(/ arg1 arg2 ...)` Divides
- `(mod arg1 arg2 ...)` takes the modulo (remainder)
- `(and arg1 arg2 ...)` Computes boolean AND
- `(or arg1 arg2 ...)` Computes boolean OR
- `(not arg1)`
- `(< arg1 arg2)` returns arg1 < arg2
- `(> arg1 arg2)`
- `(<= arg1 arg2)`
- `(>= arg1 arg2)`
- `(= arg1 arg2)` Computes EQUALITY
- `(!= arg1 arg2)` Not equal
- `(if arg1 arg2 arg3)` If arg1 is true, evaluates arg2 else arg3
- `(define name val)` Defines a variable with name _<name>_ and value _<val>_
- `(define (name arg1 arg2 ...) body)` Defines a function with name name, arguments arg1 arg2 ... and body, body

## Installing
```bash
git clone https://github.com/maruthgoyal/bork.git
cmake
make
```

## Usage
- Start the REPL with the command `./bork`
- Run a file with `./bork your_file.sc`
- Pretty-fy your file with `./bork your_file.sc -p`

## Licensing
This code is released under the **MIT** License.
### Created by Maruth Goyal

Copyright (c) 2017 Maruth Goyal

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.