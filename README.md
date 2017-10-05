# Bork: A LISP dialect
```scheme
(define (hai fren) 
		(display 
			(+ "wai halo der " 
				fren 
				"! nice doin u a meet! blep."
			)
		)
)

(hai "pupper")
```

```scheme
(define (fibonacci n) 
	(if (<= n 1) 
		n 
		(+ 
			(f (- n 1)) 
			(f (- n 2))
		)
	)
)

(display 
	(fibonacci 5)
)
(display 
	(fibonacci 20)
)
```

**Bork** is a mini-language modeled after [**LISP**](https://en.wikipedia.org/wiki/Lisp_(programming_language)).

You can define your own functions, use if-else, do arithmetic, use boolean operators, and yes, it supports recursion. 

**Bork** was created as a side-project, an attempt to develop an interpreter for a LISP-like language without having any prior education on computer languages.

## Functions
- (+ _<arg1>_ _<arg2>_ ...) Adds all the arguments. Can be strings or numbers
- (- _<arg1>_ _<arg2>_ ...) Subtracts all the arguments. Must be numbers
- (* _<arg1>_ _<arg2>_ ...) Multiplies
- (/ _<arg1>_ _<arg2>_ ...) Divides
- (mod _<arg1>_ _<arg2>_ ...) takes the modulo (remainder)
- (and _<arg1>_ _<arg2>_ ...) Computes boolean AND
- (or _<arg1>_ _<arg2>_ ...)) Computes boolean OR
- (not <arg1>)
- (< _<arg1>_ _<arg2>_ ) returns _arg1_ < _arg2_
_ (> _<arg1>_ _<arg2>_ )
- (<= _<arg1>_ _<arg2>_ )
- (>= _<arg1>_ _<arg2>_ )
- (= _<arg1>_ _<arg2>_ ) Computes EQUALITY
- (!= _<arg1>_ _<arg2>_) Not equal
- (if _<arg1>_ _<arg2>_ _<arg3>_) If _<arg1>_ is true, evaluates _<arg2>_ else _<arg3>_
- (define _<name>_ _<val>_) Defines a variable with name _<name>_ and value _<val>_
- (define (_<name>_ _<arg1>_ _<arg2>_ ...) _<body>_) Defines a function with name _<name>_, arguments _<arg1>_ _<arg2>_ ... and body _<body>_

## Installing
Clone the repository, and then type in `make` in the terminal, in the directory.

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