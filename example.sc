(define (f n) 
	(if (<= n 1) 
		n 
		(+ 
			(f (- n 1)) 
			(f (- n 2))
		)
	)
)

(display 
	(f 5)
)
(display 
	(f 20)
)